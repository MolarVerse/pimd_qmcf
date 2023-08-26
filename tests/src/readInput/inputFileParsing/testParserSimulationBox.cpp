#include "exceptions.hpp"
#include "inputFileParserSimulationBox.hpp"
#include "simulationBoxSettings.hpp"
#include "testInputFileReader.hpp"
#include "throwWithMessage.hpp"

using namespace std;
using namespace readInput;
using namespace ::testing;

/**
 * @brief tests parsing the "density" command
 */
TEST_F(TestInputFileReader, testParseDensity)
{
    EXPECT_EQ(settings::SimulationBoxSettings::getDensitySet(), false);
    InputFileParserSimulationBox parser(_engine);
    const vector<string>         lineElements = {"density", "=", "1.0"};
    parser.parseDensity(lineElements, 0);
    EXPECT_EQ(_engine.getSimulationBox().getDensity(), 1.0);
    EXPECT_EQ(settings::SimulationBoxSettings::getDensitySet(), true);

    const vector<string> lineElements2 = {"density", "=", "-1.0"};
    EXPECT_THROW_MSG(
        parser.parseDensity(lineElements2, 0), customException::InputFileException, "Density must be positive - density = -1");
}

/**
 * @brief tests parsing the "rcoulomb" command
 *
 * @details if the rcoulomb is negative it throws inputFileException
 *
 */
TEST_F(TestInputFileReader, testParseCoulombRadius)
{
    InputFileParserSimulationBox parser(_engine);
    const vector<string>         lineElements = {"rcoulomb", "=", "1.0"};
    parser.parseCoulombRadius(lineElements, 0);
    EXPECT_EQ(_engine.getSimulationBox().getCoulombRadiusCutOff(), 1.0);

    const vector<string> lineElements2 = {"rcoulomb", "=", "-1.0"};
    EXPECT_THROW_MSG(parser.parseCoulombRadius(lineElements2, 0),
                     customException::InputFileException,
                     "Coulomb radius cutoff must be positive - \"-1.0\" at line 0 in input file");
}

int main(int argc, char **argv)
{
    InitGoogleTest(&argc, argv);
    return ::RUN_ALL_TESTS();
}