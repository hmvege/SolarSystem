#include "forwardeuler.h"

ForwardEuler::ForwardEuler()
{

}

ForwardEuler::~ForwardEuler()
{

}

void ForwardEuler::integrate(System *system, const double h)
{
    /*
     * Forward Euler
     */

    system->calculateForces();

    for (SObject *sobj : system->objects()) {

        sobj->position += sobj->velocity*h;

        sobj->velocity += sobj->force*h / sobj->mass;
    }
}
