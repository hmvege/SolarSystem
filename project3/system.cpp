#include "system.h"
#include "integrators/integrator.h"
#include "force/force.h"

// TODO: implement remove-total-momentum

System::System(double normalizerMass) : m_normalizerMass(normalizerMass)
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
        obj->kineticEnergy = dot(obj->velocity, obj->velocity) * obj->mass / m_normalizerMass * 0.5;
        obj->angularMomentum = obj->mass / m_normalizerMass * cross(obj->position, obj->velocity);
    }
    m_force->calculatePotentialEnergy(this);
}

//void System::removeTotalMomentum() {
//    vec3 TotalVelocity(0,0,0);

//    for(Atom *atom : m_atoms) {
//        TotalVelocity += atom->velocity;
//    }

//    TotalVelocity /= m_atoms.size();

//    for(Atom *atom : m_atoms) {
//        atom->velocity -= TotalVelocity;
//    }
//}
