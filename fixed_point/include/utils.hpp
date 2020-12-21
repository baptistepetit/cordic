#pragma once

template<typename T>
inline T multiplyBySignOf(float signedValue, T valueToMultiply)
{
    if (signedValue < 0) {
        return -valueToMultiply;
    } else {
        return valueToMultiply;
    }
}
