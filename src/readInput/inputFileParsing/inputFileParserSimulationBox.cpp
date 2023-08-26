#include "inputFileParserSimulationBox.hpp"

#include "engine.hpp"                  // for Engine
#include "exceptions.hpp"              // for InputFileException, customException
#include "simulationBox.hpp"           // for SimulationBox
#include "simulationBoxSettings.hpp"   // for setDensitySet

#include <cstddef>      // for size_t
#include <format>       // for format
#include <functional>   // for _Bind_front_t, bind_front

using namespace std;
using namespace readInput;
using namespace customException;

/**
 * @brief Construct a new Input File Parser Simulation Box:: Input File Parser Simulation Box object
 *
 * @param engine
 */
InputFileParserSimulationBox::InputFileParserSimulationBox(engine::Engine &engine) : InputFileParser(engine)
{
    addKeyword(string("rcoulomb"), bind_front(&InputFileParserSimulationBox::parseCoulombRadius, this), false);
    addKeyword(string("density"), bind_front(&InputFileParserSimulationBox::parseDensity, this), false);
}

/**
 * @brief parses the coulomb cutoff radius
 *
 * @param lineElements
 *
 * @throw InputFileException if the cutoff radius is negative
 */
void InputFileParserSimulationBox::parseCoulombRadius(const vector<string> &lineElements, const size_t lineNumber)
{
    checkCommand(lineElements, lineNumber);

    const auto cutOff = stod(lineElements[2]);

    if (cutOff < 0.0)
        throw InputFileException(
            format("Coulomb radius cutoff must be positive - \"{}\" at line {} in input file", lineElements[2], lineNumber));

    _engine.getSimulationBox().setCoulombRadiusCutOff(cutOff);
}

/**
 * @brief parse density of simulation and set it in simulation box
 *
 * @param lineElements
 *
 * @throw InputFileException if the density is negative
 */
void InputFileParserSimulationBox::parseDensity(const vector<string> &lineElements, const size_t lineNumber)
{
    checkCommand(lineElements, lineNumber);

    const auto density = stod(lineElements[2]);

    if (density < 0.0)
        throw InputFileException(format("Density must be positive - density = {}", density));

    settings::SimulationBoxSettings::setDensitySet(true);
    _engine.getSimulationBox().setDensity(density);
}