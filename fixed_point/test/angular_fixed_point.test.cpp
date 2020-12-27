#include <cmath>

#include "gtest/gtest.h"

#include "angular_fixed_point.hpp"

TEST(AngularFixedPointTest, ValueIsConserved)
{
    float input = m_pi / 2.f;
    float expected = m_pi / 2.f;
    float epsilon = 2.f * m_pi / std::pow(2.f, 30);

    AngularFixedPoint<31> fixed(input);
    float result = fixed.toFloat();

    EXPECT_NEAR(result, expected, epsilon);
}

TEST(AngularFixedPointTest, NegativeValueIsConserved)
{
    float input = -m_pi * 3.f / 4.f;
    float expected = -m_pi * 3.f / 4.f;
    float epsilon = 2.f * m_pi / std::pow(2.f, 30);

    AngularFixedPoint<31> fixed(input);
    float result = fixed.toFloat();

    EXPECT_NEAR(result, expected, epsilon);
}

TEST(AngularFixedPointTest, ZeroIsConserved)
{
    float input = 0;
    float expected = 0;
    float epsilon = 2.f * m_pi / std::pow(2.f, 30);

    AngularFixedPoint<31> fixed(input);
    float result = fixed.toFloat();

    EXPECT_NEAR(result, expected, epsilon);
}


TEST(AngularFixedPointTest, AngleIsCyclic)
{
    float input = m_pi * 7.f / 4.f;
    float expected = - m_pi / 4.f;
    float epsilon = 2.f * m_pi / std::pow(2.f, 30);

    AngularFixedPoint<31> fixed(input);
    float result = fixed.toFloat();
    EXPECT_NEAR(result, expected, epsilon);
}

TEST(AngularFixedPointTest, SubstractionWorks)
{
    float a = 2.f;
    float b = 1.f;
    float epsilon = 2.f * m_pi / std::pow(2.f, 30);

    AngularFixedPoint<31> aFixed(a);
    AngularFixedPoint<31> bFixed(b);
    AngularFixedPoint<31> cFixed = aFixed - bFixed;

    float result = cFixed.toFloat();
    float expected = a - b;
    EXPECT_NEAR(result, expected, epsilon);
}

TEST(AngularFixedPointTest, SubstractionIsCyclic)
{
    float a = -m_pi * 3.f / 4.f;
    float b = m_pi;
    float expected = m_pi / 4.f;
    float epsilon = 2.f * m_pi / std::pow(2.f, 30);

    AngularFixedPoint<31> aFixed(a);
    AngularFixedPoint<31> bFixed(b);
    AngularFixedPoint<31> cFixed = aFixed - bFixed;

    float result = cFixed.toFloat();
    EXPECT_NEAR(result, expected, epsilon);
}

TEST(AngularFixedPointTest, NegateWorks)
{
    float a = 2.f;
    float epsilon = 2.f * m_pi / std::pow(2.f, 30);

    AngularFixedPoint<31> aFixed(a);
    AngularFixedPoint<31> cFixed = -aFixed;

    float result = cFixed.toFloat();
    float expected = -a;
    EXPECT_NEAR(result, expected, epsilon);
}

TEST(AngularFixedPointTest, SubstractionIsCyclicLowerResolution)
{
    float a = -m_pi * 3.f / 4.f;
    float b = m_pi;
    float expected = m_pi / 4.f;
    float epsilon = 2.f * m_pi / std::pow(2.f, 15);

    AngularFixedPoint<15> aFixed(a);
    AngularFixedPoint<15> bFixed(b);
    AngularFixedPoint<15> cFixed = aFixed - bFixed;

    float result = cFixed.toFloat();
    EXPECT_NEAR(result, expected, epsilon);
}

TEST(AngularFixedPointTest, IsInferiorWorks)
{
    float a = m_pi / 2.f;
    float b = m_pi * 3.f / 4.f;
    bool expected =  a <= b;

    AngularFixedPoint<15> aFixed(a);
    bool result = aFixed <= b;

    EXPECT_EQ(result, expected);
}

TEST(AngularFixedPointTest, IsSuperiorWorks)
{
    float a = m_pi / 2.f;
    float b = m_pi * 3.f / 4.f;
    bool expected =  a >= b;

    AngularFixedPoint<15> aFixed(a);
    bool result = aFixed >= b;

    EXPECT_EQ(result, expected);
}
