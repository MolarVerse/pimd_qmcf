#ifndef _ENERGY_OUTPUT_HPP_

#define _ENERGY_OUTPUT_HPP_

#include "output.hpp"   // for Output

#include <cstddef>   // for size_t

namespace physicalData
{
    class PhysicalData;   // forward declaration
}

namespace output
{
    /**
     * @class EnergyOutput inherits from Output
     *
     * @brief Output file for energy, temperature and pressure
     *
     */
    class EnergyOutput : public Output
    {
      public:
        using Output::Output;

        void write(const size_t step, const physicalData::PhysicalData &);
    };

}   // namespace output

#endif   // _ENERGY_OUTPUT_HPP_