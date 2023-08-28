#include "inputFileParserIntegrator.hpp"

#include "engine.hpp"       // for Engine
#include "exceptions.hpp"   // for InputFileException, customException
#include "integrator.hpp"   // for VelocityVerlet, integrator

#include <cstddef>      // for size_t
#include <format>       // for format
#include <functional>   // for _Bind_front_t, bind_front

using namespace readInput;

/**
 * @brief Construct a new Input File Parser Integrator:: Input File Parser Integrator object
 *
 * @details following keywords are added to the _keywordFuncMap, _keywordRequiredMap and _keywordCountMap:
 * 1) integrator <string>
 *
 * @param engine
 */
InputFileParserIntegrator::InputFileParserIntegrator(engine::Engine &engine) : InputFileParser(engine)
{
    addKeyword(std::string("integrator"), bind_front(&InputFileParserIntegrator::parseIntegrator, this), false);
}

/**
 * @brief Parse the integrator used in the simulation
 *
 * @details Possible options are:
 * 1) "v-verlet"  - velocity verlet integrator is used (default)
 *
 * @param lineElements
 *
 * @throws customException::InputFileException if integrator is not valid - currently only velocity verlet is supported
 */
void InputFileParserIntegrator::parseIntegrator(const std::vector<std::string> &lineElements, const size_t lineNumber)
{
    checkCommand(lineElements, lineNumber);
    if (lineElements[2] == "v-verlet")
        _engine.makeIntegrator(integrator::VelocityVerlet());
    else
        throw customException::InputFileException(
            format("Invalid integrator \"{}\" at line {} in input file", lineElements[2], lineNumber));
}