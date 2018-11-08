#include "resultstorer.h"
#include <fstream>
#include <iomanip>
#include <iostream>

using std::cout;
using std::endl;

ResultStorer::ResultStorer() {

}

ResultStorer::ResultStorer(System *S, unsigned long NSteps)
{
    initialize(S, NSteps);
}

ResultStorer::~ResultStorer()
{

}

void ResultStorer::initialize(System *S, unsigned long NSteps)
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
    m_kineticEnergies.resize(m_NTotElements);
    m_potentialEnergies.resize(m_NTotElements);
    m_angularMomentum.resize(m_NTotElements);

    // Pushes the correct names to the vector
    for (unsigned long iObj = 0; iObj < m_NObjects; iObj++) {
        m_objectNames[iObj] = S->objects()[iObj]->name;
    }
}

void ResultStorer::pushResults(System *S, unsigned long iStep)
{
    /*
     * Function for updating the results
     */
    for (unsigned long iObj = 0; iObj < m_NObjects; iObj++) {
        m_positions[getIndex(iStep, iObj)] = S->objects()[iObj]->position;
        m_velocities[getIndex(iStep, iObj)] = S->objects()[iObj]->velocity;
        m_kineticEnergies[getIndex(iStep, iObj)] = S->objects()[iObj]->kineticEnergy;
        m_potentialEnergies[getIndex(iStep, iObj)] = S->objects()[iObj]->potentialEnergy;
        m_angularMomentum[getIndex(iStep, iObj)] = S->objects()[iObj]->angularMomentum;
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
        string filename = "../data/" + runName + "_" + m_objectNames[iObj] + "_orbital_data.bin";

        // Opens a file to write with
        file.open(filename, std::ofstream::binary);

        writeArrayToFile(file, m_positions, iObj);
        writeArrayToFile(file, m_velocities, iObj);
        writeArrayToFile(file, m_angularMomentum, iObj);
        writeArrayToFile(file, m_kineticEnergies, iObj);
        writeArrayToFile(file, m_potentialEnergies, iObj);

        // Closes file and prints a success message.
        file.close();
        cout << "File " << filename << " written" << endl;
    }

    // Reverst back to the old precision
    std::setprecision(int(oldPrecision));
}


void ResultStorer::writeArrayToFile(std::ofstream &file, std::vector<vec3> vec, unsigned long iObj)
{
    double *tmp_arr = new double[3*m_NSteps];
    for (int iStep = 0; iStep < m_NSteps; iStep++) {
        for (int j = 0; j < 3; j++) {
            tmp_arr[3*iStep + j] = vec[getIndex(iStep, iObj)][j];
        }
    }

    file.write(reinterpret_cast<const char*> (tmp_arr), 3*m_NSteps*sizeof(double));

    delete [] tmp_arr;
}

void ResultStorer::writeArrayToFile(std::ofstream &file, std::vector<double> vec, int iObj)
{
    double *tmp_arr = new  double[m_NSteps];
    for (int iStep = 0; iStep < m_NSteps; iStep++) {
        tmp_arr[iStep] = vec[getIndex(iStep, iObj)];
    }

    file.write(reinterpret_cast<const char*> (tmp_arr), m_NSteps*sizeof(double));

    delete [] tmp_arr;
}
