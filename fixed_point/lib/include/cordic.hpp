#pragma once

#include <cmath>
#include <stdexcept>
#include <vector>

#include "types.hpp"

template <typename LinearType, typename AngularType>
class Cordic
{
public:
    Cordic();
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
    gain = LinearType(0.6072529353859136);
    angleLut = std::vector<AngularType>({
        AngularType(static_cast<float>(0.7853981633974483)),
        AngularType(static_cast<float>(0.4636476090008061)),
        AngularType(static_cast<float>(0.24497866312686414)),
        AngularType(static_cast<float>(0.12435499454676144)),
        AngularType(static_cast<float>(0.06241880999595735)),
        AngularType(static_cast<float>(0.031239833430268277)),
        AngularType(static_cast<float>(0.015623728620476831)),
        AngularType(static_cast<float>(0.007812341060101111)),
        AngularType(static_cast<float>(0.0039062301319669718)),
        AngularType(static_cast<float>(0.0019531225164788188)),
        AngularType(static_cast<float>(0.0009765621895593195)),
        AngularType(static_cast<float>(0.0004882812111948983)),
        AngularType(static_cast<float>(0.00024414062014936177)),
        AngularType(static_cast<float>(0.00012207031189367021)),
        AngularType(static_cast<float>(0.00006103515617420877))
    });
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
