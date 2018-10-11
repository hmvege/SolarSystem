#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "system.h"

class Integrator
{
public:
    Integrator();
    virtual ~Integrator();
    virtual void integrate(System *system, const double h) = 0;
};

#endif // INTEGRATOR_H
