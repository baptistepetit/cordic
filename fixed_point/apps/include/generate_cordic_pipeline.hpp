#pragma once

#include "angular_fixed_point.hpp"
#include "cordic.hpp"
#include "fixed_point.hpp"
#include "types.hpp"

#include <memory>
#include <sstream>
#include <string>
#include <vector>

const std::string header =
R"(-- ############################################################################
-- DISCLAIMER: This file was generated automatically using the application
-- generate-cordic-pipeline-app of the following project:
-- https://github.com/baptistepetit/cordic/tree/main/fixed_point
-- ############################################################################)";

const std::string libraries =
R"(library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.ALL;)";

const std::string entity =
R"(entity cordic_pipeline is
    generic(
        angular_data_width : integer := 16;
        linear_data_width  : integer := 16
    );
    port(
        i_clk        : in std_logic;
        i_reset      : in std_logic;
        i_valid      : in std_logic;
        i_phase      : in std_logic_vector((angular_data_width-1) downto 0);
        i_position_x : in std_logic_vector((linear_data_width-1) downto 0);
        i_position_y : in std_logic_vector((linear_data_width-1) downto 0);
        o_valid      : out std_logic;
        o_phase      : out std_logic_vector((angular_data_width-1) downto 0);
        o_position_x : out std_logic_vector((linear_data_width-1) downto 0);
        o_position_y : out std_logic_vector((linear_data_width-1) downto 0)
    );
end cordic_pipeline;)";

const std::string component =
R"(component cordic_stage is
    generic(
        angular_data_width : integer := 16;
        linear_data_width  : integer := 16;
        stage_index        : integer := 0;
        stage_phase        : integer := 0
    );
    port(
        i_clk        : in std_logic;
        i_reset      : in std_logic;
        i_valid      : in std_logic;
        i_phase      : in std_logic_vector((angular_data_width-1) downto 0);
        i_position_x : in std_logic_vector((linear_data_width-1) downto 0);
        i_position_y : in std_logic_vector((linear_data_width-1) downto 0);
        o_valid      : out std_logic;
        o_phase      : out std_logic_vector((angular_data_width-1) downto 0);
        o_position_x : out std_logic_vector((linear_data_width-1) downto 0);
        o_position_y : out std_logic_vector((linear_data_width-1) downto 0)
    );
end component cordic_stage;)";

template<int B>
inline std::stringstream generateCordicPipelineCode(const unsigned pipelineSize)
{
    std::stringstream generatedCode;

    const std::vector<AngularFixedPoint<B>> angleLut =
        generateAngleLut<AngularFixedPoint<B>>(pipelineSize);

    generatedCode << header << std::endl << std::endl << std::endl;
    generatedCode << libraries << std::endl << std::endl;
    generatedCode << entity  << std::endl << std::endl;

    generatedCode << "architecture behavioral of cordic_pipeline is" << std::endl << std::endl;

    generatedCode << "-- Component Declarations" << std::endl;
    generatedCode << component << std::endl << std::endl;

    generatedCode << "-- Constants" << std::endl;
    generatedCode << "---- Following constant is used to stop synthesis in" << std::endl;
    generatedCode << "---- case angle data width generic does not match with" << std::endl;
    generatedCode << "---- value used to generate constants in this file:" << std::endl;
    generatedCode << "constant c_ANGULAR_DATA_WIDTH : integer := " << B << ";" << std::endl;
    for (unsigned i = 0; i < pipelineSize; i++) {
        generatedCode
            << "constant c_STAGE_INDEX_" << std::to_string(i)
            << " : integer := " << std::to_string(i)
            << ";"
            << std::endl;
    }
    for (unsigned i = 0; i < pipelineSize; i++) {
        generatedCode
            << "constant c_STAGE_PHASE_" << std::to_string(i)
            << " : integer := " << angleLut.at(i) << ";"
            << std::endl;
    }
    generatedCode << std::endl;

    generatedCode << "-- Signals" << std::endl;
    for (unsigned i = 0; i <= pipelineSize; i++) {
        generatedCode
            << "signal valid_" << std::to_string(i)
            << " : std_logic;"
            << std::endl;
        generatedCode
            << "signal phase_" << std::to_string(i)
            << " : std_logic_vector(angular_data_width-1 downto 0);"
            << std::endl;
        generatedCode
            << "signal position_x_" << std::to_string(i)
            << " : std_logic_vector(linear_data_width-1 downto 0);"
            << std::endl;
        generatedCode
            << "signal position_y_" << std::to_string(i)
            << " : std_logic_vector(linear_data_width-1 downto 0);"
            << std::endl;
    }
    generatedCode << std::endl;

    generatedCode << "begin" << std::endl << std::endl;
    generatedCode << "assert c_ANGULAR_DATA_WIDTH = angular_data_width" << std::endl;
    generatedCode << "    report \"generated constants data width mismatch with generic, regenerate the file with correct size.\"" << std::endl;
    generatedCode << "    severity failure;" << std::endl << std::endl;

    generatedCode << "    valid_0 <= i_valid" << ";" << std::endl;
    generatedCode << "    phase_0 <= i_phase" << ";" << std::endl;
    generatedCode << "    position_x_0 <= i_position_x" << ";" << std::endl;
    generatedCode << "    position_y_0 <= i_position_y" << ";" << std::endl;
    generatedCode << "    o_valid <= " << "valid_" << std::to_string(pipelineSize) << ";" << std::endl;
    generatedCode << "    o_phase <= " << "phase_" << std::to_string(pipelineSize) << ";" << std::endl;
    generatedCode << "    o_position_x <=" << "position_x_"<< std::to_string(pipelineSize) << ";" << std::endl;
    generatedCode << "    o_position_y <=" << "position_y_"<< std::to_string(pipelineSize) << ";" << std::endl;
    generatedCode << std::endl;
    for (unsigned i = 0; i < pipelineSize; i++) {
        generatedCode << "    cordic_stage_" << std::to_string(i) << ": cordic_stage" << std::endl;
        generatedCode << "    generic map (" << std::endl;
        generatedCode << "        angular_data_width => angular_data_width," << std::endl;
        generatedCode << "        linear_data_width  => linear_data_width," << std::endl;
        generatedCode << "        stage_index        => c_STAGE_INDEX_" << std::to_string(i) << "," << std::endl;
        generatedCode << "        stage_phase        => c_STAGE_PHASE_" << std::to_string(i) << std::endl;
        generatedCode << "    ) port map (" << std::endl;
        generatedCode << "        i_clk        => i_clk," << std::endl;
        generatedCode << "        i_reset      => i_reset," << std::endl;
        generatedCode << "        i_valid      => valid_" << std::to_string(i) << "," << std::endl;
        generatedCode << "        i_phase      => phase_" << std::to_string(i) << "," << std::endl;
        generatedCode << "        i_position_x => position_x_" << std::to_string(i) << "," << std::endl;
        generatedCode << "        i_position_y => position_y_" << std::to_string(i) << "," << std::endl;
        generatedCode << "        o_valid      => valid_" << std::to_string(i + 1) << "," << std::endl;
        generatedCode << "        o_phase      => phase_" << std::to_string(i + 1) << "," << std::endl;
        generatedCode << "        o_position_x => position_x_" << std::to_string(i + 1) << "," << std::endl;
        generatedCode << "        o_position_y => position_y_" << std::to_string(i + 1) << std::endl;
        generatedCode << "    );" << std::endl;
        generatedCode << std::endl;
    }
    generatedCode << "end behavioral;" << std::endl << std::endl;

    return generatedCode;
}
