#ifndef _ANALYSIS_HPP_

#define _ANALYSIS_HPP_

#include <vector>
#include <string>

#include "frame.hpp"

class AnalysisRunner
{
protected:
    std::string _inputFilename;

public:
    AnalysisRunner() = default;

    virtual void setup() = 0;
    virtual void run() = 0;
};

#endif // _ANALYSIS_HPP_