library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.ALL;

entity cordic_stage is
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
end cordic_stage;


architecture behavioral of cordic_stage is

component add_sub is
    generic(
        data_width : integer := 16
    );
    port(
        i_clk            : in std_logic;
        i_reset          : in std_logic;
        i_valid          : in std_logic;
        i_lhs            : in std_logic_vector((data_width-1) downto 0);
        i_rhs            : in std_logic_vector((data_width-1) downto 0);
        i_is_substraction : in std_logic;
        o_result : out std_logic_vector((data_width-1) downto 0);
        o_valid : out std_logic
    );
end component add_sub;

constant c_STAGE_PHASE : std_logic_vector((angular_data_width-1) downto 0) :=
    std_logic_vector(to_signed(stage_phase, angular_data_width));

signal negative_rotation_needed : std_logic;
signal not_negative_rotation_needed : std_logic;
signal o_valid_1 : std_logic;
signal o_valid_2 : std_logic;
signal o_valid_3 : std_logic;
signal shifted_position_x : std_logic_vector((linear_data_width-1) downto 0);
signal shifted_position_y : std_logic_vector((linear_data_width-1) downto 0);

begin
    negative_rotation_needed <=
        '1' when signed(i_phase) >= to_signed(0, angular_data_width) else
        '0';
    not_negative_rotation_needed <= not(negative_rotation_needed);

    shifted_position_x <= std_logic_vector(
        shift_right(signed(i_position_x), stage_index)
    );
    shifted_position_y <= std_logic_vector(
        shift_right(signed(i_position_y), stage_index)
    );
    o_valid <= o_valid_1 and o_valid_2 and o_valid_3;

    add_sub_1 : add_sub
    generic map (
        data_width => linear_data_width
    ) port map (
        i_clk => i_clk,
        i_reset => i_reset,
        i_valid => i_valid,
        i_lhs => i_position_x,
        i_rhs => shifted_position_y,
        i_is_substraction => negative_rotation_needed,
        o_result => o_position_x,
        o_valid => o_valid_1
    );

    add_sub_2 : add_sub
    generic map (
        data_width => linear_data_width
    ) port map (
        i_clk => i_clk,
        i_reset => i_reset,
        i_valid => i_valid,
        i_lhs => i_position_y,
        i_rhs => shifted_position_x,
        i_is_substraction => not_negative_rotation_needed,
        o_result => o_position_y,
        o_valid => o_valid_2
    );

    add_sub_3 : add_sub
    generic map (
        data_width => angular_data_width
    ) port map (
        i_clk => i_clk,
        i_reset => i_reset,
        i_valid => i_valid,
        i_lhs => i_phase,
        i_rhs => c_STAGE_PHASE,
        i_is_substraction => negative_rotation_needed,
        o_result => o_phase,
        o_valid => o_valid_3
    );
end behavioral;
