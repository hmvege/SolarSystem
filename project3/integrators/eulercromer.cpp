#include "eulercromer.h"

EulerCromer::EulerCromer()
{

}

EulerCromer::~EulerCromer()
{

}

void EulerCromer::integrate(System *system, const double h)
{
    /*
     * Regular Euler Cromer
     */

    system->calculateForces();

    for (SObject *sobj : system->objects()) {

        sobj->velocity += sobj->force*h / sobj->mass;

        sobj->position += sobj->velocity*h;

    }
}
