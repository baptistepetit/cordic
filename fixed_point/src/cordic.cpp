#include <cmath>

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
    CordicParameters rotatedParams;

    if (parameters.targetAngle >= 0 && parameters.targetAngle <= M_PI/4) {
        rotatedParams = parameters;
    } else if (parameters.targetAngle >= M_PI/4 && parameters.targetAngle <= 3*M_PI/4) {
        rotatedParams = CordicParameters{
            .initialPosition=Position{
                .x=-parameters.initialPosition.y,
                .y=parameters.initialPosition.x
            },
            .targetAngle=(parameters.targetAngle - M_PI/2)
        };
    } else if (parameters.targetAngle >= 3*M_PI/4 && parameters.targetAngle <= 5*M_PI/4) {
        rotatedParams = CordicParameters{
            .initialPosition=Position{
                .x=-parameters.initialPosition.x,
                .y=-parameters.initialPosition.y
            },
            .targetAngle=(parameters.targetAngle - M_PI)
        };
    } else if (parameters.targetAngle >= 5*M_PI/4 && parameters.targetAngle <= 7*M_PI/4) {
        rotatedParams = CordicParameters{
            .initialPosition=Position{
                .x=parameters.initialPosition.y,
                .y=-parameters.initialPosition.x
            },
            .targetAngle=(parameters.targetAngle - 3*M_PI/2)
        };
    } else {  // parameters.targetAngle >= 7*M_PI/4 && parameters.targetAngle <= 2*M_PI
        rotatedParams = CordicParameters{
            .initialPosition=Position{
                .x=parameters.initialPosition.x,
                .y=parameters.initialPosition.y
            },
            .targetAngle=(parameters.targetAngle - 2*M_PI)
        };
    }

    return rotatedParams;
}

Position Cordic::calculateCordicRotation(const CordicParameters &parameters)
{
    float x = parameters.initialPosition.x;
    float y = parameters.initialPosition.y;
    float phase = parameters.targetAngle;

    for (unsigned i = 0; i < angleLut.size(); i++) {
        float sign = phase < 0 ? -1.f : 1.f;

        float xNext = x - sign * y / (1 << i);
        float yNext = y + sign * x / (1 << i);
        float phaseNext = phase - sign * angleLut.at(i);

        x = xNext;
        y = yNext;
        phase = phaseNext;
    }

    return Position{ .x=x, .y=y };
}

CosSinPair Cordic::calculateCordicCosine(const float &targetAngle)
{
    const CordicParameters parameters = {
        .initialPosition=Position{ .x= gain, .y= 0},
        .targetAngle=targetAngle
    };
    const Position rotatedPosition = calculateCordicRotation(
        preRotateIntoRange(parameters)
    );

    return CosSinPair{ .cos=rotatedPosition.x, .sin=rotatedPosition.y };
}
