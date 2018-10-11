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
    vec3 tempVel(0);
    system->calculateForces();

//    system->objects()[1]->velocity += system->objects()[1]->force*h;
//    system->objects()[1]->position += system->objects()[1]->velocity*h;

//    system->objects()[0]->velocity += system->objects()[0]->force*h;
//    system->objects()[0]->position += system->objects()[0]->velocity*h;

    for (SObject *sobj : system->objects()) {
//        tempVel = sobj->velocity;

        sobj->velocity += sobj->force*h / sobj->mass;

//        sobj->position += tempVel*h;
        sobj->position += sobj->velocity*h;
    }
}
