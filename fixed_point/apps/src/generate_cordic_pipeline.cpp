#include "angular_fixed_point.hpp"
#include "cordic.hpp"
#include "fixed_point.hpp"
#include "types.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "generate_cordic_pipeline.hpp"

int main() {
    constexpr unsigned pipelineSize = 12;
    const std::vector<AngularFixedPoint<15>> angleLut =
        generateAngleLut<AngularFixedPoint<15>>(pipelineSize);

    std::cout << header << std::endl << std::endl << std::endl;
    std::cout << libraries << std::endl << std::endl;
    std::cout << entity  << std::endl << std::endl;

    std::cout << "architecture behavioral of cordic_pipeline is" << std::endl << std::endl;

    std::cout << "-- Component Declarations" << std::endl;
    std::cout << component << std::endl << std::endl;

    std::cout << "-- Constants" << std::endl;
    std::cout << "constant c_ANGULAR_DATA_WIDTH : integer := 15;" << std::endl;
    std::cout << "constant c_LINEAR_DATA_WIDTH : integer := 15;" << std::endl;
    for (unsigned i = 0; i < pipelineSize; i++) {
        std::cout
            << "constant c_STAGE_INDEX_" << std::to_string(i)
            << " : integer := " << std::to_string(i)
            << ";"
            << std::endl;
    }
    for (unsigned i = 0; i < pipelineSize; i++) {
        std::cout
            << "constant c_STAGE_PHASE_" << std::to_string(i)
            << " : integer := " << angleLut.at(i) << ";"
            << std::endl;
    }
    std::cout << std::endl;

    std::cout << "-- Signals" << std::endl;
    for (unsigned i = 0; i <= pipelineSize; i++) {
        std::cout
            << "signal phase_" << std::to_string(i)
            << " : std_logic_vector(c_ANGULAR_DATA_WIDTH-1 downto 0);"
            << std::endl;
        std::cout
            << "signal position_x_" << std::to_string(i)
            << " : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);"
            << std::endl;
        std::cout
            << "signal position_y_" << std::to_string(i)
            << " : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);"
            << std::endl;
    }
    std::cout << std::endl;

    std::cout << "begin" << std::endl << std::endl;
    std::cout << "    phase_0 <= i_phase" << ";" << std::endl;
    std::cout << "    position_x_0 <= i_position_x" << ";" << std::endl;
    std::cout << "    position_y_0 <= i_position_y" << ";" << std::endl;
    std::cout << "    o_phase <= " << "phase_" << std::to_string(pipelineSize) << ";" << std::endl;
    std::cout << "    o_position_x <=" << "position_x_"<< std::to_string(pipelineSize) << ";" << std::endl;
    std::cout << "    o_position_y <=" << "position_y_"<< std::to_string(pipelineSize) << ";" << std::endl;
    std::cout << std::endl;
    for (unsigned i = 0; i < pipelineSize; i++) {
        std::cout << "    cordic_stage_" << std::to_string(i) << ": cordic_stage" << std::endl;
        std::cout << "    generic map (" << std::endl;
        std::cout << "        angular_data_width => c_ANGULAR_DATA_WIDTH," << std::endl;
        std::cout << "        linear_data_width  => c_LINEAR_DATA_WIDTH," << std::endl;
        std::cout << "        stage_index        => c_STAGE_INDEX_" << std::to_string(i) << "," << std::endl;
        std::cout << "        stage_phase        => c_STAGE_PHASE_" << std::to_string(i) << std::endl;
        std::cout << "    ) port map (" << std::endl;
        std::cout << "        i_clk        => i_clk," << std::endl;
        std::cout << "        i_reset      => i_reset," << std::endl;
        std::cout << "        i_phase      => phase_" << std::to_string(i) << "," << std::endl;
        std::cout << "        i_position_x => position_x_" << std::to_string(i) << "," << std::endl;
        std::cout << "        i_position_y => position_y_" << std::to_string(i) << "," << std::endl;
        std::cout << "        o_phase      => phase_" << std::to_string(i + 1) << "," << std::endl;
        std::cout << "        o_position_x => position_x_" << std::to_string(i + 1) << "," << std::endl;
        std::cout << "        o_position_y => position_y_" << std::to_string(i + 1) << std::endl;
        std::cout << "    );" << std::endl;
        std::cout << std::endl;
    }
    std::cout << "end behavioral;" << std::endl << std::endl;

    return 0;
}
