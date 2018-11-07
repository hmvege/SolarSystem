#include "sobject.h"


SObject::SObject(vec3 &newPosition, vec3 &newVelocity, const double newMass, std::string newName)
{
    position = newPosition;
    velocity = newVelocity;
    force = {0,0,0};
    kineticEnergy = 0;
    potentialEnergy = 0;
    angularMomentum = {0,0,0};
    mass = newMass;
    name = newName;
}


void SObject::printObject()
{
    printf("%8s: r=[%15.10f %15.10f %15.10f] v=[%15.10f %15.10f %15.10f] L=[%15.10f %15.10f %15.10f] KE=%15.10f PE=%15.10f\n", name.c_str(),
           position[0], position[1], position[2],
            velocity[0], velocity[1], velocity[2],
            angularMomentum.x(), angularMomentum.y(), angularMomentum.z(),
            kineticEnergy, potentialEnergy);
}

