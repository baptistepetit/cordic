#pragma once

#include <cmath>
#include <iostream>
#include <memory>

#include "angular_fixed_point.hpp"
#include "cordic.hpp"
#include "fixed_point.hpp"
#include "types.hpp"

template<int M, int F, int B>
inline void measureCordicError(const int _measureNumber = -1) {
    unsigned measureNumber = _measureNumber;
    if (_measureNumber == -1) {
        measureNumber = static_cast<unsigned>(1.f / AngularFixedPoint<B>::resolution);
    }

    std::unique_ptr<Cordic<FixedPoint<M, F>, AngularFixedPoint<B>>> cordic =
        std::make_unique<Cordic<FixedPoint<M, F>, AngularFixedPoint<B>>>();

    float error = 0;
    float standardDeviation = 0;
    for (unsigned i = 0; i < measureNumber; i++) {
        float currentValue =
            static_cast<float>(i) / static_cast<float>(measureNumber) * 2.f * m_pi - m_pi;
        CosSinPair<FixedPoint<M, F>> cosSin = cordic->calculateCordicCosine(currentValue);
        float cmathCosDifference = (cosf(currentValue) - cosSin.cos.toFloat());
        float cmathSinDifference = (sinf(currentValue) - cosSin.sin.toFloat());
        error += cmathCosDifference;
        error += cmathSinDifference;
        standardDeviation += powf(cmathCosDifference, 2);
        standardDeviation += powf(cmathSinDifference, 2);
    }
    error /= static_cast<float>(2 * measureNumber);
    standardDeviation /= static_cast<float>(2 * measureNumber);
    standardDeviation = sqrtf(standardDeviation);

    std::cout << std::endl
        << "####################################################" << std::endl
        << " Linear Fixed Point is represented with "
        << M << "." << F << " bits" << std::endl
        << " Angular Fixed Point is represented with "
        << B << " bits" << std::endl
        << "####################################################"
        << std::endl;

    std::cout
        << "Mean error compared with cmath sin and cos over " << measureNumber
        << " values approximates to: " << error
        << " with a standard deviation of " << standardDeviation
        << "."
        << std::endl;

    std::cout
        << "Meaning error is expected to be within +"
        << (error + 3 * standardDeviation)
        << "/"
        << (error - 3 * standardDeviation)
        << " with 99.7% confidence assuming error is normally distributed."
        << std::endl;
}
