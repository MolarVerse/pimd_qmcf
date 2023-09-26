#ifndef _STDOUT_OUTPUT_HPP_

#define _STDOUT_OUTPUT_HPP_

#include "output.hpp"

namespace output
{
    /**
     * @class StdoutOutput inherits from Output
     *
     * @brief Output file for stdout
     *
     */
    class StdoutOutput : public Output
    {
      public:
        using Output::Output;

        void writeHeader() const;
        void writeEndedNormally(const double elapsedTime) const;

        void writeDensityWarning() const;
    };

}   // namespace output

#endif   // _STDOUT_OUTPUT_HPP_