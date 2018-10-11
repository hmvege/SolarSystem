#include "system.h"
#include <cmath>

#include <iostream>

System::System()
{
    m_G = 4*M_PI*M_PI;
}

System::~System() {
    for(SObject *obj : m_objects) {
        delete obj;
    }
    m_objects.clear();
}

void System::resetForces() {
    for (SObject *obj : m_objects) {
        obj->force = {0,0,0};
    }
}

void System::calculateForces() {
    double r = 0;
    vec3 r_temp(0, 0, 0);
    vec3 force_temp(0, 0, 0);

    resetForces();

    // Just a single planet: Earth-sun
    // Calculates the squared
//    r_temp = m_objects[1]->position - m_objects[0]->position;
//    r = sqrt(r_temp.length());

    // Sets forces from object j on i
//    m_objects[1]->force = 0;
//    m_objects[1]->force += r_temp / (r*r*r) * (- m_G) * m_objects[0]->mass * m_objects[1]->mass / m_sunMass;
//    m_objects[1]->force += r_temp / (r*r*r) * (- m_G);

    // Uses N3L and sets forces from object i on j
//    m_objects[0]->force += m_objects[1]->force * (-1);

    // Calculates forces between iObj and all other objects in system
    for (unsigned int iObj = 0; iObj < m_objects.size(); iObj++) {
        for (unsigned int jObj = iObj + 1; jObj < m_objects.size(); jObj++) {

            // Calculates the distance between object i and j
            r_temp = m_objects[iObj]->position - m_objects[jObj]->position;
            r = sqrt(r_temp.length());

            // Sets forces from object j on i
            force_temp = r_temp / (r*r*r) * (-m_G) * (m_objects[iObj]->mass * m_objects[jObj]->mass / m_sunMass);
            m_objects[iObj]->force += force_temp;

            // Uses N3L and sets forces from object i on j
            m_objects[jObj]->force -= force_temp;

        }
    }
}
