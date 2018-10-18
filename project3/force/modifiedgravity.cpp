#include "modifiedgravity.h"
#include "sobject.h"


ModifiedGravity::ModifiedGravity()
{

}

ModifiedGravity::ModifiedGravity(double G) : m_G(G)
{

}

ModifiedGravity::~ModifiedGravity()
{
}

void ModifiedGravity::calculateForces(System *system)
{
    /*
     * Takes the system class and calculates forces between the objects
     */

    // Distance, temporary distance vector and temporary force vector
    double r = 0;
    double rbeta = 0;
    vec3 r_temp(0, 0, 0);
    vec3 force_temp(0, 0, 0);

    // Calculates forces between all objects
    for (unsigned int iObj = 0; iObj < system->objects().size(); iObj++) {
        for (unsigned int jObj = iObj + 1; jObj < system->objects().size(); jObj++) {

            // Calculates the distance between object i and j
            r_temp = system->objects()[iObj]->position - system->objects()[jObj]->position;
            r = r_temp.length();
            rbeta = pow(r, m_beta);

            // Sets forces from object j on i
            force_temp = r_temp / rbeta * (-m_G) * (system->objects()[iObj]->mass * system->objects()[jObj]->mass);
            system->objects()[iObj]->force += force_temp;

            // Uses N3L and sets forces from object i on j
            system->objects()[jObj]->force -= force_temp;

        }
    }
}

void ModifiedGravity::calculatePotentialEnergy(System *system)
{
    // Temporary distance vector defined as r = |x_i - x_j|
    vec3 distance = {0,0,0};

    for (SObject *iobj : system->objects())
    {
        // Resets potential energy
        iobj->potentialEnergy = 0;

        // Sums up all of the potential energy contributions
        for (SObject *jobj : system->objects())
        {
            if (iobj == jobj) continue;
            distance = iobj->position - jobj->position;
            iobj->potentialEnergy += (-1)*m_G * jobj->mass / pow(distance.length(), m_beta-2) / (-(m_beta-2));
        }
    }
}
