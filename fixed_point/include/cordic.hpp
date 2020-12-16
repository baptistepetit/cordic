#pragma once

#include <vector>

#include "types.hpp"

class Cordic
{
public:
    Cordic();
    ~Cordic();

    CosSinPair calculateCordicCosine(const float &targetAngle);

private:
    float gain;
    std::vector<float> angleLut;

    CordicParameters preRotateIntoRange(const CordicParameters &parameters);
    Position calculateCordicRotation(const CordicParameters &parameters);
};
