#include <iostream>

#include "angular_fixed_point.hpp"
#include "fixed_point.hpp"
#include "types.hpp"

int main() {

    std::cout << AngularFixedPoint<15>::max() << std::endl;
    std::cout << AngularFixedPoint<15>::lowest() << std::endl;
    std::cout << AngularFixedPoint<15>(m_pi / 2.f) << std::endl;
    std::cout
        << FixedPoint<2, 13>(static_cast<float>(0.6072529353859136))
        << std::endl;

    return 0;
}
