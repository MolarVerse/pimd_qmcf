#include "engine.hpp"                   // for Engine
#include "exceptions.hpp"               // for InputFileException
#include "inputFileParser.hpp"          // for readInput
#include "inputFileParserGeneral.hpp"   // for InputFileParserGeneral
#include "mmmdEngine.hpp"               // for MMMDEngine
#include "qmmdEngine.hpp"               // for QMMDEngine
#include "settings.hpp"                 // for Settings
#include "testInputFileReader.hpp"      // for TestInputFileReader
#include "throwWithMessage.hpp"         // for EXPECT_THROW_MSG

#include "gtest/gtest.h"   // for Message, TestPartResult
#include <gtest/gtest.h>   // for InitGoogleTest, RUN_ALL_TESTS
#include <memory>          // for unique_ptr
#include <string>          // for string, allocator, basic_string
#include <vector>          // for vector

using namespace readInput;

/**
 * @brief tests parsing the "jobtype" command
 *
 * @details if the jobtype is not valid it throws inputFileException - possible jobtypes are: mm-md
 *
 */
TEST_F(TestInputFileReader, JobType)
{
    InputFileParserGeneral   parser(*_engine);
    std::vector<std::string> lineElements = {"jobtype", "=", "mm-md"};
    auto                     engine       = std::unique_ptr<engine::Engine>();
    parser.parseJobTypeForEngine(lineElements, 0, engine);
    EXPECT_EQ(settings::Settings::getJobtype(), "MMMD");
    EXPECT_EQ(settings::Settings::isMMActivated(), true);
    EXPECT_EQ(typeid(*engine), typeid(engine::MMMDEngine));

    lineElements = {"jobtype", "=", "qm-md"};
    parser.parseJobTypeForEngine(lineElements, 0, engine);
    EXPECT_EQ(settings::Settings::getJobtype(), "QMMD");
    EXPECT_EQ(settings::Settings::isQMActivated(), true);
    EXPECT_EQ(typeid(*engine), typeid(engine::QMMDEngine));

    lineElements = {"jobtype", "=", "notValid"};
    EXPECT_THROW_MSG(parser.parseJobTypeForEngine(lineElements, 0, engine),
                     customException::InputFileException,
                     "Invalid jobtype \"notValid\" in input file - possible values are: mm-md, qm-md");

    EXPECT_NO_THROW(parser.parseJobType(lineElements, 0));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return ::RUN_ALL_TESTS();
}