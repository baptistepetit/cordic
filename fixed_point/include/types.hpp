#pragma once

class Position
{
public:
    Position() {}
    Position(float _x, float _y)
    {
        x = _x;
        y = _y;
    }
    ~Position() {}

    float x;
    float y;
};

class CordicParameters
{
public:
    CordicParameters() {}

    CordicParameters(float _xInit, float _yInit, float _targetAngle)
    {
        initPosition.x = _xInit;
        initPosition.y = _yInit;
        targetAngle = _targetAngle;
    }
    ~CordicParameters() {}

    Position initPosition;
    float targetAngle;
};

class CosSinPair
{
public:
    CosSinPair() {}
    CosSinPair(float _cos, float _sin)
    {
        cos = _cos;
        sin = _sin;
    }
    ~CosSinPair() {}

    float cos;
    float sin;
};
