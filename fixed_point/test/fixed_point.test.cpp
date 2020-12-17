#include "gtest/gtest.h"

#include "fixed_point.hpp"


TEST(FixedPointTest, MagnitudeIsConserved)
{
    FixedPoint<16, 16> fixed(167.f);
    float result = fixed.toFloat();
    EXPECT_FLOAT_EQ(result, 167.f);
}

TEST(FixedPointTest, SignIsConserved)
{
    FixedPoint<16, 16> fixed(-167.f);
    float result = fixed.toFloat();
    EXPECT_FLOAT_EQ(result, -167.f);
}

TEST(FixedPointTest, FractionalIsConserved)
{
    float input = -167.123456789123456;
    float epsilon = 1.f / static_cast<float>(1 << 16);

    FixedPoint<16, 16> fixed(input);
    float result = fixed.toFloat();
    EXPECT_NEAR(result, input, epsilon);
}
