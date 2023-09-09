#ifndef _TEST_RSTFILEOUTPUT_HPP_

#define _TEST_RSTFILEOUTPUT_HPP_

#include "molecule.hpp"        // for Molecule
#include "rstFileOutput.hpp"   // for RstFileOutput
#include "simulationBox.hpp"   // for SimulationBox
#include "vector3d.hpp"        // for Vec3D

#include <gtest/gtest.h>   // for Test
#include <memory>          // for allocator
#include <stdio.h>         // for remove

/**
 * @class TestRstFileOutput
 *
 * @brief test suite for restart file output
 *
 */
class TestRstFileOutput : public ::testing::Test
{
  protected:
    void SetUp() override
    {
        _rstFileOutput = new output::RstFileOutput("default.rst");
        _simulationBox = new simulationBox::SimulationBox();

        _simulationBox->setBoxDimensions({10.0, 10.0, 10.0});
        _simulationBox->setBoxAngles({90.0, 90.0, 90.0});

        auto molecule1 = simulationBox::Molecule();
        molecule1.setNumberOfAtoms(2);
        molecule1.addAtomPosition(linearAlgebra::Vec3D(1.0, 1.0, 1.0));
        molecule1.addAtomPosition(linearAlgebra::Vec3D(1.0, 2.0, 3.0));
        molecule1.addAtomForce(linearAlgebra::Vec3D(1.0, 1.0, 1.0));
        molecule1.addAtomForce(linearAlgebra::Vec3D(2.0, 3.0, 4.0));
        molecule1.addAtomVelocity(linearAlgebra::Vec3D(1.0, 1.0, 1.0));
        molecule1.addAtomVelocity(linearAlgebra::Vec3D(3.0, 4.0, 5.0));
        molecule1.addAtomName("H");
        molecule1.addAtomName("O");
        molecule1.setMoltype(1);

        auto molecule2 = simulationBox::Molecule();
        molecule2.setNumberOfAtoms(1);
        molecule2.addAtomPosition(linearAlgebra::Vec3D(1.0, 1.0, 1.0));
        molecule2.addAtomForce(linearAlgebra::Vec3D(1.0, 1.0, 1.0));
        molecule2.addAtomVelocity(linearAlgebra::Vec3D(1.0, 1.0, 1.0));
        molecule2.addAtomName("Ar");
        molecule2.setMoltype(2);

        _simulationBox->addMolecule(molecule1);
        _simulationBox->addMolecule(molecule2);
    }

    void TearDown() override
    {
        delete _rstFileOutput;
        delete _simulationBox;
        ::remove("default.rst");
    }

    output::RstFileOutput        *_rstFileOutput;
    simulationBox::SimulationBox *_simulationBox;
};

#endif   // _TEST_RSTFILEOUTPUT_HPP_