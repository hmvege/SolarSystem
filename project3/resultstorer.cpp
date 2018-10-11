#include "resultstorer.h"
#include <fstream>
#include <iomanip>
#include <iostream>

using std::cout;
using std::endl;

ResultStorer::ResultStorer(System *S, unsigned long NSteps)
{
    // Gets the number of objects
    m_NObjects = S->objects().size();

    // Number of integration steps
    m_NSteps = NSteps;

    // Total number of elements to store
    m_NTotElements = m_NSteps*m_NObjects*3;

    // Prepeares vectors for names, positions and velocities
    m_objectNames.resize(m_NObjects);
    m_positions.resize(m_NTotElements);
    m_velocities.resize(m_NTotElements);

    // Pushes the correct names to the vector
    for (unsigned long iObj = 0; iObj < m_NObjects; iObj++) {
        m_objectNames[iObj] = S->objects()[iObj]->name;
    }
}

ResultStorer::~ResultStorer()
{

}

void ResultStorer::pushResults(System *S, unsigned long iStep)
{
    /*
     * Function for updating the results
     */
    for (unsigned long iObj = 0; iObj < m_NObjects; iObj++) {
        m_positions[getIndex(iStep, iObj)] = S->objects()[iObj]->position;
        m_velocities[getIndex(iStep, iObj)] = S->objects()[iObj]->velocity;
    }
}

void ResultStorer::writeToFile(string runName)
{
    // Stores the old precision
    auto oldPrecision = std::cout.precision(15);

    for (unsigned long iObj = 0; iObj < m_NObjects; iObj++) {

        // Creates a new file object
        std::ofstream file;

        // Sets up the filename
        string filename = "../data/" + runName + "_" + m_objectNames[iObj] + "_orbital_data.txt";

        // Opens a file to write with
        file.open(filename);

        // Ensures we have a precision of 15 decimals
        file << std::fixed << std::setprecision(15);

        // Loops over results and stores them in 6 columns
        for (unsigned long iStep = 0; iStep < m_NSteps; iStep++) {

            for (unsigned long i = 0; i < 3; ++i) {
                file << m_positions.at(getIndex(iStep, iObj))[i] << " ";
            }

            for (unsigned long i = 0; i < 3; ++i) {
                file << m_velocities[getIndex(iStep, iObj)][i] << " ";
            }

            // Newline
            file << endl;
        }

        // Closes file and prints a success message.
        file.close();
        cout << "File " << filename << " written" << endl;
    }

    // Reverst back to the old precision
    std::setprecision(int(oldPrecision));
}
