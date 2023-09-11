#ifndef _TEST_RESET_KINETICS_HPP_

#define _TEST_RESET_KINETICS_HPP_

#include "molecule.hpp"        // for Molecule
#include "physicalData.hpp"    // for PhysicalData
#include "resetKinetics.hpp"   // for ResetKinetics
#include "simulationBox.hpp"   // for SimulationBox
#include "vector3d.hpp"        // for Vec3D

#include <gtest/gtest.h>   // for Test

/**
 * @class TestResetKinetics
 *
 * @brief Fixture class for testing the ResetKinetics class
 *
 */
class TestResetKinetics : public ::testing::Test
{
  protected:
    void SetUp() override
    {
        _resetKinetics = new resetKinetics::ResetKinetics(1, 2, 3, 4, 300.0);
        _data          = new physicalData::PhysicalData();

        _simulationBox = new simulationBox::SimulationBox();

        auto molecule1 = simulationBox::Molecule();

        auto atom1 = std::make_shared<simulationBox::Atom>();
        auto atom2 = std::make_shared<simulationBox::Atom>();

        molecule1.setNumberOfAtoms(2);

        atom1->setVelocity(linearAlgebra::Vec3D(1.0, 1.0, 1.0));
        atom2->setVelocity(linearAlgebra::Vec3D(1.0, 2.0, 3.0));
        atom1->setMass(1.0);
        atom2->setMass(1.0);
        molecule1.addAtom(atom1);
        molecule1.addAtom(atom2);

        auto molecule2 = simulationBox::Molecule();

        auto atom3 = std::make_shared<simulationBox::Atom>();

        molecule2.setNumberOfAtoms(1);
        atom3->setVelocity(linearAlgebra::Vec3D(1.0, 1.0, 1.0));
        atom3->setMass(1.0);
        molecule2.addAtom(atom3);

        _simulationBox->addMolecule(molecule1);
        _simulationBox->addMolecule(molecule2);
        _simulationBox->setTotalMass(3.0);
    }

    void TearDown() override
    {
        delete _data;
        delete _simulationBox;
        delete _resetKinetics;
    }

    physicalData::PhysicalData   *_data;
    simulationBox::SimulationBox *_simulationBox;
    resetKinetics::ResetKinetics *_resetKinetics;
};

#endif