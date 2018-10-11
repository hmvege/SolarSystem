#ifndef FORWARDEULER_H
#define FORWARDEULER_H

#include "integrators/integrator.h"

class ForwardEuler : public Integrator
{
public:
    ForwardEuler();
    ~ForwardEuler();

    void integrate(System *system, const double h);
};

#endif // FORWARDEULER_H
