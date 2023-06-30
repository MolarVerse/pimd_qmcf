#include "testMolecule.hpp"

using namespace std;

TEST_F(TestMolecule, numberOfAtomTypes) { EXPECT_EQ(_molecule->getNumberOfAtomTypes(), 3); }

TEST_F(TestMolecule, calculateCenterOfMass)
{
    const vector3d::Vec3D box          = {10.0, 10.0, 10.0};
    const vector3d::Vec3D centerOfMass = {1.0 / 3.0, 1.0 / 2.0, 0.0};

    _molecule->calculateCenterOfMass(box);
    EXPECT_EQ(_molecule->getCenterOfMass(), centerOfMass);
}

TEST_F(TestMolecule, scaleAtoms)
{
    const vector3d::Vec3D scale         = {1.0, 2.0, 3.0};
    const vector3d::Vec3D atomPosition1 = _molecule->getAtomPosition(0);
    const vector3d::Vec3D atomPosition2 = _molecule->getAtomPosition(1);
    const vector3d::Vec3D atomPosition3 = _molecule->getAtomPosition(2);

    _molecule->calculateCenterOfMass({10.0, 10.0, 10.0});

    const auto            centerOfMassBeforeScaling = _molecule->getCenterOfMass();
    const vector3d::Vec3D shift                     = centerOfMassBeforeScaling * (scale - 1.0);

    _molecule->scale(scale);

    EXPECT_EQ(_molecule->getAtomPosition(0), atomPosition1 + shift);
    EXPECT_EQ(_molecule->getAtomPosition(1), atomPosition2 + shift);
    EXPECT_EQ(_molecule->getAtomPosition(2), atomPosition3 + shift);
}

TEST_F(TestMolecule, scaleVelocities)
{
    const double          scale         = 2.0;
    const vector3d::Vec3D atomVelocity1 = _molecule->getAtomVelocity(0);
    const vector3d::Vec3D atomVelocity2 = _molecule->getAtomVelocity(1);
    const vector3d::Vec3D atomVelocity3 = _molecule->getAtomVelocity(2);

    _molecule->scaleVelocities(scale);

    EXPECT_EQ(_molecule->getAtomVelocity(0), atomVelocity1 * scale);
    EXPECT_EQ(_molecule->getAtomVelocity(1), atomVelocity2 * scale);
    EXPECT_EQ(_molecule->getAtomVelocity(2), atomVelocity3 * scale);
}

TEST_F(TestMolecule, correctVelocities)
{
    const vector3d::Vec3D scale         = {1.0, 2.0, 4.0};
    const vector3d::Vec3D atomVelocity1 = _molecule->getAtomVelocity(0);
    const vector3d::Vec3D atomVelocity2 = _molecule->getAtomVelocity(1);
    const vector3d::Vec3D atomVelocity3 = _molecule->getAtomVelocity(2);

    _molecule->correctVelocities(scale);

    EXPECT_EQ(_molecule->getAtomVelocity(0), atomVelocity1 - scale);
    EXPECT_EQ(_molecule->getAtomVelocity(1), atomVelocity2 - scale);
    EXPECT_EQ(_molecule->getAtomVelocity(2), atomVelocity3 - scale);
}

TEST_F(TestMolecule, resizeAtomShiftForces)
{
    EXPECT_EQ(_molecule->getAtomShiftForces().size(), 0);
    _molecule->resizeAtomShiftForces();
    EXPECT_EQ(_molecule->getAtomShiftForces().size(), 3);
}

TEST_F(TestMolecule, setAtomForceToZero)
{
    _molecule->setAtomForcesToZero();
    EXPECT_EQ(_molecule->getAtomForce(0), vector3d::Vec3D());
    EXPECT_EQ(_molecule->getAtomForce(1), vector3d::Vec3D());
    EXPECT_EQ(_molecule->getAtomForce(2), vector3d::Vec3D());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return ::RUN_ALL_TESTS();
}