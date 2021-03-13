-- ############################################################################
-- DISCLAIMER: The value of c_CORDIC_GAIN needs to be updated manually when
-- changing data bit-widths or cordic pipeline size
-- ############################################################################


library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.ALL;

entity cordic_cosine is
    generic(
        angular_data_width : integer := 16;
        linear_data_width  : integer := 16
    );
    port(
        i_clk   : in std_logic;
        i_reset : in std_logic;
        i_valid : in std_logic;
        i_phase : in std_logic_vector((angular_data_width-1) downto 0);
        o_valid : out std_logic;
        o_cos   : out std_logic_vector((linear_data_width-1) downto 0);
        o_sin   : out std_logic_vector((linear_data_width-1) downto 0)
    );
end cordic_cosine;

architecture behavioral of cordic_cosine is

component cordic_rotation is
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
end component cordic_rotation;

-- Constants
constant c_ZERO        : unsigned((linear_data_width-1) downto 0) :=
    (others => '0');
constant c_CORDIC_GAIN : unsigned((linear_data_width-1) downto 0) :=
    to_unsigned(16#136E#, 15);

begin

    rotation: cordic_rotation
    generic map (
        angular_data_width => angular_data_width,
        linear_data_width  => linear_data_width
    ) port map (
        i_clk        => i_clk,
        i_reset      => i_reset,
        i_valid      => i_valid,
        i_phase      => i_phase,
        i_position_x => std_logic_vector(c_CORDIC_GAIN),
        i_position_y => std_logic_vector(c_ZERO),
        o_valid      => o_valid,
        o_position_x => o_cos,
        o_position_y => o_sin
    );

end behavioral;
