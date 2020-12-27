#pragma once

#include <cmath>

constexpr float m_pi = M_PI;

template<typename T>
class Position
{
public:
    Position() {}
    Position(T _x, T _y)
    {
        x = _x;
        y = _y;
    }
    ~Position() {}

    T x;
    T y;
};

template<typename T>
class CordicParameters
{
public:
    CordicParameters() {}

    CordicParameters(T _xInit, T _yInit, float _targetAngle)
    {
        initPosition.x = _xInit;
        initPosition.y = _yInit;
        targetAngle = _targetAngle;
    }
    ~CordicParameters() {}

    Position<T> initPosition;
    float targetAngle;
};

template<typename T>
class CosSinPair
{
public:
    CosSinPair() {}
    CosSinPair(T _cos, T _sin)
    {
        cos = _cos;
        sin = _sin;
    }
    ~CosSinPair() {}

    T cos;
    T sin;
};
