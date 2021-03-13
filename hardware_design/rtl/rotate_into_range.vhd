library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.ALL;

entity rotate_into_range is
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
end rotate_into_range;

architecture behavioral of rotate_into_range is

-- Constants
constant c_PADDING  : std_logic_vector((angular_data_width-4) downto 0) :=
    (others => '0');
constant c_PI_2     : signed((angular_data_width-1) downto 0) :=
    signed("010" & c_PADDING);
constant c_PI : signed((angular_data_width-1) downto 0) :=
    signed("100" & c_PADDING);

-- Signals
signal angle_octant : unsigned(2 downto 0);
signal i_signed_phase : signed((angular_data_width-1) downto 0);
signal i_signed_position_x : signed((linear_data_width-1) downto 0);
signal i_signed_position_y : signed((linear_data_width-1) downto 0);

begin

    angle_octant <=
        unsigned(i_phase((angular_data_width-1) downto (angular_data_width-3)));

    i_signed_phase <= signed(i_phase);
    i_signed_position_x <= signed(i_position_x);
    i_signed_position_y <= signed(i_position_y);

    p_rotate_into_range: process(i_clk)
    begin
        if (i_clk'event and i_clk = '1') then
            if (i_reset = '1') then
                o_phase <= (others => '0');
                o_position_x <= (others => '0');
                o_position_y <= (others => '0');
                o_valid <= '0';
            else
                o_valid <= i_valid;
                case angle_octant is
                    when "000" | "111"  => -- [-PI/4, PI/4[
                        o_phase <= i_phase;
                        o_position_x <= i_position_x;
                        o_position_y <= i_position_y;
                    when "001" | "010" => -- [PI/4, 3PI/4[
                        o_phase <= std_logic_vector(i_signed_phase - c_PI_2);
                        o_position_x <= std_logic_vector(-i_signed_position_y);
                        o_position_y <= std_logic_vector(i_signed_position_x);
                    when "011" | "100" => -- [3PI/4, -3PI/4[
                        o_phase <= std_logic_vector(i_signed_phase + c_PI);
                        o_position_x <= std_logic_vector(-i_signed_position_x);
                        o_position_y <= std_logic_vector(-i_signed_position_y);
                    when "101" | "110" => -- [-3PI/4, -PI/4[
                        o_phase <= std_logic_vector(i_signed_phase + c_PI_2);
                        o_position_x <= std_logic_vector(-i_signed_position_y);
                        o_position_y <= std_logic_vector(-i_signed_position_x);
                    when others => -- Should never happen
                        o_phase <= (others => '0');
                        o_position_x <= (others => '0');
                        o_position_y <= (others => '0');
                end case;
            end if;
        end if;
    end process p_rotate_into_range;

end behavioral;
