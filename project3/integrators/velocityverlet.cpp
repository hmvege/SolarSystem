#include "velocityverlet.h"


VelocityVerlet::VelocityVerlet()
{

}

VelocityVerlet::~VelocityVerlet()
{

}

void VelocityVerlet::integrate(System *system, const double h)
{
    /*
     * A basic forward Euler(or Euler Cromer to be precise)
     */
    if(firstStep) {
        system->calculateForces();
        firstStep = false;
    }

    for (SObject *sobj : system->objects()) {

        sobj->velocity += sobj->force*h*0.5 / sobj->mass;

    }

    for (SObject *sobj : system->objects()) {

        sobj->position += sobj->velocity*h;
    }

    system->calculateForces();

    for (SObject *sobj : system->objects()) {

        sobj->velocity += sobj->force*h*0.5 / sobj->mass;
    }
}
