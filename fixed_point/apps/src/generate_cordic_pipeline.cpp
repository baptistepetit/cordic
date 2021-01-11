#include <iostream>
#include <sstream>
#include <string>

#include "../include/generate_cordic_pipeline.hpp"
#include "../include/write_to_file.hpp"

int main(int argc, char **argv) {
    constexpr unsigned pipelineSize = 12;
    std::stringstream generatedCode =
        generateCordicPipelineCode<2, 13, 15>(pipelineSize);

    std::string filePath = "";
    if (argc > 1) {
        std::string argv1(argv[1]);
        if ((argv1 == "-h") || (argv1 == "--help")) {
            std::cerr << "Usage " << argv[0] << " [-p PATH_TO_FILE]"
                << std::endl;
            return 0;
        } else if ((argv1 == "-p") && (argc == 3)) {
            filePath = std::string(argv[2]);
        }
    }

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
