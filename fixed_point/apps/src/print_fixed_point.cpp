#include <iostream>
#include <vector>

#include "angular_fixed_point.hpp"
#include "fixed_point.hpp"
#include "generate_constants.hpp"
#include "types.hpp"

typedef AngularFixedPoint<15> Angular;
typedef FixedPoint<2, 13> Linear;

int main() {

    constexpr unsigned cordicIterations = 12;
    const std::vector<Angular> angleLut =
        generateAngleLut<Angular>(cordicIterations);
    const Linear cordicGain = generateCordicGain<Linear>(cordicIterations);

    std::cout << "Angular::max() " << Angular::max() << std::endl;
    std::cout << "Angular::lowest() " << Angular::lowest() << std::endl;

    std::cout << "Cordic Angles are :" << std::endl;
    for (unsigned i = 0; i < angleLut.size(); i++) {
        std::cout << "Angle " << i
            << " is " << angleLut.at(i)
            << std::endl;
    }
    std::cout << "Cordic Gain is " << cordicGain << std::endl;

    return 0;
}
