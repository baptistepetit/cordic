#include <memory>

#include "cordic.hpp"
#include "fixed_point.hpp"

int main(int argc, char **argv) {
    std::unique_ptr<Cordic<FixedPoint<16, 16>>> cordic = std::make_unique<Cordic<FixedPoint<16, 16>>>();
    return 0;
}
