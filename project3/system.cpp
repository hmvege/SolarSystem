#include "system.h"
#include "integrators/integrator.h"
#include "force/force.h"

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
    resetForces();
    m_force->calculateForces(this);
    m_integrator->integrate(this, timestep);
}
