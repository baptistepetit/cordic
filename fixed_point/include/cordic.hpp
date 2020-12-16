#pragma once

#include <vector>

struct Position {
    float x;
    float y;
};

struct CordicParameters {
    Position initialPosition;
    float targetAngle;
};

struct CosSinPair {
    float cos;
    float sin;
};

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
