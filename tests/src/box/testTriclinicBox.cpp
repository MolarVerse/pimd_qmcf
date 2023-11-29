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

#include "constants/conversionFactors.hpp"   // for _KG_PER_LITER_TO_AMU_PER_ANGSTROM_CUBIC_
#include "manostatSettings.hpp"              // for ManostatSettings
#include "matrixNear.hpp"                    // for EXPECT_MATRIX_NEAR
#include "staticMatrix3x3.hpp"               // for StaticMatrix3x3
#include "triclinicBox.hpp"                  // for TriclinicBox
#include "vector3d.hpp"                      // for Vec3D
#include "vectorNear.hpp"                    // for EXPECT_VECTOR_NEAR

#include "gtest/gtest.h"   // for Message, TestPartResult
#include <memory>          // for allocator

using namespace simulationBox;

TEST(TestTriclinicBox, setBoxDimensions)
{
    auto                       box           = TriclinicBox();
    const linearAlgebra::Vec3D boxDimensions = {1.0, 2.0, 3.0};
    box.setBoxDimensions(boxDimensions);
    EXPECT_EQ(box.getBoxDimensions(), boxDimensions);

    // only first entry should be set to boxDimensions[0] because angles are not set yet
    EXPECT_EQ(box.getBoxMatrix(), linearAlgebra::StaticMatrix3x3<double>({1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}));
}

TEST(TestTriclinicBox, setBoxAngles)
{
    auto                       box           = TriclinicBox();
    const linearAlgebra::Vec3D boxDimensions = {1.0, 2.0, 3.0};
    const linearAlgebra::Vec3D boxAngles     = {90.0, 90.0, 90.0};
    box.setBoxDimensions(boxDimensions);
    box.setBoxAngles(boxAngles);
    EXPECT_EQ(box.getBoxDimensions(), boxDimensions);
    EXPECT_EQ(box.getBoxAngles(), boxAngles);
    EXPECT_MATRIX_NEAR(
        box.getBoxMatrix(), linearAlgebra::StaticMatrix3x3<double>({1.0, 0.0, 0.0}, {0.0, 2.0, 0.0}, {0.0, 0.0, 3.0}), 1e-15);
    EXPECT_MATRIX_NEAR(box.getTransformationMatrix(),
                       linearAlgebra::StaticMatrix3x3<double>({1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}),
                       1e-15);

    box.setBoxAngles({30.0, 60.0, 45.0});

    const auto alpha = 30.0 * constants::_DEG_TO_RAD_;
    const auto beta  = 60.0 * constants::_DEG_TO_RAD_;
    const auto gamma = 45.0 * constants::_DEG_TO_RAD_;

    EXPECT_MATRIX_NEAR(
        box.getTransformationMatrix(),
        linearAlgebra::StaticMatrix3x3<double>({1.0, sqrt(0.5), ::cos(beta)},
                                               {0.0, sqrt(0.5), (cos(alpha) - cos(beta) * cos(gamma)) / sin(gamma)},
                                               {0.0,
                                                0.0,
                                                ::sqrt(1 - cos(alpha) * cos(alpha) - cos(beta) * cos(beta) -
                                                       cos(gamma) * cos(gamma) + 2 * cos(alpha) * cos(beta) * cos(gamma)) /
                                                    sin(gamma)}),
        1e-15);

    auto boxMatrix = linearAlgebra::StaticMatrix3x3<double>();
    boxMatrix[0]   = {box.getTransformationMatrix()[0] * box.getBoxDimensions()};
    boxMatrix[1]   = {box.getTransformationMatrix()[1] * box.getBoxDimensions()};
    boxMatrix[2]   = {box.getTransformationMatrix()[2] * box.getBoxDimensions()};
    EXPECT_MATRIX_NEAR(box.getBoxMatrix(), boxMatrix, 1.0e-15);
}

TEST(TestTriclinicBox, calculateVolume)
{
    auto box = TriclinicBox();
    box.setBoxDimensions({1.0, 2.0, 3.0});
    box.setBoxAngles({30.0, 60.0, 45.0});

    const auto alpha = 30.0 * constants::_DEG_TO_RAD_;
    const auto beta  = 60.0 * constants::_DEG_TO_RAD_;
    const auto gamma = 45.0 * constants::_DEG_TO_RAD_;

    const auto volume = 1.0 * 2.0 * 3.0 *
                        ::sqrt(1 - ::cos(alpha) * ::cos(alpha) - ::cos(beta) * ::cos(beta) - ::cos(gamma) * ::cos(gamma) +
                               2 * ::cos(alpha) * ::cos(beta) * ::cos(gamma));

    EXPECT_DOUBLE_EQ(box.calculateVolume(), volume);
}

TEST(TestTriclinicBox, applyPBC)
{
    auto box = TriclinicBox();
    box.setBoxDimensions({1.0, 2.0, 3.0});
    box.setBoxAngles({30.0, 60.0, 45.0});

    auto position = linearAlgebra::Vec3D({1.3, 2.3, 3.3});

    box.applyPBC(position);

    EXPECT_VECTOR_NEAR(position, linearAlgebra::Vec3D({0.12842712474619078, 0.77995789639665647, 0.45556413851582972}), 1e-8);
}

TEST(TestTriclinicBox, calculateShiftVectors)
{
    auto box = TriclinicBox();
    box.setBoxDimensions({1.0, 2.0, 3.0});
    box.setBoxAngles({30.0, 60.0, 45.0});

    const auto position    = linearAlgebra::Vec3D({1.3, 2.3, 3.3});
    const auto newPosition = linearAlgebra::Vec3D({0.12842712474619078, 0.77995789639665647, 0.45556413851582972});

    const auto shiftVector = box.calculateShiftVector(position);

    EXPECT_VECTOR_NEAR(shiftVector, (position - newPosition), 1e-8);
}

TEST(TestTriclinicBox, transformIntoOrthogonalSpace)
{
    auto box = TriclinicBox();
    box.setBoxDimensions({1.0, 2.0, 3.0});
    box.setBoxAngles({90.0, 90.0, 90.0});

    const auto position       = linearAlgebra::Vec3D({1.3, 2.3, 3.3});
    const auto positionMatrix = linearAlgebra::tensor3D{{1.3, 2.3, 3.3}, {1.3, 2.3, 3.3}, {1.3, 2.3, 3.3}};
    auto       newPosition    = linearAlgebra::Vec3D({1.3, 2.3, 3.3});
    auto       newMatrix      = linearAlgebra::tensor3D{{1.3, 2.3, 3.3}, {1.3, 2.3, 3.3}, {1.3, 2.3, 3.3}};

    auto transformedPosition = box.transformIntoOrthogonalSpace(position);
    auto transformedMatrix   = box.transformIntoOrthogonalSpace(positionMatrix);

    EXPECT_VECTOR_NEAR(transformedPosition, newPosition, 1e-8);
    EXPECT_MATRIX_NEAR(transformedMatrix, newMatrix, 1e-8);

    box.setBoxAngles({30.0, 60.0, 45.0});

    newPosition = inverse(box.getTransformationMatrix()) * position;
    newMatrix   = inverse(box.getTransformationMatrix()) * positionMatrix;

    transformedPosition = box.transformIntoOrthogonalSpace(position);
    transformedMatrix   = box.transformIntoOrthogonalSpace(positionMatrix);

    EXPECT_VECTOR_NEAR(transformedPosition, newPosition, 1e-8);
    EXPECT_MATRIX_NEAR(transformedMatrix, newMatrix, 1e-8);
}

TEST(TestTriclinicBox, transformIntoSimulationSpace)
{
    auto box = TriclinicBox();
    box.setBoxDimensions({1.0, 2.0, 3.0});
    box.setBoxAngles({90.0, 90.0, 90.0});

    const auto position       = linearAlgebra::Vec3D({1.3, 2.3, 3.3});
    const auto positionMatrix = linearAlgebra::tensor3D{{1.3, 2.3, 3.3}, {1.3, 2.3, 3.3}, {1.3, 2.3, 3.3}};
    auto       newPosition    = linearAlgebra::Vec3D({1.3, 2.3, 3.3});
    auto       newMatrix      = linearAlgebra::tensor3D{{1.3, 2.3, 3.3}, {1.3, 2.3, 3.3}, {1.3, 2.3, 3.3}};

    auto transformedPosition = box.transformIntoSimulationSpace(position);
    auto transformedMatrix   = box.transformIntoSimulationSpace(positionMatrix);

    EXPECT_VECTOR_NEAR(transformedPosition, newPosition, 1e-8);
    EXPECT_MATRIX_NEAR(transformedMatrix, newMatrix, 1e-8);

    box.setBoxAngles({30.0, 60.0, 45.0});

    newPosition = box.getTransformationMatrix() * position;
    newMatrix   = box.getTransformationMatrix() * positionMatrix;

    transformedPosition = box.transformIntoSimulationSpace(position);
    transformedMatrix   = box.transformIntoSimulationSpace(positionMatrix);

    EXPECT_VECTOR_NEAR(transformedPosition, newPosition, 1e-8);
    EXPECT_MATRIX_NEAR(transformedMatrix, newMatrix, 1e-8);
}

TEST(TestTriclinicBox, calculateBoxDimensionsAndAnglesFromBoxMatrix)
{
    auto box = TriclinicBox();
    box.setBoxDimensions({1.0, 2.0, 3.0});
    box.setBoxAngles({30.0, 60.0, 45.0});

    auto boxDimensionsAndAngles = calculateBoxDimensionsAndAnglesFromBoxMatrix(box.getBoxMatrix());

    EXPECT_VECTOR_NEAR(boxDimensionsAndAngles.first, box.getBoxDimensions(), 1e-10);
    EXPECT_VECTOR_NEAR(boxDimensionsAndAngles.second, box.getBoxAngles(), 1e-10);
}

TEST(TestTriclinicBox, scaleBox)
{
    auto scalingTensor = linearAlgebra::tensor3D{{1.0, 0.0, 0.0}, {0.0, 2.0, 0.0}, {0.0, 0.0, 3.0}};

    auto box = TriclinicBox();
    box.setBoxDimensions({1.0, 2.0, 3.0});
    box.setBoxAngles({30.0, 60.0, 45.0});
    auto oldBoxMatrix = box.getBoxMatrix();

    box.scaleBox(scalingTensor);

    auto newBoxDimensions  = linearAlgebra::Vec3D({1.0, 4.0, 9.0});
    auto newBoxAngles      = linearAlgebra::Vec3D({30.0, 60.0, 45.0});
    auto newBoxMatrix_row1 = oldBoxMatrix[0] * linearAlgebra::Vec3D(1.0, 2.0, 3.0);
    auto newBoxMatrix_row2 = oldBoxMatrix[1] * linearAlgebra::Vec3D(1.0, 2.0, 3.0);
    auto newBoxMatrix_row3 = oldBoxMatrix[2] * linearAlgebra::Vec3D(1.0, 2.0, 3.0);
    EXPECT_VECTOR_NEAR(box.getBoxMatrix()[0], newBoxMatrix_row1, 1e-12);
    EXPECT_VECTOR_NEAR(box.getBoxMatrix()[1], newBoxMatrix_row2, 1e-12);
    EXPECT_VECTOR_NEAR(box.getBoxMatrix()[2], newBoxMatrix_row3, 1e-12);
    EXPECT_VECTOR_NEAR(box.getBoxDimensions(), newBoxDimensions, 1e-12);
    EXPECT_VECTOR_NEAR(box.getBoxAngles(), newBoxAngles, 1e-12);

    settings::ManostatSettings::setIsotropy(settings::Isotropy::FULL_ANISOTROPIC);

    box.setBoxDimensions({1.0, 2.0, 3.0});
    box.setBoxAngles({30.0, 60.0, 45.0});

    box.scaleBox(scalingTensor);

    newBoxMatrix_row1 = oldBoxMatrix[0] * 1.0;
    newBoxMatrix_row2 = oldBoxMatrix[1] * 2.0;
    newBoxMatrix_row3 = oldBoxMatrix[2] * 3.0;
    EXPECT_VECTOR_NEAR(box.getBoxMatrix()[0], newBoxMatrix_row1, 1e-12);
    EXPECT_VECTOR_NEAR(box.getBoxMatrix()[1], newBoxMatrix_row2, 1e-12);
    EXPECT_VECTOR_NEAR(box.getBoxMatrix()[2], newBoxMatrix_row3, 1e-12);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return ::RUN_ALL_TESTS();
}