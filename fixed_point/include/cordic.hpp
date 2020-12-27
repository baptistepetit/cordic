#pragma once

#include <cmath>
#include <stdexcept>
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

    CordicParameters<LinearType, float> preRotateIntoRange(const CordicParameters<LinearType, float> &parameters);
    Position<LinearType> calculateCordicRotation(const CordicParameters<LinearType, float> &parameters);
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
CordicParameters<LinearType, float> Cordic<LinearType>::preRotateIntoRange(const CordicParameters<LinearType, float> &parameters)
{
    CordicParameters<LinearType, float> rotatedParams;

    if (parameters.targetAngle >= -m_pi/4 && parameters.targetAngle <= m_pi/4) {
        rotatedParams = parameters;
    } else if (parameters.targetAngle >= m_pi/4 && parameters.targetAngle <= 3*m_pi/4) {
        rotatedParams = CordicParameters<LinearType, float>(
            -parameters.initPosition.y,
            parameters.initPosition.x,
            parameters.targetAngle - m_pi / 2
        );
    } else if (parameters.targetAngle >= 3*m_pi/4 && parameters.targetAngle <= m_pi) {
        rotatedParams = CordicParameters<LinearType, float>(
            -parameters.initPosition.x,
            -parameters.initPosition.y,
            parameters.targetAngle - m_pi
        );
    } else if (parameters.targetAngle >= -m_pi && parameters.targetAngle <= -3*m_pi/4) {
        rotatedParams = CordicParameters<LinearType, float>(
            -parameters.initPosition.x,
            -parameters.initPosition.y,
            parameters.targetAngle + m_pi
        );
    } else if (parameters.targetAngle >= -3*m_pi/4 && parameters.targetAngle <= -m_pi/4) {
        rotatedParams = CordicParameters<LinearType, float>(
            -parameters.initPosition.y,
            -parameters.initPosition.x,
            parameters.targetAngle + m_pi / 2
        );
    } else {
        throw std::runtime_error("error out of range [-Pi; Pi]");
    }

    return rotatedParams;
}

template <typename LinearType>
Position<LinearType> Cordic<LinearType>::calculateCordicRotation(const CordicParameters<LinearType, float> &parameters)
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
    const CordicParameters<LinearType, float> parameters(gain, LinearType(0), targetAngle);
    const Position<LinearType> rotatedPosition = calculateCordicRotation(
        preRotateIntoRange(parameters)
    );

    return CosSinPair<LinearType>(rotatedPosition.x, rotatedPosition.y);
}
