-- ############################################################################
-- DISCLAIMER: This file was generated automatically using the application
-- generate-cordic-pipeline-app of the following project:
-- https://github.com/baptistepetit/cordic/tree/main/fixed_point
-- ############################################################################


library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.ALL;

entity cordic_pipeline is
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
end cordic_pipeline;

architecture behavioral of cordic_pipeline is

-- Component Declarations
component cordic_stage is
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
end component cordic_stage;

-- Constants
constant c_ANGULAR_DATA_WIDTH : integer := 15;
constant c_LINEAR_DATA_WIDTH : integer := 15;
constant c_STAGE_INDEX_0 : integer := 0;
constant c_STAGE_INDEX_1 : integer := 1;
constant c_STAGE_INDEX_2 : integer := 2;
constant c_STAGE_INDEX_3 : integer := 3;
constant c_STAGE_INDEX_4 : integer := 4;
constant c_STAGE_INDEX_5 : integer := 5;
constant c_STAGE_INDEX_6 : integer := 6;
constant c_STAGE_INDEX_7 : integer := 7;
constant c_STAGE_INDEX_8 : integer := 8;
constant c_STAGE_INDEX_9 : integer := 9;
constant c_STAGE_INDEX_10 : integer := 10;
constant c_STAGE_INDEX_11 : integer := 11;
constant c_STAGE_PHASE_0 : integer := 16#1000#;
constant c_STAGE_PHASE_1 : integer := 16#0972#;
constant c_STAGE_PHASE_2 : integer := 16#04FD#;
constant c_STAGE_PHASE_3 : integer := 16#0288#;
constant c_STAGE_PHASE_4 : integer := 16#0145#;
constant c_STAGE_PHASE_5 : integer := 16#00A2#;
constant c_STAGE_PHASE_6 : integer := 16#0051#;
constant c_STAGE_PHASE_7 : integer := 16#0028#;
constant c_STAGE_PHASE_8 : integer := 16#0014#;
constant c_STAGE_PHASE_9 : integer := 16#000A#;
constant c_STAGE_PHASE_10 : integer := 16#0005#;
constant c_STAGE_PHASE_11 : integer := 16#0002#;

-- Signals
signal phase_0 : std_logic_vector(c_ANGULAR_DATA_WIDTH-1 downto 0);
signal position_x_0 : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal position_y_0 : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal phase_1 : std_logic_vector(c_ANGULAR_DATA_WIDTH-1 downto 0);
signal position_x_1 : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal position_y_1 : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal phase_2 : std_logic_vector(c_ANGULAR_DATA_WIDTH-1 downto 0);
signal position_x_2 : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal position_y_2 : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal phase_3 : std_logic_vector(c_ANGULAR_DATA_WIDTH-1 downto 0);
signal position_x_3 : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal position_y_3 : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal phase_4 : std_logic_vector(c_ANGULAR_DATA_WIDTH-1 downto 0);
signal position_x_4 : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal position_y_4 : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal phase_5 : std_logic_vector(c_ANGULAR_DATA_WIDTH-1 downto 0);
signal position_x_5 : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal position_y_5 : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal phase_6 : std_logic_vector(c_ANGULAR_DATA_WIDTH-1 downto 0);
signal position_x_6 : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal position_y_6 : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal phase_7 : std_logic_vector(c_ANGULAR_DATA_WIDTH-1 downto 0);
signal position_x_7 : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal position_y_7 : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal phase_8 : std_logic_vector(c_ANGULAR_DATA_WIDTH-1 downto 0);
signal position_x_8 : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal position_y_8 : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal phase_9 : std_logic_vector(c_ANGULAR_DATA_WIDTH-1 downto 0);
signal position_x_9 : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal position_y_9 : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal phase_10 : std_logic_vector(c_ANGULAR_DATA_WIDTH-1 downto 0);
signal position_x_10 : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal position_y_10 : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal phase_11 : std_logic_vector(c_ANGULAR_DATA_WIDTH-1 downto 0);
signal position_x_11 : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal position_y_11 : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal phase_12 : std_logic_vector(c_ANGULAR_DATA_WIDTH-1 downto 0);
signal position_x_12 : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal position_y_12 : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);

begin

    phase_0 <= i_phase;
    position_x_0 <= i_position_x;
    position_y_0 <= i_position_y;
    o_phase <= phase_12;
    o_position_x <=position_x_12;
    o_position_y <=position_y_12;

    cordic_stage_0: cordic_stage
    generic map (
        angular_data_width => c_ANGULAR_DATA_WIDTH,
        linear_data_width  => c_LINEAR_DATA_WIDTH,
        stage_index        => c_STAGE_INDEX_0,
        stage_phase        => c_STAGE_PHASE_0
    ) port map (
        i_clk        => i_clk,
        i_reset      => i_reset,
        i_phase      => phase_0,
        i_position_x => position_x_0,
        i_position_y => position_y_0,
        o_phase      => phase_1,
        o_position_x => position_x_1,
        o_position_y => position_y_1
    );

    cordic_stage_1: cordic_stage
    generic map (
        angular_data_width => c_ANGULAR_DATA_WIDTH,
        linear_data_width  => c_LINEAR_DATA_WIDTH,
        stage_index        => c_STAGE_INDEX_1,
        stage_phase        => c_STAGE_PHASE_1
    ) port map (
        i_clk        => i_clk,
        i_reset      => i_reset,
        i_phase      => phase_1,
        i_position_x => position_x_1,
        i_position_y => position_y_1,
        o_phase      => phase_2,
        o_position_x => position_x_2,
        o_position_y => position_y_2
    );

    cordic_stage_2: cordic_stage
    generic map (
        angular_data_width => c_ANGULAR_DATA_WIDTH,
        linear_data_width  => c_LINEAR_DATA_WIDTH,
        stage_index        => c_STAGE_INDEX_2,
        stage_phase        => c_STAGE_PHASE_2
    ) port map (
        i_clk        => i_clk,
        i_reset      => i_reset,
        i_phase      => phase_2,
        i_position_x => position_x_2,
        i_position_y => position_y_2,
        o_phase      => phase_3,
        o_position_x => position_x_3,
        o_position_y => position_y_3
    );

    cordic_stage_3: cordic_stage
    generic map (
        angular_data_width => c_ANGULAR_DATA_WIDTH,
        linear_data_width  => c_LINEAR_DATA_WIDTH,
        stage_index        => c_STAGE_INDEX_3,
        stage_phase        => c_STAGE_PHASE_3
    ) port map (
        i_clk        => i_clk,
        i_reset      => i_reset,
        i_phase      => phase_3,
        i_position_x => position_x_3,
        i_position_y => position_y_3,
        o_phase      => phase_4,
        o_position_x => position_x_4,
        o_position_y => position_y_4
    );

    cordic_stage_4: cordic_stage
    generic map (
        angular_data_width => c_ANGULAR_DATA_WIDTH,
        linear_data_width  => c_LINEAR_DATA_WIDTH,
        stage_index        => c_STAGE_INDEX_4,
        stage_phase        => c_STAGE_PHASE_4
    ) port map (
        i_clk        => i_clk,
        i_reset      => i_reset,
        i_phase      => phase_4,
        i_position_x => position_x_4,
        i_position_y => position_y_4,
        o_phase      => phase_5,
        o_position_x => position_x_5,
        o_position_y => position_y_5
    );

    cordic_stage_5: cordic_stage
    generic map (
        angular_data_width => c_ANGULAR_DATA_WIDTH,
        linear_data_width  => c_LINEAR_DATA_WIDTH,
        stage_index        => c_STAGE_INDEX_5,
        stage_phase        => c_STAGE_PHASE_5
    ) port map (
        i_clk        => i_clk,
        i_reset      => i_reset,
        i_phase      => phase_5,
        i_position_x => position_x_5,
        i_position_y => position_y_5,
        o_phase      => phase_6,
        o_position_x => position_x_6,
        o_position_y => position_y_6
    );

    cordic_stage_6: cordic_stage
    generic map (
        angular_data_width => c_ANGULAR_DATA_WIDTH,
        linear_data_width  => c_LINEAR_DATA_WIDTH,
        stage_index        => c_STAGE_INDEX_6,
        stage_phase        => c_STAGE_PHASE_6
    ) port map (
        i_clk        => i_clk,
        i_reset      => i_reset,
        i_phase      => phase_6,
        i_position_x => position_x_6,
        i_position_y => position_y_6,
        o_phase      => phase_7,
        o_position_x => position_x_7,
        o_position_y => position_y_7
    );

    cordic_stage_7: cordic_stage
    generic map (
        angular_data_width => c_ANGULAR_DATA_WIDTH,
        linear_data_width  => c_LINEAR_DATA_WIDTH,
        stage_index        => c_STAGE_INDEX_7,
        stage_phase        => c_STAGE_PHASE_7
    ) port map (
        i_clk        => i_clk,
        i_reset      => i_reset,
        i_phase      => phase_7,
        i_position_x => position_x_7,
        i_position_y => position_y_7,
        o_phase      => phase_8,
        o_position_x => position_x_8,
        o_position_y => position_y_8
    );

    cordic_stage_8: cordic_stage
    generic map (
        angular_data_width => c_ANGULAR_DATA_WIDTH,
        linear_data_width  => c_LINEAR_DATA_WIDTH,
        stage_index        => c_STAGE_INDEX_8,
        stage_phase        => c_STAGE_PHASE_8
    ) port map (
        i_clk        => i_clk,
        i_reset      => i_reset,
        i_phase      => phase_8,
        i_position_x => position_x_8,
        i_position_y => position_y_8,
        o_phase      => phase_9,
        o_position_x => position_x_9,
        o_position_y => position_y_9
    );

    cordic_stage_9: cordic_stage
    generic map (
        angular_data_width => c_ANGULAR_DATA_WIDTH,
        linear_data_width  => c_LINEAR_DATA_WIDTH,
        stage_index        => c_STAGE_INDEX_9,
        stage_phase        => c_STAGE_PHASE_9
    ) port map (
        i_clk        => i_clk,
        i_reset      => i_reset,
        i_phase      => phase_9,
        i_position_x => position_x_9,
        i_position_y => position_y_9,
        o_phase      => phase_10,
        o_position_x => position_x_10,
        o_position_y => position_y_10
    );

    cordic_stage_10: cordic_stage
    generic map (
        angular_data_width => c_ANGULAR_DATA_WIDTH,
        linear_data_width  => c_LINEAR_DATA_WIDTH,
        stage_index        => c_STAGE_INDEX_10,
        stage_phase        => c_STAGE_PHASE_10
    ) port map (
        i_clk        => i_clk,
        i_reset      => i_reset,
        i_phase      => phase_10,
        i_position_x => position_x_10,
        i_position_y => position_y_10,
        o_phase      => phase_11,
        o_position_x => position_x_11,
        o_position_y => position_y_11
    );

    cordic_stage_11: cordic_stage
    generic map (
        angular_data_width => c_ANGULAR_DATA_WIDTH,
        linear_data_width  => c_LINEAR_DATA_WIDTH,
        stage_index        => c_STAGE_INDEX_11,
        stage_phase        => c_STAGE_PHASE_11
    ) port map (
        i_clk        => i_clk,
        i_reset      => i_reset,
        i_phase      => phase_11,
        i_position_x => position_x_11,
        i_position_y => position_y_11,
        o_phase      => phase_12,
        o_position_x => position_x_12,
        o_position_y => position_y_12
    );

end behavioral;

