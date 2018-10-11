#include <iostream>
#include "system.h"
#include "integrators/forwardeuler.h"
//#include "integrators/integrator.h"
#include "resultstorer.h"
#include "force/newtoniangravity.h"

#include <cmath>

using namespace std;

int main()
{
    double time_normalization = 365.25;

    // Sun
    vec3 sun_pos = {-2.996929750308121E-04, 7.299007490141281E-03, -6.887565019562871E-05};
    vec3 sun_vel = {-7.635678308544194E-06, 2.420578297394992E-06, 1.909523923438376E-07};
//    vec3 sun_pos = {0,0,0};
//    vec3 sun_vel = {0,0,0};
    sun_vel *= time_normalization; // since [v] = [au/day]
    double sun_mass = 1988500e24;
    SObject *sunObj = new SObject(sun_pos, sun_vel, sun_mass, "sun");

    // Earth
    vec3 earth_pos = {7.568866818711384E-01, 6.483949789024712E-01, -1.019825122556535E-04};
    vec3 earth_vel = {-1.140300222458833E-02, 1.307463198392195E-02, -8.646472327809290E-07};
//    vec3 earth_pos = {1,0,0};
//    vec3 earth_vel = {0,2*M_PI,0};
    earth_vel *= time_normalization; // since [v] = [au/day]
    double earth_mass = 5.97219e24;
    SObject *earthObj = new SObject(earth_pos, earth_vel, earth_mass, "earth");

    // Juptier
    vec3 jupiter_pos = {-2.530234099776776E+00, -4.724912151622468E+00, 7.619427020895447E-02};
    vec3 jupiter_vel = {6.563190638070959E-03, -3.202416923549941E-03, -1.334759412082958E-04};
    jupiter_vel *= time_normalization; // since [v] = [au/day]
    double jupiter_mass = 1898.13e24;
    SObject *jupiterObj = new SObject(jupiter_pos, jupiter_vel, jupiter_mass, "jupiter");


    // Mars
    vec3 mars_pos = {1.388769709785988E+00, 1.556244779300845E-01, -3.104556796346191E-02};
    vec3 mars_vel = {-9.586334259664849E-04, 1.511271999086297E-02, 3.401500099368581E-04};
    mars_vel *= time_normalization; // since [v] = [au/day]
    double mars_mass = 6.4171e23;
    SObject *marsObj = new SObject(mars_pos, mars_vel, mars_mass, "mars");

    // Specifies the number of steps, time to run for and step size
    unsigned long NSteps = 100;
    double T = 1; // Time, years
    double h = T / double(NSteps);

    // Specify run name here
    string runName = "systemrun1";

    // Creates our system
    System S;

    // New objects
    S.addObject(sunObj);
    S.addObject(earthObj);
    S.addObject(marsObj);
    S.addObject(jupiterObj);

    double G = 4*M_PI*M_PI;
    double sunMass = 1988500e24;

    ForwardEuler *integrator = new ForwardEuler;
    NewtonianGravity *force = new NewtonianGravity(G, sunMass);

    S.setIntegrator(integrator);
    S.setForce(force);

    ResultStorer res(&S, NSteps+1);

    // Push initial positions and velocities to file.
    res.pushResults(&S, 0);

    // Prints start position
    S.objects()[1]->printObject();

    for (unsigned int i = 0; i<NSteps;i++) {
        // Resets old forces
//        S.resetForces();

        // Calculate forces
//        force->calculateForces(&S);

        // Integrate system one step ahead
//        integrator->integrate(&S, h);
        S.update(h);

        // Pushes new results in
        res.pushResults(&S, i + 1);
    }

    // Prints final position to ensure it is the same as the start position
    S.objects()[1]->printObject();

    // Writes the results to file
    res.writeToFile(runName);

    return 0;
}
