#ifndef SOBJECT_H
#define SOBJECT_H

#include <string>
#include "math/vec3.h"

class SObject
{
public:
    SObject(vec3 &newPosition, vec3 &newVelocity, const double newMass, std::string newName);
    ~SObject() {}

    vec3 position;
    vec3 velocity;
    vec3 force;
    double mass;
    double kineticEnergy;
    double potentialEnergy;
    vec3 angularMomentum;

    std::string name;

    void printObject();

};

#endif // SOBJECT_H
