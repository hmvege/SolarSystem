#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include "sobject.h"


// Defines classes to use, if not they will be left out by guard since it wont allow cross usage.
class Force;
class Integrator;


using std::vector;


class System
{
private:
    Integrator *m_integrator;

    Force *m_force;

    vector<SObject*> m_objects;
public:
    System();
    ~System();

    void addObject(SObject *object) { m_objects.push_back(object); }
    void update(const double timestep);

    void resetForces();

    void setIntegrator(Integrator *integrator) { m_integrator = integrator; }
    void setForce(Force *force) { m_force = force; }

    vector<SObject*> &objects() { return m_objects; }
};

#endif // SYSTEM_H
