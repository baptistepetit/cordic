#include "gtest/gtest.h"

#include "utils.hpp"
#include "fixed_point.hpp"

TEST(UtilsTest, MultiplyBySignOfWorksForFloat)
{
    float input = 167.123456789123456;
    float result = multiplyBySignOf(-2.f, input);
    float expected = -input;

    EXPECT_FLOAT_EQ(result, expected);
}

TEST(UtilsTest, MultiplyBySignOfWorksForFixedPoint)
{
    float input = 167.123456789123456;
    float epsilon = 1.f / static_cast<float>(1 << 16);

    FixedPoint<15, 16> aFixed(input);
    FixedPoint<15, 16> bFixed = multiplyBySignOf(-2.f, aFixed);

    float result = bFixed.toFloat();
    float expected = -input;
    EXPECT_NEAR(result, expected, epsilon);
}
