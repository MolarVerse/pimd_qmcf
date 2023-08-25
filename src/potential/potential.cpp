#include "potential.hpp"

#include "coulombPotential.hpp"      // for CoulombPotential
#include "molecule.hpp"              // for Molecule
#include "nonCoulombPair.hpp"        // for NonCoulombPair
#include "nonCoulombPotential.hpp"   // for NonCoulombPotential

#include <cmath>

using namespace std;
using namespace simulationBox;
using namespace potential;
using namespace physicalData;
using namespace linearAlgebra;

/**
 * @brief inner part of the double loop to calculate non-bonded inter molecular interactions
 *
 * @param box
 * @param molecule1
 * @param molecule2
 * @param atom1
 * @param atom2
 * @return std::pair<double, double>
 */
std::pair<double, double> Potential::calculateSingleInteraction(const linearAlgebra::Vec3D &box,
                                                                simulationBox::Molecule    &molecule1,
                                                                simulationBox::Molecule    &molecule2,
                                                                const size_t                atom1,
                                                                const size_t                atom2) const
{
    auto coulombEnergy    = 0.0;
    auto nonCoulombEnergy = 0.0;

    const auto xyz_i = molecule1.getAtomPosition(atom1);
    const auto xyz_j = molecule2.getAtomPosition(atom2);

    auto dxyz = xyz_i - xyz_j;

    const auto txyz = -box * round(dxyz / box);

    // dxyz += txyz;
    dxyz[0] += txyz[0];
    dxyz[1] += txyz[1];
    dxyz[2] += txyz[2];

    const double distanceSquared = normSquared(dxyz);

    if (const auto RcCutOff = CoulombPotential::getCoulombRadiusCutOff(); distanceSquared < RcCutOff * RcCutOff)
    {
        const double distance   = ::sqrt(distanceSquared);
        const size_t atomType_i = molecule1.getAtomType(atom1);
        const size_t atomType_j = molecule2.getAtomType(atom2);

        const auto globalVdwType_i = molecule1.getInternalGlobalVDWType(atom1);
        const auto globalVdwType_j = molecule2.getInternalGlobalVDWType(atom2);

        const auto moltype_i = molecule1.getMoltype();
        const auto moltype_j = molecule2.getMoltype();

        const auto combinedIndices = {moltype_i, moltype_j, atomType_i, atomType_j, globalVdwType_i, globalVdwType_j};

        const auto coulombPreFactor = molecule1.getPartialCharge(atomType_i) * molecule2.getPartialCharge(atomType_j);

        auto [energy, force] = _coulombPotential->calculate(distance, coulombPreFactor);
        coulombEnergy        = energy;

        const auto nonCoulombicPair = _nonCoulombPotential->getNonCoulombPair(combinedIndices);

        if (const auto rncCutOff = nonCoulombicPair->getRadialCutOff(); distance < rncCutOff)
        {
            const auto &[energy, nonCoulombForce] = nonCoulombicPair->calculateEnergyAndForce(distance);
            nonCoulombEnergy                      = energy;

            force += nonCoulombForce;
        }

        force /= distance;

        const auto forcexyz = force * dxyz;

        const auto shiftForcexyz = forcexyz * txyz;

        molecule1.addAtomForce(atom1, forcexyz);
        molecule2.addAtomForce(atom2, -forcexyz);

        molecule1.addAtomShiftForce(atom1, shiftForcexyz);
    }

    return {coulombEnergy, nonCoulombEnergy};
}