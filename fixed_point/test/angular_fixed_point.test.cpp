#include <cmath>

#include "gtest/gtest.h"

#include "angular_fixed_point.hpp"

TEST(AngularFixedPointTest, ValueIsConserved)
{
    float input = M_PI / 2.f;
    float expected = M_PI / 2.f;
    float epsilon = 2.f * M_PI / std::pow(2.f, 30);

    AngularFixedPoint<31> fixed(input);
    float result = fixed.toFloat();

    EXPECT_NEAR(result, expected, epsilon);
}

TEST(AngularFixedPointTest, NegativeValueIsConserved)
{
    float input = -M_PI * 3.f / 4.f;
    float expected = -M_PI * 3.f / 4.f;
    float epsilon = 2.f * M_PI / std::pow(2.f, 30);

    AngularFixedPoint<31> fixed(input);
    float result = fixed.toFloat();

    EXPECT_NEAR(result, expected, epsilon);
}

TEST(AngularFixedPointTest, ZeroIsConserved)
{
    float input = 0;
    float expected = 0;
    float epsilon = 2.f * M_PI / std::pow(2.f, 30);

    AngularFixedPoint<31> fixed(input);
    float result = fixed.toFloat();

    EXPECT_NEAR(result, expected, epsilon);
}


TEST(AngularFixedPointTest, AngleIsCyclic)
{
    float input = M_PI * 7.f / 4.f;
    float expected = - M_PI / 4.f;
    float epsilon = 2.f * M_PI / std::pow(2.f, 30);

    AngularFixedPoint<31> fixed(input);
    float result = fixed.toFloat();
    EXPECT_NEAR(result, expected, epsilon);
}

TEST(AngularFixedPointTest, SubstractionWorks)
{
    float a = 2.f;
    float b = 1.f;
    float epsilon = 2.f * M_PI / std::pow(2.f, 30);

    AngularFixedPoint<31> aFixed(a);
    AngularFixedPoint<31> bFixed(b);
    AngularFixedPoint<31> cFixed = aFixed - bFixed;

    float result = cFixed.toFloat();
    float expected = a - b;
    EXPECT_NEAR(result, expected, epsilon);
}

TEST(AngularFixedPointTest, SubstractionIsCyclic)
{
    float a = -M_PI * 3.f / 4.f;
    float b = M_PI;
    float expected = M_PI / 4.f;
    float epsilon = 2.f * M_PI / std::pow(2.f, 30);

    AngularFixedPoint<31> aFixed(a);
    AngularFixedPoint<31> bFixed(b);
    AngularFixedPoint<31> cFixed = aFixed - bFixed;

    float result = cFixed.toFloat();
    EXPECT_NEAR(result, expected, epsilon);
}

TEST(AngularFixedPointTest, NegateWorks)
{
    float a = 2.f;
    float epsilon = 2.f * M_PI / std::pow(2.f, 30);

    AngularFixedPoint<31> aFixed(a);
    AngularFixedPoint<31> cFixed = -aFixed;

    float result = cFixed.toFloat();
    float expected = -a;
    EXPECT_NEAR(result, expected, epsilon);
}

TEST(AngularFixedPointTest, SubstractionIsCyclicLowerResolution)
{
    float a = -M_PI * 3.f / 4.f;
    float b = M_PI;
    float expected = M_PI / 4.f;
    float epsilon = 2.f * M_PI / std::pow(2.f, 15);

    AngularFixedPoint<15> aFixed(a);
    AngularFixedPoint<15> bFixed(b);
    AngularFixedPoint<15> cFixed = aFixed - bFixed;

    float result = cFixed.toFloat();
    EXPECT_NEAR(result, expected, epsilon);
}

TEST(AngularFixedPointTest, IsInferiorWorks)
{
    float a = M_PI / 2.f;
    float b = M_PI * 3.f / 4.f;
    bool expected =  a <= b;

    AngularFixedPoint<15> aFixed(a);
    bool result = aFixed <= b;

    EXPECT_EQ(result, expected);
}

TEST(AngularFixedPointTest, IsSuperiorWorks)
{
    float a = M_PI / 2.f;
    float b = M_PI * 3.f / 4.f;
    bool expected =  a >= b;

    AngularFixedPoint<15> aFixed(a);
    bool result = aFixed >= b;

    EXPECT_EQ(result, expected);
}
