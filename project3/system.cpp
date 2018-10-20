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
//    resetForces();
//    calculateForces();
    m_integrator->integrate(this, timestep);
    updateEnergies();
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

void System::removeTotalMomentum() {
    vec3 TotalVelocity(0,0,0);

    double totalMass = 0;

    for(SObject *obj : m_objects) {
        TotalVelocity += (obj->velocity * obj->mass);
        totalMass += obj->mass;
    }
    std::cout<< TotalVelocity << std::endl;

//    TotalVelocity /= (m_objects.size() * totalMass);
    TotalVelocity /= (totalMass);


    for(SObject *obj: m_objects) {
        obj->velocity -= TotalVelocity;
    }

    TotalVelocity = {0,0,0};
    for(SObject *obj : m_objects) {
        TotalVelocity += (obj->velocity * obj->mass);
    }
    std::cout<< TotalVelocity << std::endl;
}
