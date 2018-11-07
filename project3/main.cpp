#include <iostream>
#include <cmath>
#include "system.h"
#include "integrators/forwardeuler.h"
#include "integrators/velocityverlet.h"
#include "integrators/eulercromer.h"
#include "resultstorer.h"
#include "force/newtoniangravity.h"
#include "force/modifiedgravity.h"
#include "force/newtoniangravitycorrected.h"


using namespace std;

int main()
{
    double time_normalization = 365.25;

    // Sun
    vec3 sun_pos = { -5.919155772743485E-04,  7.385542274920093E-03, -6.154229355980155E-05};
    vec3 sun_vel = {-7.757658457453950E-06,  2.141834870050543E-06,  1.962698872807737E-07};
    sun_vel *= time_normalization; // since [v] = [au/day]
    double sun_mass = 11988500e24;
    SObject *sunObj = new SObject(sun_pos, sun_vel, 1.0, "sun");

    sun_pos = {0,0,0};
    sun_vel = {0,0,0};
    SObject *sunObjBasic = new SObject(sun_pos, sun_vel, 1.0, "sun");

    // Mercury
    vec3 mercury_pos = {-2.830259311829709E-01, 1.999944216677920E-01, 4.158711313644133E-02};
    vec3 mercury_vel = {-2.161187944929931E-02, -2.207233009714748E-02, 1.783325912551766E-04};
    mercury_vel *= time_normalization;
    double mercury_mass = 3.302e23;
    mercury_mass /= sun_mass;
    SObject *mercuryObj = new SObject(mercury_pos, mercury_vel, mercury_mass, "mercury");

    vec3 mercury_pos_prec = {0.3075, 0, 0};
    vec3 mercury_vel_prec = {0, 12.44, 0};
    SObject *mercuryObjPrecession = new SObject(mercury_pos_prec, mercury_vel_prec, mercury_mass, "mercury");


    // Venus
    vec3 venus_pos = {-1.979804002020823E-01,  6.983650310789559E-01, 2.081035900640404E-02};
    vec3 venus_vel = {-1.952418772472886E-02, -5.665705836375252E-03,  1.048675733150797E-03};
    venus_vel *= time_normalization; // since [v] = [au/day]
    double venus_mass = 48.685e23;
    venus_mass /= sun_mass;
    SObject *venusObj = new SObject(venus_pos, venus_vel, venus_mass, "venus");

    // Earth
    vec3 earth_pos = {7.568866818711384E-01, 6.483949789024712E-01, -1.019825122556535E-04};
    vec3 earth_vel = {-1.140300222458833E-02, 1.307463198392195E-02, -8.646472327809290E-07};
    earth_vel *= time_normalization; // since [v] = [au/day]
    double earth_mass = 5.97219e24;
    earth_mass /= sun_mass;
    SObject *earthObj = new SObject(earth_pos, earth_vel, earth_mass, "earth");

    earth_pos = {1,0,0};
    earth_vel = {0,2*M_PI,0};
    SObject *earthObjBasic = new SObject(earth_pos, earth_vel, earth_mass, "earth");

    // Mars
    vec3 mars_pos = {1.388769709785988E+00, 1.556244779300845E-01, -3.104556796346191E-02};
    vec3 mars_vel = {-9.586334259664849E-04, 1.511271999086297E-02, 3.401500099368581E-04};
    mars_vel *= time_normalization; // since [v] = [au/day]
    double mars_mass = 6.4171e23;
    mars_mass /= sun_mass;
    SObject *marsObj = new SObject(mars_pos, mars_vel, mars_mass, "mars");

    // Jupiter
    vec3 jupiter_pos = {-2.530234099776776E+00, -4.724912151622468E+00, 7.619427020895447E-02};
    vec3 jupiter_vel = {6.563190638070959E-03, -3.202416923549941E-03, -1.334759412082958E-04};
    jupiter_vel *= time_normalization; // since [v] = [au/day]
    double jupiter_mass = 1898.13e24;
    jupiter_mass /= sun_mass;
    SObject *jupiterObj = new SObject(jupiter_pos, jupiter_vel, jupiter_mass, "jupiter");

    // Saturn
    vec3 saturn_pos = {  1.850242332516125E+00, -9.881522337036836E+00,  9.816416616683857E-02};
    vec3 saturn_vel = {5.176955755662489E-03,  1.009140386167208E-03, -2.236909273787052E-04};
    saturn_vel *= time_normalization; // since [v] = [au/day]
    double saturn_mass = 5.6834e26;
    saturn_mass /= sun_mass;
    SObject *saturnObj = new SObject(saturn_pos, saturn_vel, saturn_mass, "saturn");

    // Uranus
    vec3 uranus_pos = {1.705839546641438E+01,  1.018354541295799E+01, -1.831717748605908E-01};
    vec3 uranus_vel = {-2.044898236053100E-03,  3.193771066110533E-03,  3.841503574618114E-05};
    uranus_vel *= time_normalization; // since [v] = [au/day]
    double uranus_mass = 86.813e24;
    uranus_mass /= sun_mass;
    SObject *uranusObj = new SObject(uranus_pos, uranus_vel, uranus_mass, "uranus");

    // Neptune
    vec3 neptune_pos = { 2.896552399030275E+01, -7.545409155038740E+00, -5.121563515019911E-01};
    vec3 neptune_vel = {7.701585398168282E-04,  3.056586272651174E-03, -8.029789856472037E-05};
    neptune_vel *= time_normalization; // since [v] = [au/day]
    double neptune_mass = 102.413e24;
    neptune_mass /= sun_mass;
    SObject *neptuneObj = new SObject(neptune_pos, neptune_vel, neptune_mass, "neptune");

    // Pluto
    vec3 pluto_pos = {1.181856182332348E+01, -3.155008973446227E+01, -4.257843132576340E-02};
    vec3 pluto_vel = {3.008268496778462E-03,  4.309136659867673E-04, -9.289217919459634E-04};
    pluto_vel *= time_normalization; // since [v] = [au/day]
    double pluto_mass = 1.307e23;
    pluto_mass /= sun_mass;
    SObject *plutoObj = new SObject(pluto_pos, pluto_vel, pluto_mass, "pluto");


    // Specifies the number of steps, time to run for and step size
    unsigned long NSteps = 10000000;
    double T = 100; // Time, years
    double h = T / double(NSteps);

    // Specify run name here
    string runName = "relativistic_run";

    // Creates our system
    System S;

    // New objects
//    S.addObject(sunObjBasic);
//    S.addObject(earthObjBasic);

    // Mercury precession
    S.addObject(sunObjBasic);
    S.addObject(mercuryObjPrecession);

//    S.addObject(sunObj);
//    S.addObject(earthObj);
//    S.addObject(mercuryObj);
//    S.addObject(venusObj);
//    S.addObject(marsObj);
//    S.addObject(jupiterObj);
//    S.addObject(saturnObj);
//    S.addObject(uranusObj);
//    S.addObject(neptuneObj);
//    S.addObject(plutoObj);

    double G = 4*M_PI*M_PI;

//    ForwardEuler *integrator = new ForwardEuler;
//    EulerCromer *integrator = new EulerCromer;
    VelocityVerlet *integrator = new VelocityVerlet;

//    NewtonianGravity *force = new NewtonianGravity(G);
//    ModifiedGravity *force = new ModifiedGravity(G);
//    force->setBeta(3);
    NewtonianGravityCorrected *force = new NewtonianGravityCorrected(G);

    // Analytic escape velocity: sqrt(2*G*M/r0)

    S.removeTotalMomentum();

    S.setIntegrator(integrator);
    S.setForce(force);

    ResultStorer res(&S, NSteps+1);

    // Push initial positions and velocities to file.
    S.updateEnergies();
    res.pushResults(&S, 0);


    // Prints start position
    S.objects()[1]->printObject();

    for (unsigned int i = 0; i<NSteps;i++) {
        // Integrate system one step ahead
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
