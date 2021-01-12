library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.ALL;

library vunit_lib;
context vunit_lib.vunit_context;

library cordic_lib;

entity add_sub_tb is
    generic(
        runner_cfg : string
    );
end add_sub_tb;

architecture sim of add_sub_tb is

-- Constants
constant c_CLK_PERIOD : time := 10 us;
constant c_RESET_TIME : time := 105 us;
constant c_DATA_WIDTH : integer := 3;

-- Inputs
signal clk             : std_logic := '0';
signal reset           : std_logic := '0';
signal i_valid         : std_logic := '0';
signal is_substraction : std_logic := 'U';
signal lhs             : std_logic_vector(c_DATA_WIDTH-1 downto 0) := (others => 'U');
signal rhs             : std_logic_vector(c_DATA_WIDTH-1 downto 0) := (others => 'U');

-- Output
signal result          : std_logic_vector(c_DATA_WIDTH-1 downto 0);
signal o_valid         : std_logic;
signal expected_result : std_logic_vector(c_DATA_WIDTH-1 downto 0);

begin

    dut : entity cordic_lib.add_sub
    generic map (
        data_width => c_DATA_WIDTH
    ) port map (
        i_clk => clk,
        i_reset => reset,
        i_valid => i_valid,
        i_lhs => lhs,
        i_rhs => rhs,
        i_is_substraction => is_substraction,
        o_result => result,
        o_valid => o_valid
    );

    p_clk : process
    begin
        clk <= '0';
        wait for c_CLK_PERIOD / 2;
        clk <= '1';
        wait for c_CLK_PERIOD / 2;
    end process p_clk;

    p_main : process
    begin
        test_runner_setup(runner, runner_cfg);

        while test_suite loop
            if run("synchronous_reset_works") then
                reset <= '1';
                expected_result <= (others => '0');
                wait for c_CLK_PERIOD;
                check_not_unknown(o_valid);
                check_not_unknown(result);
                check_equal(o_valid, '0');
                check_equal(result, expected_result);
                wait for c_RESET_TIME;
                reset <= '0';
            elsif run("addition_works") then
                i_valid <= '0';
                wait for c_CLK_PERIOD;
                i_valid <= '1';
                lhs <= std_logic_vector(to_signed(1, c_DATA_WIDTH));
                rhs <= std_logic_vector(to_signed(2, c_DATA_WIDTH));
                is_substraction <= '0';
                expected_result <= std_logic_vector(to_signed(3, c_DATA_WIDTH));
                wait until o_valid = '1';
                check_equal(result, expected_result);
            elsif run("addition_result_is_truncated") then
                i_valid <= '0';
                wait for c_CLK_PERIOD;
                i_valid <= '1';
                lhs <= std_logic_vector(to_signed(3, c_DATA_WIDTH));
                rhs <= std_logic_vector(to_signed(1, c_DATA_WIDTH));
                is_substraction <= '0';
                expected_result <= std_logic_vector(to_signed(-4, c_DATA_WIDTH));
                wait until o_valid = '1';
                check_equal(result, expected_result);
            elsif run("substraction_works") then
                i_valid <= '0';
                wait for c_CLK_PERIOD;
                i_valid <= '1';
                lhs <= std_logic_vector(to_signed(1, c_DATA_WIDTH));
                rhs <= std_logic_vector(to_signed(2, c_DATA_WIDTH));
                is_substraction <= '1';
                expected_result <= std_logic_vector(to_signed(-1, c_DATA_WIDTH));
                wait until o_valid = '1';
                check_equal(result, expected_result);
            elsif run("substraction_result_is_truncated") then
                i_valid <= '0';
                wait for c_CLK_PERIOD;
                i_valid <= '1';
                lhs <= std_logic_vector(to_signed(-4, c_DATA_WIDTH));
                rhs <= std_logic_vector(to_signed(1, c_DATA_WIDTH));
                is_substraction <= '1';
                expected_result <= std_logic_vector(to_signed(3, c_DATA_WIDTH));
                wait until o_valid = '1';
                check_equal(result, expected_result);
            end if;
        end loop;

        test_runner_cleanup(runner);
    end process p_main;

    test_runner_watchdog(runner, 10 ms);

end sim;
