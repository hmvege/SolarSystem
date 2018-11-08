#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include "sobject.h"
#include "perihelionstorer.h"


// Defines classes to use, if not they will be left out by guard since it wont allow cross usage.
class Force;
class Integrator;


using std::vector;


class System
{
private:
    bool m_storePerihelion = false;

    // Is there a better way?
    bool m_forceStationarySun = false;
    void setSunStationary();

    bool m_firstPerihelionStep = false;
    vector <PerihelionStorer*>m_perihelionValues; // A vector of the objects perihelion angles

    Integrator *m_integrator;

    Force *m_force;

    vector<SObject*> m_objects;
public:
    System();
    ~System();

    void addObject(SObject *object) { m_objects.push_back(object); }
    void update(const double timestep);

    void forceStationarySun(bool forceStationary);
    void resetForces();
    void calculateForces();
    void updateEnergies();
    void storePerihelionValues(bool storePerihelion);

    void setIntegrator(Integrator *integrator) { m_integrator = integrator; }
    void setForce(Force *force) { m_force = force; }

    void removeTotalMomentum();
    void checkTotalMomentum();

    vector<SObject*> &objects() { return m_objects; }
};

#endif // SYSTEM_H
