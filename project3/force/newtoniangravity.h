#ifndef NEWTONIANGRAVITY_H
#define NEWTONIANGRAVITY_H

#include "force/force.h"

class NewtonianGravity : public Force
{
private:
    double m_G = 0;
public:
    NewtonianGravity();
    NewtonianGravity(double G);
    ~NewtonianGravity();

    void calculateForces(System *system);
    void calculatePotentialEnergy(System *system);
};

#endif // NEWTONIANGRAVITY_H
