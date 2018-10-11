#ifndef NEWTONIANGRAVITY_H
#define NEWTONIANGRAVITY_H

#include "force/force.h"

class NewtonianGravity : public Force
{
private:
    double m_G = 0;
    double m_sunMass = 0;
public:
    NewtonianGravity();
    NewtonianGravity(double G, double sunMass);
    ~NewtonianGravity();

    void calculateForces(System *system);
};

#endif // NEWTONIANGRAVITY_H
