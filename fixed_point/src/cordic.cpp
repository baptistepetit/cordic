#include "cordic.hpp"

Cordic::Cordic()
{
}

Cordic::~Cordic()
{
}

CordicParameters Cordic::preRotateIntoRange(const CordicParameters &parameters)
{
    return {{0, 0}, 0};
}

Position Cordic::calculateCordicRotation(const CordicParameters &parameters)
{
    return {0, 0};
}

CosSinPair Cordic::calculateCordicCosine(const float &targetAngle)
{
    return {0, 0};
}
