#pragma once

#include <cmath>
#include <vector>

#include "types.hpp"
#include "utils.hpp"

template <typename LinearType>
class Cordic
{
public:
    Cordic();
    ~Cordic();

    CosSinPair<LinearType> calculateCordicCosine(const float &targetAngle);

private:
    LinearType gain;
    std::vector<float> angleLut;

    CordicParameters<LinearType> preRotateIntoRange(const CordicParameters<LinearType> &parameters);
    Position<LinearType> calculateCordicRotation(const CordicParameters<LinearType> &parameters);
};

template <typename LinearType>
Cordic<LinearType>::Cordic()
{
    gain = LinearType(0.6072529353859136);
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

template <typename LinearType>
Cordic<LinearType>::~Cordic()
{
}

template <typename LinearType>
CordicParameters<LinearType> Cordic<LinearType>::preRotateIntoRange(const CordicParameters<LinearType> &parameters)
{
    CordicParameters<LinearType> rotatedParams;

    if (parameters.targetAngle >= 0 && parameters.targetAngle <= M_PI/4) {
        rotatedParams = parameters;
    } else if (parameters.targetAngle >= M_PI/4 && parameters.targetAngle <= 3*M_PI/4) {
        rotatedParams = CordicParameters<LinearType>(
            -parameters.initPosition.y,
            parameters.initPosition.x,
            parameters.targetAngle - M_PI / 2
        );
    } else if (parameters.targetAngle >= 3*M_PI/4 && parameters.targetAngle <= 5*M_PI/4) {
        rotatedParams = CordicParameters<LinearType>(
            -parameters.initPosition.x,
            -parameters.initPosition.y,
            parameters.targetAngle - M_PI
        );
    } else if (parameters.targetAngle >= 5*M_PI/4 && parameters.targetAngle <= 7*M_PI/4) {
        rotatedParams = CordicParameters<LinearType>(
            parameters.initPosition.y,
            -parameters.initPosition.x,
            parameters.targetAngle - 3 * M_PI / 2
        );
    } else {  // parameters.targetAngle >= 7*M_PI/4 && parameters.targetAngle <= 2*M_PI
        rotatedParams = CordicParameters<LinearType>(
            parameters.initPosition.x,
            parameters.initPosition.y,
            parameters.targetAngle - 2 * M_PI
        );
    }

    return rotatedParams;
}

template <typename LinearType>
Position<LinearType> Cordic<LinearType>::calculateCordicRotation(const CordicParameters<LinearType> &parameters)
{
    Position<LinearType> position(parameters.initPosition.x, parameters.initPosition.y);
    float phase = parameters.targetAngle;

    for (unsigned i = 0; i < angleLut.size(); i++) {
        Position<LinearType> positionNext;
        float sign = phase < 0 ? -1.f : 1.f;

        positionNext.x = position.x - multiplyBySignOf<LinearType>(sign, (position.y >> i));
        positionNext.y = position.y + multiplyBySignOf<LinearType>(sign, (position.x >> i));
        float phaseNext = phase - sign * angleLut.at(i);

        position = positionNext;
        phase = phaseNext;
    }

    return position;
}

template <typename LinearType>
CosSinPair<LinearType> Cordic<LinearType>::calculateCordicCosine(const float &targetAngle)
{
    const CordicParameters<LinearType> parameters(gain, LinearType(0), targetAngle);
    const Position<LinearType> rotatedPosition = calculateCordicRotation(
        preRotateIntoRange(parameters)
    );

    return CosSinPair<LinearType>(rotatedPosition.x, rotatedPosition.y);
}
