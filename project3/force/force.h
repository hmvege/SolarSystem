#ifndef FORCE_H
#define FORCE_H

#include "sobject.h"
#include "system.h"

class Force
{
public:
    Force();
    virtual ~Force();

    virtual void calculateForces(System *system) = 0;
};

#endif // FORCE_H
