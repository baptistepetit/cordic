#include <cmath>

#include "gtest/gtest.h"

#include "cordic.hpp"

class CordicTest : public testing::TestWithParam<float> {
protected:
    void SetUp() override {
        cordic = std::make_unique<Cordic>();
    };
    std::unique_ptr<Cordic> cordic;
};


TEST_P(CordicTest, CosineCalculationsAreCorrect)
{
    float epsilon = 0.001;
    CosSinPair calculatedCosSinPair = cordic->calculateCordicCosine(GetParam());
    CosSinPair expectedCosSinPair = CosSinPair{
        .cos=static_cast<float>(cos(GetParam())),
        .sin=static_cast<float>(sin(GetParam()))
    };

    EXPECT_NEAR(calculatedCosSinPair.cos, expectedCosSinPair.cos, epsilon);
    EXPECT_NEAR(calculatedCosSinPair.sin, expectedCosSinPair.sin, epsilon);
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
