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
    float input = -static_cast<float>(167.123456789123456);
    float epsilon = 1.f / static_cast<float>(1 << 16);

    FixedPoint<16, 16> fixed(input);
    float result = fixed.toFloat();
    EXPECT_NEAR(result, input, epsilon);
}

TEST(FixedPointTest, AdditionWorks)
{
    float a = static_cast<float>(167.123456789123456);
    float b = static_cast<float>(183.678912389502341);
    float epsilon = 1.f / static_cast<float>(1 << 16);

    FixedPoint<16, 16> aFixed(a);
    FixedPoint<16, 16> bFixed(b);
    FixedPoint<16, 16> cFixed = aFixed + bFixed;

    float result = cFixed.toFloat();
    float expected = a + b;
    EXPECT_NEAR(result, expected, epsilon);
}

TEST(FixedPointTest, AdditionOverflowWorks)
{
    float a = 3.f;
    float b = 1.f;
    float epsilon = 1.f / static_cast<float>(1 << 16);

    FixedPoint<3, 0> aFixed(a);
    FixedPoint<3, 0> bFixed(b);
    FixedPoint<3, 0> cFixed = aFixed + bFixed;

    float result = cFixed.toFloat();
    float expected = -4;
    EXPECT_NEAR(result, expected, epsilon);
}

TEST(FixedPointTest, SubstractionWorks)
{
    float a = static_cast<float>(167.123456789123456);
    float b = static_cast<float>(183.678912389502341);
    float epsilon = 1.f / static_cast<float>(1 << 16);

    FixedPoint<16, 16> aFixed(a);
    FixedPoint<16, 16> bFixed(b);
    FixedPoint<16, 16> cFixed = aFixed - bFixed;

    float result = cFixed.toFloat();
    float expected = a - b;
    EXPECT_NEAR(result, expected, epsilon);
}

TEST(FixedPointTest, SubstractionOverflowWorks)
{
    float a = -4.f;
    float b = 1.f;
    float epsilon = 1.f / static_cast<float>(1 << 16);

    FixedPoint<3, 0> aFixed(a);
    FixedPoint<3, 0> bFixed(b);
    FixedPoint<3, 0> cFixed = aFixed - bFixed;

    float result = cFixed.toFloat();
    float expected = 3;
    EXPECT_NEAR(result, expected, epsilon);
}

TEST(FixedPointTest, LeftShiftWorks)
{
    float a = -static_cast<float>(167.123456789123456);
    unsigned shiftValue = 2;
    float epsilon = 1.f / static_cast<float>(1 << 16);

    FixedPoint<13, 16> aFixed(a);
    FixedPoint<13, 16> bFixed = aFixed << shiftValue;

    float result = bFixed.toFloat();
    float expected = a * static_cast<float>(1 << shiftValue);
    EXPECT_NEAR(result, expected, epsilon);
}

TEST(FixedPointTest, LeftShiftOverflowWorks)
{
    float a = 3.f;
    unsigned shiftValue = 1;
    float epsilon = 1.f / static_cast<float>(1 << 16);

    FixedPoint<3, 0> aFixed(a);
    FixedPoint<3, 0> bFixed = aFixed << shiftValue;

    float result = bFixed.toFloat();
    float expected = -2;
    EXPECT_NEAR(result, expected, epsilon);
}

TEST(FixedPointTest, RightShiftWorks)
{
    float a = -static_cast<float>(167.123456789123456);
    unsigned shiftValue = 2;
    float epsilon = 1.f / static_cast<float>(1 << 16);

    FixedPoint<13, 16> aFixed(a);
    FixedPoint<13, 16> bFixed = aFixed >> shiftValue;

    float result = bFixed.toFloat();
    float expected = a / static_cast<float>(1 << shiftValue);
    EXPECT_NEAR(result, expected, epsilon);
}

TEST(FixedPointTest, FixedPointNegationWorks)
{
    float a = static_cast<float>(167.123456789123456);
    float epsilon = 1.f / static_cast<float>(1 << 16);

    FixedPoint<16, 16> aFixed(a);
    FixedPoint<16, 16> bFixed = -aFixed;

    float result = bFixed.toFloat();
    float expected = -a;
    EXPECT_NEAR(result, expected, epsilon);
}
