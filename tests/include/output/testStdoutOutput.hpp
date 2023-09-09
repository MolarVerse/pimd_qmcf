#ifndef _TEST_STDOUTOUTPUT_HPP_

#define _TEST_STDOUTOUTPUT_HPP_

#include "stdoutOutput.hpp"   // for StdoutOutput

#include <gtest/gtest.h>   // for Test
#include <memory>          // for allocator

/**
 * @class TestStdoutOutput
 *
 * @brief test suite for stdout output
 *
 */
class TestStdoutOutput : public ::testing::Test
{
  protected:
    void SetUp() override { _stdoutOutput = new output::StdoutOutput("stdout"); }

    void TearDown() override { delete _stdoutOutput; }

    output::StdoutOutput *_stdoutOutput;
};

#endif   // _TEST_STDOUTOUTPUT_HPP_