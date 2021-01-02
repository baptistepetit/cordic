#include <cmath>
#include <iostream>
#include <memory>

#include "angular_fixed_point.hpp"
#include "cordic.hpp"
#include "fixed_point.hpp"
#include "types.hpp"

constexpr unsigned simulationSteps = 5000000;

int main() {
    std::unique_ptr<Cordic<FixedPoint<16, 16>, AngularFixedPoint<32>>> cordic =
        std::make_unique<Cordic<FixedPoint<16, 16>, AngularFixedPoint<32>>>();

    float error = 0;
    float standardDeviation = 0;
    for (unsigned i = 0; i < simulationSteps; i++) {
        float currentValue =
            static_cast<float>(i) / static_cast<float>(simulationSteps) * 2.f * m_pi - m_pi;
        CosSinPair<FixedPoint<16, 16>> cosSin = cordic->calculateCordicCosine(currentValue);
        float cmathCosDifference = (cosf(currentValue) - cosSin.cos.toFloat());
        float cmathSinDifference = (sinf(currentValue) - cosSin.sin.toFloat());
        error += cmathCosDifference;
        error += cmathSinDifference;
        standardDeviation += powf(cmathCosDifference, 2);
        standardDeviation += powf(cmathSinDifference, 2);
    }
    error /= static_cast<float>(2 * simulationSteps);
    standardDeviation /= static_cast<float>(2 * simulationSteps);
    standardDeviation = sqrtf(standardDeviation);

    std::cout
        << "Mean error compared with cmath sin and cos over " << simulationSteps
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

    return 0;
}
