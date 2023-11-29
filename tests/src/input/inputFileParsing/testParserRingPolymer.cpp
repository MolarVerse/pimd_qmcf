#include "inputFileParserRingPolymer.hpp"
#include "ringPolymerSettings.hpp"
#include "testInputFileReader.hpp"
#include "throwWithMessage.hpp"

#include "gtest/gtest.h"   // for Message, TestPartResult

using input::InputFileParserRingPolymer;

/**
 * @brief tests parsing the "rpmd_n_replica" command
 *
 */
TEST_F(TestInputFileReader, parseNumberOfBeads)
{
    InputFileParserRingPolymer parser(*_engine);
    std::vector<std::string>   lineElements = {"rpmd_n_replica", "=", "3"};
    parser.parseNumberOfBeads(lineElements, 0);
    EXPECT_EQ(settings::RingPolymerSettings::getNumberOfBeads(), 3);

    lineElements = {"rpmd_n_replica", "=", "1"};
    EXPECT_THROW_MSG(parser.parseNumberOfBeads(lineElements, 0),
                     customException::InputFileException,
                     "Number of beads must be at least 2 - in input file in line 0");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return ::RUN_ALL_TESTS();
}