#include <cmath>

#include "gtest/gtest.h"

#include "cordic.hpp"
#include "fixed_point.hpp"
#include "types.hpp"

class CordicTest : public testing::TestWithParam<float> {
protected:
    void SetUp() override {
        cordic = std::make_unique<Cordic<FixedPoint<16, 16>>>();
    };
    std::unique_ptr<Cordic<FixedPoint<16, 16>>> cordic;
};


TEST_P(CordicTest, CosineCalculationsAreCorrect)
{
    float epsilon = 0.001;
    CosSinPair<FixedPoint<16, 16>> calculatedCosSinPair = cordic->calculateCordicCosine(GetParam());
    CosSinPair<float> expectedCosSinPair(
        static_cast<float>(cos(GetParam())),
        static_cast<float>(sin(GetParam()))
    );

    EXPECT_NEAR(calculatedCosSinPair.cos.toFloat(), expectedCosSinPair.cos, epsilon);
    EXPECT_NEAR(calculatedCosSinPair.sin.toFloat(), expectedCosSinPair.sin, epsilon);
}

INSTANTIATE_TEST_SUITE_P(
    CordicTestParameterized,
    CordicTest,
    testing::Values(
        0.f,
        1.f,
        3.f,
        M_PI / 4.f,
        3.f * M_PI / 4.f,
        M_PI,
        5 * M_PI / 4.f
    )
);
