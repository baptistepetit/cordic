library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.ALL;

library vunit_lib;
context vunit_lib.vunit_context;

library cordic_lib;

entity cordic_cosine_tb is
    generic(
        runner_cfg : string
    );
end cordic_cosine_tb;


architecture sim of cordic_cosine_tb is

-- Constants
constant c_CLK_PERIOD           : time := 10 us;
constant c_RESET_TIME           : time := 104 us;
constant c_ANGULAR_DATA_WIDTH   : integer := 15;
constant c_LINEAR_DATA_WIDTH    : integer := 15;

-- Inputs
signal clk     : std_logic := '0';
signal reset   : std_logic := '0';
signal i_valid : std_logic := '0';
signal i_phase : std_logic_vector(c_ANGULAR_DATA_WIDTH-1 downto 0) := (others => 'U');

-- Output
signal o_valid      : std_logic;
signal result_cos   : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal result_sin   : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal expected_cos : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal expected_sin : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);

begin

    dut : entity cordic_lib.cordic_cosine
    generic map (
        angular_data_width => c_ANGULAR_DATA_WIDTH,
        linear_data_width  => c_LINEAR_DATA_WIDTH
    ) port map (
        i_clk   => clk,
        i_reset => reset,
        i_valid => i_valid,
        i_phase => i_phase,
        o_valid => o_valid,
        o_cos   => result_cos,
        o_sin   => result_sin
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
                expected_cos <= (others => '0');
                expected_sin <= (others => '0');
                wait for c_CLK_PERIOD;
                check_not_unknown(o_valid);
                check_not_unknown(result_cos);
                check_not_unknown(result_sin);
                check_equal(o_valid,    '0');
                check_equal(result_cos, expected_cos);
                check_equal(result_sin, expected_sin);
                wait for c_RESET_TIME;
                reset <= '0';
            elsif run("negative_angle_works") then
                i_valid <= '0';
                wait for c_CLK_PERIOD;
                i_valid <= '1';
                i_phase <= std_logic_vector(to_unsigned(16#77DA#, 15));
                expected_cos <= std_logic_vector(to_unsigned(16#1D7A#, 15));
                expected_sin <= std_logic_vector(to_unsigned(16#7389#, 15));
                wait until o_valid = '1';
                check_equal(result_cos, expected_cos);
                check_equal(result_sin, expected_sin);
            elsif run("positive_angle_works") then
                i_valid <= '0';
                wait for c_CLK_PERIOD;
                i_valid <= '1';
                i_phase <= std_logic_vector(to_unsigned(16#0826#, 15));
                expected_cos <= std_logic_vector(to_unsigned(16#1D79#, 15));
                expected_sin <= std_logic_vector(to_unsigned(16#0C76#, 15));
                wait until o_valid = '1';
                check_equal(result_cos, expected_cos);
                check_equal(result_sin, expected_sin);
            elsif run("angle_to_normalize_works") then
                i_valid <= '0';
                wait for c_CLK_PERIOD;
                i_valid <= '1';
                i_phase <= std_logic_vector(to_unsigned(16#5742#, 15));
                expected_cos <= std_logic_vector(to_unsigned(16#72AE#, 15));
                expected_sin <= std_logic_vector(to_unsigned(16#62E8#, 15));
                wait until o_valid = '1';
                check_equal(result_cos, expected_cos);
                check_equal(result_sin, expected_sin);
            end if;
        end loop;

        test_runner_cleanup(runner);
    end process p_main;

    test_runner_watchdog(runner, 10 ms);

end sim;
