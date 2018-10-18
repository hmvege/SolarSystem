#ifndef NEWTONIANGRAVITYCORRECTED_H
#define NEWTONIANGRAVITYCORRECTED_H

#include "force/force.h"

class NewtonianGravityCorrected : public Force
{
private:
    double m_G = 0;
public:
    NewtonianGravityCorrected();
    NewtonianGravityCorrected(double G);
    ~NewtonianGravityCorrected();

    void calculateForces(System *system);
    void calculatePotentialEnergy(System *system);
};

#endif // NEWTONIANGRAVITYCORRECTED_H
