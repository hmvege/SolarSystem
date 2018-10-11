#include "vec3.h"

vec3::vec3()
{
}

vec3::vec3(double val)
{
    vec[0] = val;
    vec[1] = val;
    vec[2] = val;
}

vec3::vec3(double x, double y, double z)
{
    vec[0] = x;
    vec[1] = y;
    vec[2] = z;
}

vec3::vec3(vec3 const &copy)
{
    // Uncomment to see what methods is called when!
//    cout << "Using copy constructor" << endl;
    vec[0] = copy.vec[0];
    vec[1] = copy.vec[1];
    vec[2] = copy.vec[2];
}
