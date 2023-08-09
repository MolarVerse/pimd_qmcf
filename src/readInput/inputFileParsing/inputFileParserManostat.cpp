#include "constants.hpp"
#include "inputFileParser.hpp"

#include <memory>

using namespace std;
using namespace readInput;
using namespace manostat;
using namespace customException;

/**
 * @brief Construct a new Input File Parser Manostat:: Input File Parser Manostat object
 *
 * @param engine
 */
InputFileParserManostat::InputFileParserManostat(engine::Engine &engine) : InputFileParser(engine)
{
    addKeyword(string("manostat"), bind_front(&InputFileParserManostat::parseManostat, this), false);
    addKeyword(string("pressure"), bind_front(&InputFileParserManostat::parsePressure, this), false);
    addKeyword(string("p_relaxation"), bind_front(&InputFileParserManostat::parseManostatRelaxationTime, this), false);
    addKeyword(string("compressibility"), bind_front(&InputFileParserManostat::parseCompressibility, this), false);
}

/**
 * @brief Parse the manostat used in the simulation
 *
 * @param lineElements
 */
void InputFileParserManostat::parseManostat(const vector<string> &lineElements, const size_t lineNumber)
{
    checkCommand(lineElements, lineNumber);
    if (lineElements[2] == "none")
    {
        _engine.makeManostat(Manostat());
        _engine.getSettings().setManostat("none");
    }
    else if (lineElements[2] == "berendsen")
    {
        _engine.makeManostat(BerendsenManostat());
        _engine.getSettings().setManostat("berendsen");
    }
    else
        throw InputFileException(format("Invalid manostat \"{}\" at line {} in input file", lineElements[2], lineNumber));
}

/**
 * @brief Parse the pressure used in the simulation
 *
 * @param lineElements
 */
void InputFileParserManostat::parsePressure(const vector<string> &lineElements, const size_t lineNumber)
{
    checkCommand(lineElements, lineNumber);
    _engine.getSettings().setPressure(stod(lineElements[2]));
}

/**
 * @brief parses the relaxation time of the manostat
 *
 * @param lineElements
 *
 * @throw InputFileException if relaxation time is negative
 */
void InputFileParserManostat::parseManostatRelaxationTime(const vector<string> &lineElements, const size_t lineNumber)
{
    checkCommand(lineElements, lineNumber);
    const auto relaxationTime = stod(lineElements[2]);

    if (relaxationTime < 0) throw InputFileException("Relaxation time of manostat cannot be negative");

    _engine.getSettings().setTauManostat(relaxationTime);
}

/**
 * @brief Parse the compressibility used in the simulation (isothermal compressibility)
 *
 * @param lineElements
 *
 * @throw InputFileException if compressibility is negative
 */
void InputFileParserManostat::parseCompressibility(const vector<string> &lineElements, const size_t lineNumber)
{
    checkCommand(lineElements, lineNumber);
    const auto compressibility = stod(lineElements[2]);
    if (compressibility < 0.0)
        throw InputFileException(
            format("Invalid compressibility \"{}\" at line {} in input file - has to be positive", lineElements[2], lineNumber));

    _engine.getSettings().setCompressibility(compressibility);
}