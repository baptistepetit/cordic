#include <iostream>
#include <sstream>
#include <string>

#include "../include/generate_cordic_pipeline.hpp"
#include "../include/write_to_file.hpp"

int main() {
    constexpr unsigned pipelineSize = 12;
    std::stringstream generatedCode =
        generateCordicPipelineCode<2, 13, 15>(pipelineSize);

    const std::string filePath = "";
    if (writeToFile(filePath, generatedCode)) {
        std::cout << "Content have been written to: "
            << "\"" << filePath << "\""
            << std::endl;
    } else {
        std::cerr << "Content have not been written to a file, here it is: "
            << std::endl;
        std::cout << generatedCode.rdbuf();
    }

    return 0;
}
