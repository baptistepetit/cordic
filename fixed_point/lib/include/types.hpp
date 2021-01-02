#pragma once

#include <cmath>

constexpr float m_pi = static_cast<float>(M_PI);

template<typename LinearType>
class Position
{
public:
    Position() {}
    Position(LinearType _x, LinearType _y):
    x(_x),
    y(_y)
    {}
    ~Position() {}

    LinearType x;
    LinearType y;
};

template<typename LinearType, typename AngularType>
class CordicParameters
{
public:
    CordicParameters() {}

    CordicParameters(LinearType _xInit, LinearType _yInit, AngularType _targetAngle):
    initPosition(_xInit, _yInit),
    targetAngle(_targetAngle)
    {}
    ~CordicParameters() {}

    Position<LinearType> initPosition;
    AngularType targetAngle;
};

template<typename LinearType>
class CosSinPair
{
public:
    CosSinPair() {}
    CosSinPair(LinearType _cos, LinearType _sin):
    cos(_cos),
    sin(_sin)
    {}
    ~CosSinPair() {}

    LinearType cos;
    LinearType sin;
};
