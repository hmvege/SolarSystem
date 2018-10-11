#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include "sobject.h"


class System
{
private:
    double m_G;
    double m_sunMass = 1988500e24;

    std::vector<SObject*> m_objects;
public:
    System();
    ~System();

    void addObject(SObject *object) { m_objects.push_back(object); }
    void solve(const double timestep);

    void resetForces();

    void calculateForces();

    std::vector<SObject*> &objects() { return m_objects; }
};

#endif // SYSTEM_H
