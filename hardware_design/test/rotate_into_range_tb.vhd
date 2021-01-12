library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.ALL;

library vunit_lib;
context vunit_lib.vunit_context;

library cordic_lib;

entity rotate_into_range_tb is
    generic(
        runner_cfg : string
    );
end rotate_into_range_tb;


architecture sim of rotate_into_range_tb is

-- Constants
constant c_CLK_PERIOD         : time := 10 us;
constant c_RESET_TIME         : time := 104 us;
constant c_ANGULAR_DATA_WIDTH : integer := 15;
constant c_LINEAR_DATA_WIDTH  : integer := 15;

-- Inputs
signal clk          : std_logic := '0';
signal reset        : std_logic := '0';
signal i_valid      : std_logic := '0';
signal i_position_x : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0) := (others => 'U');
signal i_position_y : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0) := (others => 'U');
signal i_phase      : std_logic_vector(c_ANGULAR_DATA_WIDTH-1 downto 0) := (others => 'U');

-- Output
signal o_valid             : std_logic;
signal result_phase        : std_logic_vector(c_ANGULAR_DATA_WIDTH-1 downto 0);
signal result_position_x   : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal result_position_y   : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal expected_phase      : std_logic_vector(c_ANGULAR_DATA_WIDTH-1 downto 0);
signal expected_position_x : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal expected_position_y : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);

begin

    dut : entity cordic_lib.rotate_into_range
    generic map (
        angular_data_width => c_ANGULAR_DATA_WIDTH,
        linear_data_width  => c_LINEAR_DATA_WIDTH
    ) port map (
        i_clk        => clk,
        i_reset      => reset,
        i_valid      => i_valid,
        i_phase      => i_phase,
        i_position_x => i_position_x,
        i_position_y => i_position_y,
        o_valid      => o_valid,
        o_phase      => result_phase,
        o_position_x => result_position_x,
        o_position_y => result_position_y
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
            -- Test Setup
            i_position_x <= std_logic_vector(to_unsigned(16#136E#, 15));
            i_position_y <= std_logic_vector(to_unsigned(16#1234#, 15));

            if run("synchronous_reset_works") then
                reset <= '1';
                expected_phase      <= (others => '0');
                expected_position_x <= (others => '0');
                expected_position_y <= (others => '0');
                wait for c_CLK_PERIOD;
                check_not_unknown(o_valid);
                check_not_unknown(result_phase);
                check_not_unknown(result_position_x);
                check_not_unknown(result_position_y);
                check_equal(o_valid,           '0');
                check_equal(result_phase,      expected_phase);
                check_equal(result_position_x, expected_position_x);
                check_equal(result_position_y, expected_position_y);
                wait for c_RESET_TIME;
                reset <= '0';
            elsif run("garbage_data") then
                i_valid <= '0';
                wait for c_CLK_PERIOD;
                i_valid <= '1';
                i_phase      <= (others => 'X');
                expected_phase      <= (others => '0');
                expected_position_x <= (others => '0');
                expected_position_y <= (others => '0');
                wait until o_valid = '1';
                check_equal(result_phase,      expected_phase);
                check_equal(result_position_x, expected_position_x);
                check_equal(result_position_y, expected_position_y);
            elsif run("octant_0") then
                i_valid <= '0';
                wait for c_CLK_PERIOD;
                i_valid <= '1';
                i_phase      <= std_logic_vector(to_unsigned(16#0111#, 15));
                expected_phase      <= std_logic_vector(to_unsigned(16#0111#, 15));
                expected_position_x <= std_logic_vector(to_unsigned(16#136E#, 15));
                expected_position_y <= std_logic_vector(to_unsigned(16#1234#, 15));
                wait until o_valid = '1';
                check_equal(result_phase,      expected_phase);
                check_equal(result_position_x, expected_position_x);
                check_equal(result_position_y, expected_position_y);
            elsif run("octant_1") then
                i_valid <= '0';
                wait for c_CLK_PERIOD;
                i_valid <= '1';
                i_phase      <= std_logic_vector(to_unsigned(16#1111#, 15));
                expected_phase      <= std_logic_vector(to_unsigned(16#7111#, 15));
                expected_position_x <= std_logic_vector(to_unsigned(16#6DCC#, 15));
                expected_position_y <= std_logic_vector(to_unsigned(16#136E#, 15));
                wait until o_valid = '1';
                check_equal(result_phase,      expected_phase);
                check_equal(result_position_x, expected_position_x);
                check_equal(result_position_y, expected_position_y);
            elsif run("octant_2") then
                i_valid <= '0';
                wait for c_CLK_PERIOD;
                i_valid <= '1';
                i_phase      <= std_logic_vector(to_unsigned(16#2111#, 15));
                expected_phase      <= std_logic_vector(to_unsigned(16#0111#, 15));
                expected_position_x <= std_logic_vector(to_unsigned(16#6DCC#, 15));
                expected_position_y <= std_logic_vector(to_unsigned(16#136E#, 15));
                wait until o_valid = '1';
                check_equal(result_phase,      expected_phase);
                check_equal(result_position_x, expected_position_x);
                check_equal(result_position_y, expected_position_y);
            elsif run("octant_3") then
                i_valid <= '0';
                wait for c_CLK_PERIOD;
                i_valid <= '1';
                i_phase      <= std_logic_vector(to_unsigned(16#3111#, 15));
                expected_phase      <= std_logic_vector(to_unsigned(16#7111#, 15));
                expected_position_x <= std_logic_vector(to_unsigned(16#6C92#, 15));
                expected_position_y <= std_logic_vector(to_unsigned(16#6DCC#, 15));
                wait until o_valid = '1';
                check_equal(result_phase,      expected_phase);
                check_equal(result_position_x, expected_position_x);
                check_equal(result_position_y, expected_position_y);
            elsif run("octant_4") then
                i_valid <= '0';
                wait for c_CLK_PERIOD;
                i_valid <= '1';
                i_phase      <= std_logic_vector(to_unsigned(16#4111#, 15));
                expected_phase      <= std_logic_vector(to_unsigned(16#0111#, 15));
                expected_position_x <= std_logic_vector(to_unsigned(16#6C92#, 15));
                expected_position_y <= std_logic_vector(to_unsigned(16#6DCC#, 15));
                wait until o_valid = '1';
                check_equal(result_phase,      expected_phase);
                check_equal(result_position_x, expected_position_x);
                check_equal(result_position_y, expected_position_y);
            elsif run("octant_5") then
                i_valid <= '0';
                wait for c_CLK_PERIOD;
                i_valid <= '1';
                i_phase      <= std_logic_vector(to_unsigned(16#5111#, 15));
                expected_phase      <= std_logic_vector(to_unsigned(16#7111#, 15));
                expected_position_x <= std_logic_vector(to_unsigned(16#6DCC#, 15));
                expected_position_y <= std_logic_vector(to_unsigned(16#6C92#, 15));
                wait until o_valid = '1';
                check_equal(result_phase,      expected_phase);
                check_equal(result_position_x, expected_position_x);
                check_equal(result_position_y, expected_position_y);
            elsif run("octant_6") then
                i_valid <= '0';
                wait for c_CLK_PERIOD;
                i_valid <= '1';
                i_phase      <= std_logic_vector(to_unsigned(16#6111#, 15));
                expected_phase      <= std_logic_vector(to_unsigned(16#0111#, 15));
                expected_position_x <= std_logic_vector(to_unsigned(16#6DCC#, 15));
                expected_position_y <= std_logic_vector(to_unsigned(16#6C92#, 15));
                wait until o_valid = '1';
                check_equal(result_phase,      expected_phase);
                check_equal(result_position_x, expected_position_x);
                check_equal(result_position_y, expected_position_y);
            elsif run("octant_7") then
                i_valid <= '0';
                wait for c_CLK_PERIOD;
                i_valid <= '1';
                i_phase      <= std_logic_vector(to_unsigned(16#7111#, 15));
                expected_phase      <= std_logic_vector(to_unsigned(16#7111#, 15));
                expected_position_x <= std_logic_vector(to_unsigned(16#136E#, 15));
                expected_position_y <= std_logic_vector(to_unsigned(16#1234#, 15));
                wait until o_valid = '1';
                check_equal(result_phase,      expected_phase);
                check_equal(result_position_x, expected_position_x);
                check_equal(result_position_y, expected_position_y);
            end if;
        end loop;

        test_runner_cleanup(runner);
    end process p_main;

    test_runner_watchdog(runner, 10 ms);

end sim;
