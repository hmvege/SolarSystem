#include "sobject.h"


SObject::SObject(vec3 &newPosition, vec3 &newVelocity, const double newMass, std::string newName)
{
    position = newPosition;
    velocity = newVelocity;
    for (unsigned int i = 0; i < 3; i++) {
        force[i] = 0;
    }
    mass = newMass;
    name = newName;
}


void SObject::printObject()
{
    printf("%8s: r=[%12.5f %12.5f %12.5f] v=[%12.5f %12.5f %12.5f]\n", name.c_str(),
           position[0], position[1], position[2],
            velocity[0], velocity[1], velocity[2]);
}
