#include <memory>

#include "angular_fixed_point.hpp"
#include "cordic.hpp"
#include "fixed_point.hpp"

int main(int argc, char **argv) {
    std::unique_ptr<Cordic<FixedPoint<16, 16>, AngularFixedPoint<32>>> cordic =
        std::make_unique<Cordic<FixedPoint<16, 16>, AngularFixedPoint<32>>>();
    return 0;
}
