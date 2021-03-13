library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.ALL;

entity cordic_rotation is
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
end cordic_rotation;

architecture behavioral of cordic_rotation is

-- Component Declarations
component cordic_pipeline is
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
end component cordic_pipeline;

component rotate_into_range is
    generic(
        angular_data_width  : integer := 16;
        linear_data_width : integer := 16
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
end component rotate_into_range;

-- Signals
signal valid              : std_logic;
signal rotated_phase      : std_logic_vector((angular_data_width-1) downto 0);
signal rotated_position_x : std_logic_vector((linear_data_width-1) downto 0);
signal rotated_position_y : std_logic_vector((linear_data_width-1) downto 0);

begin

    pre_rotation: rotate_into_range
    generic map (
        angular_data_width => angular_data_width,
        linear_data_width  => linear_data_width
    ) port map (
        i_clk        => i_clk,
        i_reset      => i_reset,
        i_valid      => i_valid,
        i_phase      => i_phase,
        i_position_x => i_position_x,
        i_position_y => i_position_y,
        o_valid      => valid,
        o_phase      => rotated_phase,
        o_position_x => rotated_position_x,
        o_position_y => rotated_position_y
    );

    compute_pipeline: cordic_pipeline
    generic map (
        angular_data_width => angular_data_width,
        linear_data_width  => linear_data_width
    ) port map (
        i_clk        => i_clk,
        i_reset      => i_reset,
        i_valid      => valid,
        i_phase      => rotated_phase,
        i_position_x => rotated_position_x,
        i_position_y => rotated_position_y,
        o_valid      => o_valid,
        o_phase      => o_phase,
        o_position_x => o_position_x,
        o_position_y => o_position_y
    );

end behavioral;
