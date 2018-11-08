#include "newtoniangravitycorrected.h"
#include "sobject.h"


NewtonianGravityCorrected::NewtonianGravityCorrected()
{

}

NewtonianGravityCorrected::NewtonianGravityCorrected(double G) : m_G(G)
{

}

NewtonianGravityCorrected::~NewtonianGravityCorrected()
{
}

void NewtonianGravityCorrected::calculateForces(System *system)
{
    /*
     * Takes the system class and calculates forces between the objects
     */

    // Distance, temporary distance vector and temporary force vector
    double r = 0;
    vec3 r_temp(0, 0, 0);
    vec3 force_temp(0, 0, 0);

    // Relativistic correction variables
    double relativistic_correction = 0;
    double angular_momentum_squared = 0;
    /*
     * >>> c = 299792458
     * >>> au = 149597871000
     * >>> yr = 31556926
     * >>> c / au * yr
     * 63239.726268992876
     */
    double c = 63239.726268992876;

    // Calculates forces between all objects
    for (unsigned int iObj = 0; iObj < system->objects().size(); iObj++) {
        for (unsigned int jObj = iObj + 1; jObj < system->objects().size(); jObj++) {

            // Calculates the distance between object i and j
            r_temp = system->objects()[iObj]->position - system->objects()[jObj]->position;
            r = r_temp.length();

            // Relativistic correction
            angular_momentum_squared = cross(r_temp, system->objects()[jObj]->velocity).lengthSquared();
            relativistic_correction = 3*angular_momentum_squared / (r*r*c*c);

//            std::cout << system->objects()[iObj]->position << " " << system->objects()[iObj]->velocity << angular_momentum_squared << " " << relativistic_correction  << std::endl;
//            printf("%.16f %.16f\n", relativistic_correction, angular_momentum_squared);

            // Sets forces from object j on i
            force_temp = r_temp / (r*r*r) * (-m_G) * (system->objects()[iObj]->mass * system->objects()[jObj]->mass);
            force_temp *= (1 + relativistic_correction);
            system->objects()[iObj]->force += force_temp;

            // Uses N3L and sets forces from object i on j
            system->objects()[jObj]->force -= force_temp;

        }
    }
}

void NewtonianGravityCorrected::calculatePotentialEnergy(System *system)
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
            iobj->potentialEnergy += (-1)*m_G * jobj->mass / distance.length();
        }
    }
}
