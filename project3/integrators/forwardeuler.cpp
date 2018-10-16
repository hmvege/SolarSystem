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
     * A basic forward Euler(or Euler Cromer to be precise)
     */

    system->calculateForces();

//    vec3 tempVelocity(0,0,0);

    for (SObject *sobj : system->objects()) {

//        tempVelocity = sobj->velocity;


//        sobj->position += tempVelocity*h;
        sobj->velocity += sobj->force*h / sobj->mass;

        sobj->position += sobj->velocity*h;
    }
}
