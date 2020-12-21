#pragma once

#include <cmath>
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

CordicParameters<float> Cordic::preRotateIntoRange(const CordicParameters<float> &parameters)
{
    CordicParameters<float> rotatedParams;

    if (parameters.targetAngle >= 0 && parameters.targetAngle <= M_PI/4) {
        rotatedParams = parameters;
    } else if (parameters.targetAngle >= M_PI/4 && parameters.targetAngle <= 3*M_PI/4) {
        rotatedParams = CordicParameters<float>(
            -parameters.initPosition.y,
            parameters.initPosition.x,
            parameters.targetAngle - M_PI / 2
        );
    } else if (parameters.targetAngle >= 3*M_PI/4 && parameters.targetAngle <= 5*M_PI/4) {
        rotatedParams = CordicParameters<float>(
            -parameters.initPosition.x,
            -parameters.initPosition.y,
            parameters.targetAngle - M_PI
        );
    } else if (parameters.targetAngle >= 5*M_PI/4 && parameters.targetAngle <= 7*M_PI/4) {
        rotatedParams = CordicParameters<float>(
            parameters.initPosition.y,
            -parameters.initPosition.x,
            parameters.targetAngle - 3 * M_PI / 2
        );
    } else {  // parameters.targetAngle >= 7*M_PI/4 && parameters.targetAngle <= 2*M_PI
        rotatedParams = CordicParameters<float>(
            parameters.initPosition.x,
            parameters.initPosition.y,
            parameters.targetAngle - 2 * M_PI
        );
    }

    return rotatedParams;
}

Position<float> Cordic::calculateCordicRotation(const CordicParameters<float> &parameters)
{
    Position<float> position(parameters.initPosition.x, parameters.initPosition.y);
    float phase = parameters.targetAngle;

    for (unsigned i = 0; i < angleLut.size(); i++) {
        Position<float> positionNext;
        float sign = phase < 0 ? -1.f : 1.f;

        positionNext.x = position.x - sign * position.y / (1 << i);
        positionNext.y = position.y + sign * position.x / (1 << i);
        float phaseNext = phase - sign * angleLut.at(i);

        position = positionNext;
        phase = phaseNext;
    }

    return position;
}

CosSinPair<float> Cordic::calculateCordicCosine(const float &targetAngle)
{
    const CordicParameters<float> parameters(gain, 0, targetAngle);
    const Position<float> rotatedPosition = calculateCordicRotation(
        preRotateIntoRange(parameters)
    );

    return CosSinPair<float>(rotatedPosition.x, rotatedPosition.y);
}
