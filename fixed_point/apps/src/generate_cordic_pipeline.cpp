#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "../include/generate_cordic_pipeline.hpp"

int main() {
    constexpr unsigned pipelineSize = 12;
    std::stringstream generatedCode =
        generateCordicPipelineCode<2, 13, 15>(pipelineSize);
    std::cout << generatedCode.str();

    return 0;
}
