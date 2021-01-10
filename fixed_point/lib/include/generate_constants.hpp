#pragma once

#include <cmath>
#include <vector>
#include <iostream>

#include "types.hpp"

template<typename AngularType>
inline std::vector<AngularType> generateAngleLut(unsigned size)
{
    std::vector<AngularType> angleLut;
    for (unsigned i = 0; i < size; i++) {
        angleLut.push_back(
            AngularType(atanf(powf(2.f, -static_cast<float>(i))))
        );
    }
    return angleLut;
}

template<typename LinearType>
inline LinearType generateCordicGain(unsigned size)
{
    float gain = 1.f;
    const std::vector<float> angleLut = generateAngleLut<float>(size);
    for (unsigned i = 0; i < angleLut.size(); i++) {
        gain *= cosf(angleLut.at(i));
    }
    return LinearType(gain);
}
