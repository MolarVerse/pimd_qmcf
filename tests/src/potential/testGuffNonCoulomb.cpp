#include "nonCoulombPotential.hpp"

#include <cmath>
#include <gtest/gtest.h>

TEST(TestGuffNonCoulomb, guffNonCoulomb)
{
    const auto   coefficients = std::vector<double>{2.0,  3.0,  4.0,  5.0,  6.0,  7.0,  8.0,  9.0,  10.0, 11.0, 12.0,
                                                    13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0};
    const auto   rncCutoff    = 3.0;
    double       energy       = 0.0;
    double       force        = 0.0;
    const double energyCutoff = 1.0;
    const double forceCutoff  = 2.0;

    const auto guffNonCoulomb = potential::GuffNonCoulomb();

    auto distance = 2.0;
    guffNonCoulomb.calcNonCoulomb(coefficients, rncCutoff, distance, energy, force, energyCutoff, forceCutoff);

    auto energyREF  = coefficients[0] / pow(distance, coefficients[1]) + coefficients[2] / pow(distance, coefficients[3]);
    energyREF      += coefficients[4] / pow(distance, coefficients[5]) + coefficients[6] / pow(distance, coefficients[7]);
    energyREF      += coefficients[8] / (1 + exp(coefficients[9] * (distance - coefficients[10])));
    energyREF      += coefficients[11] / (1 + exp(coefficients[12] * (distance - coefficients[13])));
    energyREF      += coefficients[14] * exp(coefficients[15] * pow(distance - coefficients[16], coefficients[17]));
    energyREF      += coefficients[18] * exp(coefficients[19] * pow(distance - coefficients[20], coefficients[21]));
    energyREF      += -energyCutoff - forceCutoff * (rncCutoff - distance);

    auto forceREF  = coefficients[0] * coefficients[1] / pow(distance, coefficients[1] + 1);
    forceREF      += coefficients[2] * coefficients[3] / pow(distance, coefficients[3] + 1);
    forceREF      += coefficients[4] * coefficients[5] / pow(distance, coefficients[5] + 1);
    forceREF      += coefficients[6] * coefficients[7] / pow(distance, coefficients[7] + 1);
    forceREF      += coefficients[8] * coefficients[9] * exp(coefficients[9] * (distance - coefficients[10])) /
                pow(1 + exp(coefficients[9] * (distance - coefficients[10])), 2);
    forceREF += coefficients[11] * coefficients[12] * exp(coefficients[12] * (distance - coefficients[13])) /
                pow(1 + exp(coefficients[12] * (distance - coefficients[13])), 2);
    forceREF -= coefficients[14] * coefficients[15] * exp(coefficients[15] * pow(distance - coefficients[16], coefficients[17])) *
                pow(distance - coefficients[16], coefficients[17] - 1);
    forceREF -= coefficients[18] * coefficients[19] * exp(coefficients[19] * pow(distance - coefficients[20], coefficients[21])) *
                pow(distance - coefficients[20], coefficients[21] - 1);
    forceREF -= forceCutoff;

    EXPECT_DOUBLE_EQ(energy, energyREF);

    EXPECT_DOUBLE_EQ(force, forceREF);
    const auto intermediateForce = force;

    distance = 5.0;

    energyREF  = coefficients[0] / pow(distance, coefficients[1]) + coefficients[2] / pow(distance, coefficients[3]);
    energyREF += coefficients[4] / pow(distance, coefficients[5]) + coefficients[6] / pow(distance, coefficients[7]);
    energyREF += coefficients[8] / (1 + exp(coefficients[9] * (distance - coefficients[10])));
    energyREF += coefficients[11] / (1 + exp(coefficients[12] * (distance - coefficients[13])));
    energyREF += coefficients[14] * exp(coefficients[15] * pow(distance - coefficients[16], coefficients[17]));
    energyREF += coefficients[18] * exp(coefficients[19] * pow(distance - coefficients[20], coefficients[21]));
    energyREF += -energyCutoff - forceCutoff * (rncCutoff - distance);

    forceREF  = coefficients[0] * coefficients[1] / pow(distance, coefficients[1] + 1);
    forceREF += coefficients[2] * coefficients[3] / pow(distance, coefficients[3] + 1);
    forceREF += coefficients[4] * coefficients[5] / pow(distance, coefficients[5] + 1);
    forceREF += coefficients[6] * coefficients[7] / pow(distance, coefficients[7] + 1);
    forceREF += coefficients[8] * coefficients[9] * exp(coefficients[9] * (distance - coefficients[10])) /
                pow(1 + exp(coefficients[9] * (distance - coefficients[10])), 2);
    forceREF += coefficients[11] * coefficients[12] * exp(coefficients[12] * (distance - coefficients[13])) /
                pow(1 + exp(coefficients[12] * (distance - coefficients[13])), 2);
    forceREF -= coefficients[14] * coefficients[15] * exp(coefficients[15] * pow(distance - coefficients[16], coefficients[17])) *
                pow(distance - coefficients[16], coefficients[17] - 1);
    forceREF -= coefficients[18] * coefficients[19] * exp(coefficients[19] * pow(distance - coefficients[20], coefficients[21])) *
                pow(distance - coefficients[20], coefficients[21] - 1);
    forceREF -= forceCutoff;

    guffNonCoulomb.calcNonCoulomb(coefficients, rncCutoff, distance, energy, force, energyCutoff, forceCutoff);
    EXPECT_DOUBLE_EQ(energy, energyREF);
    EXPECT_DOUBLE_EQ(force, forceREF + intermediateForce);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}