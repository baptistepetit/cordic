library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.ALL;

entity add_sub is
    generic(
        data_width : integer := 16
    );
    port(
        i_clk            : in std_logic;
        i_reset          : in std_logic;
        i_lhs            : in std_logic_vector((data_width-1) downto 0);
        i_rhs            : in std_logic_vector((data_width-1) downto 0);
        i_is_substraction : in std_logic;
        o_result : out std_logic_vector((data_width-1) downto 0)
    );
end add_sub;

architecture behavioral of add_sub is
begin
    p_add_sub : process(i_clk)
    begin
        if (i_clk'event and i_clk = '1') then
            if (i_reset = '1') then
                o_result <= (others => '0');
            else
                if (i_is_substraction = '1') then
                    o_result <= std_logic_vector(signed(i_lhs) - signed(i_rhs));
                else
                    o_result <= std_logic_vector(signed(i_lhs) + signed(i_rhs));
                end if;
            end if;
        end if;
    end process p_add_sub;
end behavioral;
