#ifndef MODIFIEDGRAVITY_H
#define MODIFIEDGRAVITY_H

#include "force/force.h"

class ModifiedGravity : public Force
{
private:
    double m_G = 0;
    double m_beta = 2;
public:
    ModifiedGravity();
    ModifiedGravity(double G);
    ~ModifiedGravity();

    void setBeta(double beta) { m_beta = beta; }

    void calculateForces(System *system);
    void calculatePotentialEnergy(System *system);
};

#endif // MODIFIEDGRAVITY_H
