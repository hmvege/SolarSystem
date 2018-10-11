#ifndef RESULTSTORER_H
#define RESULTSTORER_H

#include <string>
#include "system.h"

class ResultStorer
{
private:
    unsigned long m_NObjects;
    unsigned long m_NSteps;
    unsigned long m_NTotElements;

    std::vector<vec3> m_positions;
    std::vector<vec3> m_velocities;
    std::vector<std::string> m_objectNames;

    inline unsigned long getIndex(unsigned long iStep, unsigned long iObj) {
        return iObj + m_NObjects*iStep;
//        return i + Ni*(j + Nj*k);
    }

public:
    ResultStorer(System *S, unsigned long NSteps);
    ~ResultStorer();

    void pushResults(System *S, unsigned long iStep);
    void writeToFile();
};

#endif // RESULTSTORER_H
