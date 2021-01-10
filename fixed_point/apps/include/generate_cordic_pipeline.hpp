#pragma once

#include <string>

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
        i_phase      : in std_logic_vector((angular_data_width-1) downto 0);
        i_position_x : in std_logic_vector((linear_data_width-1) downto 0);
        i_position_y : in std_logic_vector((linear_data_width-1) downto 0);
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
        i_phase      : in std_logic_vector((angular_data_width-1) downto 0);
        i_position_x : in std_logic_vector((linear_data_width-1) downto 0);
        i_position_y : in std_logic_vector((linear_data_width-1) downto 0);
        o_phase      : out std_logic_vector((angular_data_width-1) downto 0);
        o_position_x : out std_logic_vector((linear_data_width-1) downto 0);
        o_position_y : out std_logic_vector((linear_data_width-1) downto 0)
    );
end component cordic_stage;)";
