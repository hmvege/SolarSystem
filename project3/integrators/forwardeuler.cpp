#include "forwardeuler.h"
#include <cmath>

ForwardEuler::ForwardEuler()
{

}

ForwardEuler::~ForwardEuler()
{

}

void ForwardEuler::integrate(System *system, const double h)
{
    /*
     * A basic forward Euler(or Euler Cromer to be precise)
     */

    for (SObject *sobj : system->objects()) {

        sobj->velocity += sobj->force*h / sobj->mass;

        sobj->position += sobj->velocity*h;
    }
}
