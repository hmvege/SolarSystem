#include "system.h"
#include "integrators/integrator.h"
#include "force/force.h"

// TODO: implement remove-total-momentum

System::System()
{

}

System::~System() {
    /*
     * Deallocates all the objects!
     */
    for(SObject *obj : m_objects) {
        delete obj;
    }
    m_objects.clear();
    delete m_force;
    delete m_integrator;

}

void System::resetForces() {
    /*
     * Ensures the force vector in each object is set to zero.
     */
    for (SObject *obj : m_objects) {
        obj->force = {0,0,0};
    }
}

void System::update(const double timestep)
{
    // Forces sun to be stationary. Used for calculating precesion.
    if (m_forceStationarySun) {
        setSunStationary();
    }

    m_integrator->integrate(this, timestep);
    updateEnergies();
    if (m_storePerihelion) {
        if (!m_firstPerihelionStep) {
            for (SObject *obj : m_objects) {
                obj->perihelion.previousPos = obj->position;
            }
            m_firstPerihelionStep = true;
        }
        else {
            // Updates perihelion positions
            for (SObject *obj : m_objects) {
                obj->perihelion.previousPreviousPos = obj->perihelion.previousPos;
                obj->perihelion.previousPos = obj->perihelion.currentPos;
                obj->perihelion.currentPos = obj->position;
            }

            for (SObject *obj : m_objects) {
                double prevLength = obj->perihelion.previousPos.length();
                if ((prevLength < obj->perihelion.currentPos.length())
                        && (prevLength < obj->perihelion.previousPreviousPos.length())) {
                    obj->perihelion.perhielionPosition.push_back(obj->position);
                    obj->perihelion.perhielionVelocity.push_back(obj->velocity);
                }
            }
        }

    }
}

void System::calculateForces()
{
    resetForces();
    m_force->calculateForces(this);
}

void System::updateEnergies()
{
    for (SObject *obj : m_objects) {
        obj->kineticEnergy = obj->velocity.lengthSquared() * obj->mass * 0.5;
        obj->angularMomentum = obj->mass * cross(obj->position, obj->velocity);
    }
    m_force->calculatePotentialEnergy(this);
}

void System::storePerihelionValues(bool storePerihelion) {
    /*
     * Sets up objects for storing perihelion values, and initializes
     * prev-prev values.
     */
    for (SObject *obj : m_objects) {
        obj->initializePerihelion();
    }
    m_storePerihelion = storePerihelion;
}

void System::forceStationarySun(bool forceStationary)
{
    m_forceStationarySun = forceStationary;
}

void System::setSunStationary()
{
    for (SObject *obj : m_objects) {
        if (obj->name == "sun") {
            obj->position = {0,0,0};
            obj->velocity = {0,0,0};
        }
    }
}


void System::removeTotalMomentum() {
    vec3 TotalMomentum(0,0,0);

    double totalMass = 0;

    for(SObject *obj : m_objects) {
        TotalMomentum += (obj->velocity * obj->mass);
        totalMass += obj->mass;
    }

    //    TotalMomentum /= (m_objects.size() * totalMass);
    TotalMomentum /= (totalMass);

    for(SObject *obj: m_objects) {
        obj->velocity -= TotalMomentum;
    }

}

void System::checkTotalMomentum()
{
    vec3 TotalMomentum= {0,0,0};
    for(SObject *obj : m_objects) {
        TotalMomentum += (obj->velocity * obj->mass);
    }
    std::cout<< TotalMomentum << std::endl;
}
