#include "intraNonBonded.hpp"

#include "exceptions.hpp"
#include "simulationBox.hpp"

#include <algorithm>   // for for_each
#include <format>      // for format
#include <ranges>      // for ranges::find_if

using namespace std;
using namespace intraNonBonded;

/**
 * @brief find a intraNonBondedContainer by molType and return a pointer to it
 *
 * @param molType
 * @return IntraNonBondedContainer*
 */
IntraNonBondedContainer *IntraNonBonded::findIntraNonBondedContainerByMolType(const size_t molType)
{
    auto findByMolType = [molType](const auto &intraNonBondedType) { return intraNonBondedType.getMolType() == molType; };
    if (const auto it = ranges::find_if(_intraNonBondedContainers, findByMolType); it != _intraNonBondedContainers.end())
        return std::to_address(it);
    else
        throw customException::IntraNonBondedException(format("IntraNonBondedContainer with molType {} not found!", molType));
}

/**
 * @brief fill the _intraNonBondedMaps vector with IntraNonBondedMap objects
 *
 * @param box
 */
void IntraNonBonded::fillIntraNonBondedMaps(simulationBox::SimulationBox &box)
{
    auto fillSingleMap = [this](auto &molecule)
    {
        auto *intraNonBondedContainer = findIntraNonBondedContainerByMolType(molecule.getMoltype());
        _intraNonBondedMaps.push_back(IntraNonBondedMap(&molecule, intraNonBondedContainer));
    };

    ranges::for_each(box.getMolecules(), fillSingleMap);
}

void IntraNonBonded::calculate(simulationBox::SimulationBox &box, physicalData::PhysicalData &physicalData)
{
    for (auto &intraNonBondedMap : _intraNonBondedMaps)
        intraNonBondedMap.calculate(_coulombPotential.get(), _nonCoulombPotential.get(), box, physicalData);
}