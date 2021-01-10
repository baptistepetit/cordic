#include "gtest/gtest.h"

#include "utils.hpp"

TEST(ToHexStringTest, IntegerNumberOfHexSymbolsWorks)
{
    int32_t input = 0xFC;
    std::string expected = "FC";
    std::string result = toHexString<8>(input);
    EXPECT_EQ(result, expected);
}

TEST(ToHexStringTest, NonIntegerNumberOfHexSymbolsWorks)
{
    int32_t input = 0xFC;
    std::string expected = "7C";
    std::string result = toHexString<7>(input);
    EXPECT_EQ(result, expected);
}
