#include "mathUtilities.hpp"

#include <gtest/gtest.h>

using namespace utilities;

/**
 * @brief tests compare function for double type
 *
 */
TEST(TestMathUtilities, compare)
{
    const double a = 1.0;
    EXPECT_TRUE(compare(a, a));
    EXPECT_FALSE(compare(a, a + std::numeric_limits<double>::epsilon()));

    const auto &b = linearAlgebra::Vec3D(1.0, 2.0, 3.0);
    EXPECT_TRUE(compare(b, b));
    EXPECT_FALSE(compare(b, b + linearAlgebra::Vec3D(b[0], b[1], std::numeric_limits<double>::epsilon())));
}

/**
 * @brief tests sign template function (here tests only for double data type)
 *
 */
TEST(TestMathUtilities, sign)
{
    EXPECT_EQ(sign(2.0), 1);
    EXPECT_EQ(sign(-2.0), -1);
    EXPECT_EQ(sign(0.0), 0);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return ::RUN_ALL_TESTS();
}