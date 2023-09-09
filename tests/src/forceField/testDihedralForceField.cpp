#include "coulombShiftedPotential.hpp"   // for CoulombShiftedPotential
#include "dihedralForceField.hpp"        // for BondForceField
#include "forceFieldNonCoulomb.hpp"      // for ForceFieldNonCoulomb
#include "lennardJonesPair.hpp"          // for LennardJonesPair
#include "matrix.hpp"                    // for Matrix
#include "molecule.hpp"                  // for Molecule
#include "physicalData.hpp"              // for PhysicalData
#include "potentialSettings.hpp"         // for PotentialSettings
#include "simulationBox.hpp"             // for SimulationBox
#include "vector3d.hpp"                  // for Vector3D, Vec3D, operator*

#include "gmock/gmock.h"   // for DoubleNear, ElementsAre
#include "gtest/gtest.h"   // for Message, TestPartResult
#include <cmath>           // for sqrt
#include <cstddef>         // for size_t
#include <gtest/gtest.h>   // for EXPECT_NEAR, Test, InitGoogleTest, RUN_ALL_TESTS
#include <memory>          // for shared_ptr, allocator

namespace potential
{
    class NonCoulombPair;   // forward declaration
}

TEST(TestDihedralForceField, calculateEnergyAndForces)
{
    auto box = simulationBox::SimulationBox();
    box.setBoxDimensions({10.0, 10.0, 10.0});

    auto physicalData        = physicalData::PhysicalData();
    auto coulombPotential    = potential::CoulombShiftedPotential(20.0);
    auto nonCoulombPotential = potential::ForceFieldNonCoulomb();

    auto nonCoulombPair = potential::LennardJonesPair(size_t(0), size_t(1), 15.0, 2.0, 4.0);
    nonCoulombPotential.setNonCoulombPairsMatrix(linearAlgebra::Matrix<std::shared_ptr<potential::NonCoulombPair>>(2, 2));
    nonCoulombPotential.setNonCoulombPairsMatrix(0, 1, nonCoulombPair);

    auto molecule = simulationBox::Molecule();

    molecule.setMoltype(0);
    molecule.setNumberOfAtoms(3);
    molecule.addAtomPosition({0.0, 0.0, 0.0});
    molecule.addAtomPosition({1.0, 1.0, 1.0});
    molecule.addAtomPosition({1.0, 2.0, 3.0});
    molecule.addAtomPosition({4.0, 2.0, 3.0});

    molecule.addAtomForce({0.0, 0.0, 0.0});
    molecule.addAtomForce({0.0, 0.0, 0.0});
    molecule.addAtomForce({0.0, 0.0, 0.0});
    molecule.addAtomForce({0.0, 0.0, 0.0});

    molecule.addInternalGlobalVDWType(0);
    molecule.addInternalGlobalVDWType(1);
    molecule.addInternalGlobalVDWType(0);
    molecule.addInternalGlobalVDWType(1);

    molecule.addAtomType(0);
    molecule.addAtomType(1);
    molecule.addAtomType(0);
    molecule.addAtomType(1);

    molecule.addPartialCharge(1.0);
    molecule.addPartialCharge(-0.5);
    molecule.addPartialCharge(1.0);
    molecule.addPartialCharge(-0.5);

    auto bondForceField = forceField::DihedralForceField({&molecule, &molecule, &molecule, &molecule}, {0, 1, 2, 3}, 0);
    bondForceField.setPhaseShift(180.0 * M_PI / 180.0);
    bondForceField.setPeriodicity(3);
    bondForceField.setForceConstant(3.0);
    bondForceField.setIsLinker(false);

    settings::PotentialSettings::setScale14Coulomb(0.75);
    settings::PotentialSettings::setScale14VanDerWaals(0.5);

    bondForceField.calculateEnergyAndForces(box, physicalData, false, coulombPotential, nonCoulombPotential);

    EXPECT_NEAR(physicalData.getDihedralEnergy(), 3.9128709291752739, 1e-9);
    EXPECT_NEAR(physicalData.getImproperEnergy(), 0.0, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(0)[0], 3.19504825211347, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(0)[1], -6.39009650422694, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(0)[2], 3.19504825211347, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(1)[0], -5.1120772033815518, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(1)[1], 10.224154406763104, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(1)[2], -5.1120772033815518, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(2)[0], 1.9170289512680818, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(2)[1], -1.2780193008453877, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(2)[2], 0.63900965042269386, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(3)[0], 0.0, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(3)[1], -2.5560386016907759, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(3)[2], 1.278019300845388, 1e-9);
    EXPECT_NEAR(physicalData.getCoulombEnergy(), 0.0, 1e-9);
    EXPECT_NEAR(physicalData.getNonCoulombEnergy(), 0.0, 1e-9);
    EXPECT_THAT(
        physicalData.getVirial(),
        testing::ElementsAre(testing::DoubleNear(0.0, 1e-9), testing::DoubleNear(0.0, 1e-9), testing::DoubleNear(0.0, 1e-9)));

    molecule.setAtomForce(0, {0.0, 0.0, 0.0});
    molecule.setAtomForce(1, {0.0, 0.0, 0.0});
    molecule.setAtomForce(2, {0.0, 0.0, 0.0});
    molecule.setAtomForce(3, {0.0, 0.0, 0.0});
    physicalData.reset();

    bondForceField.setIsLinker(false);

    bondForceField.calculateEnergyAndForces(box, physicalData, true, coulombPotential, nonCoulombPotential);

    EXPECT_NEAR(physicalData.getImproperEnergy(), 3.9128709291752739, 1e-9);
    EXPECT_NEAR(physicalData.getDihedralEnergy(), 0.0, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(0)[0], 3.19504825211347, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(0)[1], -6.39009650422694, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(0)[2], 3.19504825211347, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(1)[0], -5.1120772033815518, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(1)[1], 10.224154406763104, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(1)[2], -5.1120772033815518, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(2)[0], 1.9170289512680818, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(2)[1], -1.2780193008453877, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(2)[2], 0.63900965042269386, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(3)[0], 0.0, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(3)[1], -2.5560386016907759, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(3)[2], 1.278019300845388, 1e-9);
    EXPECT_NEAR(physicalData.getCoulombEnergy(), 0.0, 1e-9);
    EXPECT_NEAR(physicalData.getNonCoulombEnergy(), 0.0, 1e-9);
    EXPECT_THAT(
        physicalData.getVirial(),
        testing::ElementsAre(testing::DoubleNear(0.0, 1e-9), testing::DoubleNear(0.0, 1e-9), testing::DoubleNear(0.0, 1e-9)));

    molecule.setAtomForce(0, {0.0, 0.0, 0.0});
    molecule.setAtomForce(1, {0.0, 0.0, 0.0});
    molecule.setAtomForce(2, {0.0, 0.0, 0.0});
    molecule.setAtomForce(3, {0.0, 0.0, 0.0});
    physicalData.reset();

    bondForceField.setIsLinker(true);

    bondForceField.calculateEnergyAndForces(box, physicalData, false, coulombPotential, nonCoulombPotential);

    EXPECT_NEAR(physicalData.getDihedralEnergy(), 3.9128709291752739, 1e-9);
    EXPECT_NEAR(physicalData.getImproperEnergy(), 0.0, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(0)[0], 2.2090108292824047, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(0)[1], -6.8831152156424729, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(0)[2], 2.4555201849901707, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(1)[0], -5.1120772033815518, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(1)[1], 10.224154406763104, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(1)[2], -5.1120772033815518, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(2)[0], 1.9170289512680818, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(2)[1], -1.2780193008453877, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(2)[2], 0.63900965042269386, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(3)[0], 0.98603742283106555, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(3)[1], -2.063019890275243, 1e-9);
    EXPECT_NEAR(molecule.getAtomForce(3)[2], 2.0175473679686871, 1e-9);
    EXPECT_NEAR(physicalData.getCoulombEnergy(), 4.1158570930777021, 1e-9);
    EXPECT_NEAR(physicalData.getNonCoulombEnergy(), -4.100545344959669e-05, 1e-9);
    EXPECT_NEAR(physicalData.getVirial()[0], 3.9441496913242622, 1e-9);
    EXPECT_NEAR(physicalData.getVirial()[1], 0.98603742283106555, 1e-9);
    EXPECT_NEAR(physicalData.getVirial()[2], 2.2185842013698975, 1e-9);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return ::RUN_ALL_TESTS();
}