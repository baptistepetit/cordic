#pragma once

#include <vector>

#include "types.hpp"

class Cordic
{
public:
    Cordic();
    ~Cordic();

    CosSinPair<float> calculateCordicCosine(const float &targetAngle);

private:
    float gain;
    std::vector<float> angleLut;

    CordicParameters<float> preRotateIntoRange(const CordicParameters<float> &parameters);
    Position<float> calculateCordicRotation(const CordicParameters<float> &parameters);
};
