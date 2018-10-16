#ifndef VELOCITYVERLET_H
#define VELOCITYVERLET_H

#include "integrators/integrator.h"

class VelocityVerlet : public Integrator
{
private:
    bool firstStep = true;
public:
    VelocityVerlet();
    ~VelocityVerlet();

    void integrate(System *system, const double h);
};

#endif // VELOCITYVERLET_H
