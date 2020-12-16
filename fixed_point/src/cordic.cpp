#include "cordic.hpp"

Cordic::Cordic()
{
    gain = 0.6072529353859136;
    angleLut = std::vector<float>({
        0.7853981633974483,
        0.4636476090008061,
        0.24497866312686414,
        0.12435499454676144,
        0.06241880999595735,
        0.031239833430268277,
        0.015623728620476831,
        0.007812341060101111,
        0.0039062301319669718,
        0.0019531225164788188,
        0.0009765621895593195,
        0.0004882812111948983,
        0.00024414062014936177,
        0.00012207031189367021,
        0.00006103515617420877
    });
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
