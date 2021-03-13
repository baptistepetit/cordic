#include <iostream>
#include <memory>
#include <vector>

#include "angular_fixed_point.hpp"
#include "cordic.hpp"
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

    CosSinPair<Linear> cosSin;
    std::unique_ptr<Cordic<Linear, Angular>> cordic =
        std::make_unique<Cordic<Linear, Angular>>(cordicIterations);

    std::cout << "Angular::max() " << Angular::max() << std::endl;
    std::cout << "Angular::lowest() " << Angular::lowest() << std::endl;

    std::cout << "Cordic Angles are :" << std::endl;
    for (unsigned i = 0; i < angleLut.size(); i++) {
        std::cout << "Angle " << i
            << " is " << angleLut.at(i)
            << std::endl;
    }
    std::cout << "Cordic Gain is " << cordicGain << std::endl;

    cosSin = cordic->calculateCordicCosine(0.4f);
    std::cout << "Result of cordic->calculateCordicCosine("
        << Angular(0.4f) << ") is: "
        << "{ cos: " << cosSin.cos
        << ", sin: " << cosSin.sin
        << " }" << std::endl;

    cosSin = cordic->calculateCordicCosine(-0.4f);
    std::cout << "Result of cordic->calculateCordicCosine("
        << Angular(-0.4f) << ") is: "
        << "{ cos: " << cosSin.cos
        << ", sin: " << cosSin.sin
        << " }" << std::endl;

    cosSin = cordic->calculateCordicCosine(-2.f);
    std::cout << "Result of cordic->calculateCordicCosine("
        << Angular(-2.f) << ") is: "
        << "{ cos: " << cosSin.cos
        << ", sin: " << cosSin.sin
        << " }" << std::endl;

    return 0;
}
