#include "setup.hpp"

#include "celllistSetup.hpp"
#include "constraintsSetup.hpp"
#include "forceFieldSetup.hpp"
#include "guffDatReader.hpp"
#include "inputFileReader.hpp"
#include "integratorSetup.hpp"
#include "intraNonBondedReader.hpp"
#include "manostatSetup.hpp"
#include "moldescriptorReader.hpp"
#include "parameterFileReader.hpp"
#include "potentialSetup.hpp"
#include "resetKineticsSetup.hpp"
#include "rstFileReader.hpp"
#include "simulationBoxSetup.hpp"
#include "thermostatSetup.hpp"
#include "topologyReader.hpp"

#include <iostream>

using namespace std;
using namespace engine;
using namespace readInput;

/**
 * @brief setup the engine
 *
 * @param inputFilename
 * @param engine
 */
void setup::setupSimulation(const string &inputFilename, Engine &engine)
{
    readFiles(inputFilename, engine);

    cout << "setup engine..." << endl;
    setupEngine(engine);

    // needs setup of engine before reading guff.dat
    cout << "Reading guff.dat..." << endl;
    readGuffDat(engine);

    cout << "Setup complete!" << endl;
}

/**
 * @brief reads all the files needed for the simulation
 *
 * @param inputFilename
 * @param engine
 */
void setup::readFiles(const string &inputFilename, Engine &engine)
{
    cout << "Reading input file..." << endl;
    readInputFile(inputFilename, engine);

    cout << "Reading moldescriptor..." << endl;
    readMolDescriptor(engine);

    cout << "Reading rst file..." << endl;
    readRstFile(engine);

    cout << "Reading topology file..." << endl;
    topology::readTopologyFile(engine);

    cout << "Reading parameter file..." << endl;
    parameterFile::readParameterFile(engine);

    cout << "Reading intra non bonded file..." << endl;
    readIntraNonBondedFile(engine);
}

/**
 * @brief setup the engine
 *
 * @param engine
 */
void setup::setupEngine(Engine &engine)
{
    setupSimulationBox(engine);
    setupCellList(engine);
    setupThermostat(engine);
    setupManostat(engine);
    setupResetKinetics(engine);
    setupPotential(engine);
    setupIntegrator(engine);
    setupConstraints(engine);

    setupForceField(engine);   // important to setup force field after potential!!!
}