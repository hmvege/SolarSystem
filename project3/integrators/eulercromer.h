#ifndef EULERCROMER_H
#define EULERCROMER_H

#include "integrators/integrator.h"

class EulerCromer : public Integrator
{
public:
    EulerCromer();
    ~EulerCromer();

    void integrate(System *system, const double h);
};

#endif // EULERCROMER_H
