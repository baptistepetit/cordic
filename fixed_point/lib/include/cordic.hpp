#pragma once

#include <cmath>
#include <stdexcept>
#include <vector>

#include "generate_constants.hpp"
#include "types.hpp"

template <typename LinearType, typename AngularType>
class Cordic
{
public:
    Cordic();
    Cordic(unsigned iterations);
    ~Cordic();

    CosSinPair<LinearType> calculateCordicCosine(const float &targetAngle);

private:
    LinearType gain;
    std::vector<AngularType> angleLut;

    CordicParameters<LinearType, AngularType> preRotateIntoRange(const CordicParameters<LinearType, AngularType> &parameters);
    Position<LinearType> calculateCordicRotation(const CordicParameters<LinearType, AngularType> &parameters);
};

template <typename LinearType, typename AngularType>
Cordic<LinearType, AngularType>::Cordic()
{
    const unsigned defaultIterationNb = 15;
    gain = generateCordicGain<LinearType>(defaultIterationNb);
    angleLut = generateAngleLut<AngularType>(defaultIterationNb);
}

template <typename LinearType, typename AngularType>
Cordic<LinearType, AngularType>::Cordic(unsigned iterations)
{
    gain = generateCordicGain<LinearType>(iterations);
    angleLut = generateAngleLut<AngularType>(iterations);
}

template <typename LinearType, typename AngularType>
Cordic<LinearType, AngularType>::~Cordic()
{
}

template <typename LinearType, typename AngularType>
CordicParameters<LinearType, AngularType> Cordic<LinearType, AngularType>::preRotateIntoRange(const CordicParameters<LinearType, AngularType> &parameters)
{
    CordicParameters<LinearType, AngularType> rotatedParams;

    if (parameters.targetAngle >= -m_pi/4 && parameters.targetAngle <= m_pi/4) {
        rotatedParams = parameters;
    } else if (parameters.targetAngle >= m_pi/4 && parameters.targetAngle <= 3*m_pi/4) {
        rotatedParams = CordicParameters<LinearType, AngularType>(
            -parameters.initPosition.y,
            parameters.initPosition.x,
            parameters.targetAngle - m_pi / 2
        );
    } else if (parameters.targetAngle >= 3*m_pi/4 && parameters.targetAngle <= AngularType::max()) {
        rotatedParams = CordicParameters<LinearType, AngularType>(
            -parameters.initPosition.x,
            -parameters.initPosition.y,
            parameters.targetAngle - m_pi
        );
    } else if (parameters.targetAngle >= AngularType::lowest() && parameters.targetAngle <= -3*m_pi/4) {
        rotatedParams = CordicParameters<LinearType, AngularType>(
            -parameters.initPosition.x,
            -parameters.initPosition.y,
            parameters.targetAngle + m_pi
        );
    } else if (parameters.targetAngle >= -3*m_pi/4 && parameters.targetAngle <= -m_pi/4) {
        rotatedParams = CordicParameters<LinearType, AngularType>(
            -parameters.initPosition.y,
            -parameters.initPosition.x,
            parameters.targetAngle + m_pi / 2
        );
    } else {
        throw std::runtime_error("error out of range [-Pi; Pi[");
    }

    return rotatedParams;
}

template <typename LinearType, typename AngularType>
Position<LinearType> Cordic<LinearType, AngularType>::calculateCordicRotation(const CordicParameters<LinearType, AngularType> &parameters)
{
    Position<LinearType> position(parameters.initPosition.x, parameters.initPosition.y);
    AngularType phase = parameters.targetAngle;

    for (unsigned i = 0; i < angleLut.size(); i++) {
        Position<LinearType> positionNext;
        AngularType phaseNext;

        if (phase >= 0) {
            positionNext.x = position.x - (position.y >> i);
            positionNext.y = position.y + (position.x >> i);
            phaseNext = phase - angleLut.at(i);
        } else {
            positionNext.x = position.x + (position.y >> i);
            positionNext.y = position.y - (position.x >> i);
            phaseNext = phase + angleLut.at(i);
        }

        position = positionNext;
        phase = phaseNext;
    }

    return position;
}

template <typename LinearType, typename AngularType>
CosSinPair<LinearType> Cordic<LinearType, AngularType>::calculateCordicCosine(const float &targetAngle)
{
    const CordicParameters<LinearType, AngularType> parameters(gain, LinearType(0), AngularType(targetAngle));
    const Position<LinearType> rotatedPosition = calculateCordicRotation(
        preRotateIntoRange(parameters)
    );

    return CosSinPair<LinearType>(rotatedPosition.x, rotatedPosition.y);
}
