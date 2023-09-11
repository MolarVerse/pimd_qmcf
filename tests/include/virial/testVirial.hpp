#ifndef _TEST_VIRIAL_HPP_

#define _TEST_VIRIAL_HPP_

#include "molecule.hpp"        // for Molecule
#include "physicalData.hpp"    // for PhysicalData
#include "simulationBox.hpp"   // for SimulationBox
#include "vector3d.hpp"        // for Vec3D
#include "virial.hpp"          // for Virial

#include <gtest/gtest.h>   // for Test

class TestVirial : public ::testing::Test
{
  protected:
    void SetUp() override
    {
        _virial = new virial::Virial();
        _data   = new physicalData::PhysicalData();

        _simulationBox = new simulationBox::SimulationBox();

        auto molecule1 = simulationBox::Molecule();

        auto atom1 = std::make_shared<simulationBox::Atom>();
        auto atom2 = std::make_shared<simulationBox::Atom>();

        molecule1.setNumberOfAtoms(2);

        atom1->setPosition(linearAlgebra::Vec3D(1.0, 1.0, 1.0));
        atom2->setPosition(linearAlgebra::Vec3D(1.0, 2.0, 3.0));
        atom1->setForce(linearAlgebra::Vec3D(1.0, 1.0, 1.0));
        atom2->setForce(linearAlgebra::Vec3D(1.0, 2.0, 3.0));
        atom1->setShiftForce(linearAlgebra::Vec3D(1.0, 1.0, 1.0));
        atom2->setShiftForce(linearAlgebra::Vec3D(1.0, 2.0, 3.0));
        molecule1.setCenterOfMass(linearAlgebra::Vec3D(1.0, 1.0, 1.0));
        molecule1.addAtom(atom1);
        molecule1.addAtom(atom2);

        auto molecule2 = simulationBox::Molecule();

        auto atom3 = std::make_shared<simulationBox::Atom>();

        molecule2.setNumberOfAtoms(1);
        atom3->setPosition(linearAlgebra::Vec3D(1.0, 1.0, 1.0));
        atom3->setForce(linearAlgebra::Vec3D(1.0, 1.0, 1.0));
        atom3->setShiftForce(linearAlgebra::Vec3D(1.0, 1.0, 1.0));
        molecule2.setCenterOfMass(linearAlgebra::Vec3D(0.0, 0.0, 0.0));
        molecule2.addAtom(atom3);

        _simulationBox->addMolecule(molecule1);
        _simulationBox->addMolecule(molecule2);

        _simulationBox->setBoxDimensions(linearAlgebra::Vec3D(10.0, 10.0, 10.0));
    }

    void TearDown() override
    {
        delete _data;
        delete _simulationBox;
        delete _virial;
    }

    physicalData::PhysicalData   *_data;
    simulationBox::SimulationBox *_simulationBox;
    virial::Virial               *_virial;
};

#endif