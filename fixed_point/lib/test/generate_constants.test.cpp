#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "angular_fixed_point.hpp"
#include "fixed_point.hpp"
#include "generate_constants.hpp"

TEST(GenerateConstantsTest, AngleLutIsCorrect)
{
    std::vector<AngularFixedPoint<15>> result =
        generateAngleLut<AngularFixedPoint<15>>(15);
    std::vector<AngularFixedPoint<15>> expected({
        AngularFixedPoint<15>(static_cast<float>(0.7853981633974483)),
        AngularFixedPoint<15>(static_cast<float>(0.4636476090008061)),
        AngularFixedPoint<15>(static_cast<float>(0.24497866312686414)),
        AngularFixedPoint<15>(static_cast<float>(0.12435499454676144)),
        AngularFixedPoint<15>(static_cast<float>(0.06241880999595735)),
        AngularFixedPoint<15>(static_cast<float>(0.031239833430268277)),
        AngularFixedPoint<15>(static_cast<float>(0.015623728620476831)),
        AngularFixedPoint<15>(static_cast<float>(0.007812341060101111)),
        AngularFixedPoint<15>(static_cast<float>(0.0039062301319669718)),
        AngularFixedPoint<15>(static_cast<float>(0.0019531225164788188)),
        AngularFixedPoint<15>(static_cast<float>(0.0009765621895593195)),
        AngularFixedPoint<15>(static_cast<float>(0.0004882812111948983)),
        AngularFixedPoint<15>(static_cast<float>(0.00024414062014936177)),
        AngularFixedPoint<15>(static_cast<float>(0.00012207031189367021)),
        AngularFixedPoint<15>(static_cast<float>(0.00006103515617420877))
    });

    EXPECT_THAT(result, ::testing::ElementsAreArray(expected));
}

TEST(GenerateConstantsTest, CordicGainIsCorrect)
{
    FixedPoint<2, 13> result = generateCordicGain<FixedPoint<2, 13>>(15);
    const FixedPoint<2, 13> expected(static_cast<float>(0.6072529353859136));

    EXPECT_EQ(expected, result);
}
