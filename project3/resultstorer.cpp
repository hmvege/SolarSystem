#include "resultstorer.h"
#include <fstream>
#include <iomanip>
#include <iostream>

ResultStorer::ResultStorer(System *S, unsigned long NSteps)
{
    m_NObjects = S->objects().size();
    m_NSteps = NSteps;
    m_NTotElements = m_NSteps*m_NObjects*3;

    m_objectNames.resize(m_NObjects);
    m_positions.resize(m_NTotElements);
    m_velocities.resize(m_NTotElements);
    for (unsigned long iObj = 0; iObj < m_NObjects; iObj++) {
        m_objectNames[iObj] = S->objects()[iObj]->name;
    }
}

ResultStorer::~ResultStorer()
{

}

void ResultStorer::pushResults(System *S, unsigned long iStep)
{
    for (unsigned long iObj = 0; iObj < m_NObjects; iObj++) {
        m_positions[getIndex(iStep, iObj)] = S->objects()[iObj]->position;
        m_velocities[getIndex(iStep, iObj)] = S->objects()[iObj]->velocity;
    }
}

void ResultStorer::writeToFile()
{
    auto oldPrecision = std::cout.precision(15);

    for (unsigned long iObj = 0; iObj < m_NObjects; iObj++) {
        std::ofstream file;
        std::string filename = "../data/" + m_objectNames[iObj] + "_orbital_data.txt";
        file.open(filename);
        file << std::fixed << std::setprecision(15);
        for (unsigned long iStep = 0; iStep < m_NSteps; iStep++) {

//            std::cout << iStep << " ";
            for (unsigned long i = 0; i < 3; ++i) {
                file << m_positions.at(getIndex(iStep, iObj))[i] << " ";
//                std::cout << m_positions[getIndex(iStep, iObj, i)] << " ";
            }

            for (unsigned long i = 0; i < 3; ++i) {
                file << m_velocities[getIndex(iStep, iObj)][i] << " ";
//                std::cout << m_velocities[getIndex(iStep, iObj, i)] << " ";
            }

//            std::cout << std::endl;
            file << std::endl;
        }
        std::cout << "File " << filename << " written" << std::endl;
        file.close();
    }

    std::setprecision(int(oldPrecision));
}
