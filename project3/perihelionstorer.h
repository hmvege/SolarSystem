#ifndef PERIHELIONSTORER_H
#define PERIHELIONSTORER_H

#include <vector>
#include "math/vec3.h"
#include <string>

using std::vector;
using std::string;

struct PerihelionStorer {
public:
    PerihelionStorer() {}
    ~PerihelionStorer() {}

    vector <vec3> perhielionPosition;
    vector <vec3> perhielionVelocity;

    vec3 previousPreviousPos = {0,0,0};
    vec3 previousPos = {0,0,0};
    vec3 currentPos = {0,0,0};
};

#endif // PERIHELIONSTORER_H
