#ifndef FORCE_H
#define FORCE_H

#include "system.h"

class Force
{
public:
    Force();
    virtual ~Force();

    virtual void calculateForces(System *system) = 0;
    virtual void calculatePotentialEnergy(System *system) = 0;
};

#endif // FORCE_H
