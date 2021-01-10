#pragma once

#include <array>
#include <cstdint>
#include <string>

template<int B>
std::string toHexString(int32_t value) {
    std::string result("");

    const std::array<std::string, 16> hexadecimalSymbols =
        {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"};
    const int32_t oneSymbolBitMask = 0xF;

    for (int i = 0; i < B; i +=4)
    {
        char currentSymbol = 0;

        if ((B - i) >= 4) {
            // All the data from the 4 bits is valid
            currentSymbol = static_cast<char>(value & oneSymbolBitMask);
        } else {
            // Invalid data is masked out
            int32_t customBitMask = 0;
            for (int j = 0; j < (B - i); j++) {
                customBitMask <<= 1;
                customBitMask += 1;
            }
            currentSymbol = static_cast<char>(value & customBitMask);
        }
        if ((currentSymbol >= 0) && (currentSymbol < 16)) {
            result = hexadecimalSymbols.at(currentSymbol) + result;
        }
        value >>= 4;
    }

    return result;
}
