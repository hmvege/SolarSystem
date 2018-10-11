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

