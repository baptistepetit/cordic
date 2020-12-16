#include <memory>

#include "cordic.hpp"

int main(int argc, char **argv) {
    std::unique_ptr<Cordic> cordic = std::make_unique<Cordic>();
    return 0;
}
