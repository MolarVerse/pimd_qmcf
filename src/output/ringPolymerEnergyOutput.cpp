/*****************************************************************************
<GPL_HEADER>

    PIMD-QMCF
    Copyright (C) 2023-now  Jakob Gamper

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

<GPL_HEADER>
******************************************************************************/

#include "ringPolymerEnergyOutput.hpp"

#include "physicalData.hpp"   // for PhysicalData
#include "stlVector.hpp"      // for sum

#include <algorithm>   // for for_each
#include <format>      // for format
#include <vector>      // for vector

using namespace output;

/**
 * @brief write the energy output of each ring polymer
 *
 * @details
 * 1) step
 * 2) sum of all ring polymer spring energies
 * 3) ... 2+n) ring polymer spring energies
 *
 * @param step
 * @param loopTime
 * @param data
 */
void RingPolymerEnergyOutput::write(const size_t step, const physicalData::PhysicalData &data)
{
    _fp << std::format("{:10d}\t", step);

    _fp << std::format("{:20.12f}\t", sum(data.getRingPolymerEnergy()));

    std::ranges::for_each(data.getRingPolymerEnergy(), [&](const double &energy) { _fp << std::format("{:20.12f}\t", energy); });

    _fp << '\n' << std::flush;

    _fp << std::flush;
}