library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.ALL;

library vunit_lib;
context vunit_lib.vunit_context;

library cordic_lib;

entity cordic_stage_tb is
    generic(
        runner_cfg : string
    );
end cordic_stage_tb;


architecture sim of cordic_stage_tb is

-- Constants
constant c_CLK_PERIOD         : time := 10 us;
constant c_RESET_TIME         : time := 104 us;
constant c_ANGULAR_DATA_WIDTH : integer := 15;
constant c_LINEAR_DATA_WIDTH  : integer := 15;
constant c_STAGE_INDEX_0      : integer := 0;
constant c_STAGE_PHASE_0      : integer := 16#1000#;
constant c_STAGE_INDEX_1      : integer := 1;
constant c_STAGE_PHASE_1      : integer := 16#0972#;

-- Inputs
signal clk          : std_logic := '0';
signal reset        : std_logic := '0';
signal i_valid      : std_logic := '0';
signal i_position_x : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0) := (others => 'U');
signal i_position_y : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0) := (others => 'U');
signal i_phase      : std_logic_vector(c_ANGULAR_DATA_WIDTH-1 downto 0) := (others => 'U');

-- Output
signal o_valid_0           : std_logic;
signal result_phase_0      : std_logic_vector(c_ANGULAR_DATA_WIDTH-1 downto 0);
signal result_position_x_0 : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal result_position_y_0 : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal o_valid_1           : std_logic;
signal result_phase_1      : std_logic_vector(c_ANGULAR_DATA_WIDTH-1 downto 0);
signal result_position_x_1 : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal result_position_y_1 : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal expected_phase      : std_logic_vector(c_ANGULAR_DATA_WIDTH-1 downto 0);
signal expected_position_x : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal expected_position_y : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);

begin

    dut_stage_0 : entity cordic_lib.cordic_stage
    generic map (
        angular_data_width => c_ANGULAR_DATA_WIDTH,
        linear_data_width  => c_LINEAR_DATA_WIDTH,
        stage_index        => c_STAGE_INDEX_0,
        stage_phase        => c_STAGE_PHASE_0
    ) port map (
        i_clk        => clk,
        i_reset      => reset,
        i_valid      => i_valid,
        i_phase      => i_phase,
        i_position_x => i_position_x,
        i_position_y => i_position_y,
        o_valid      => o_valid_0,
        o_phase      => result_phase_0,
        o_position_x => result_position_x_0,
        o_position_y => result_position_y_0
    );

    dut_stage_1 : entity cordic_lib.cordic_stage
    generic map (
        angular_data_width => c_ANGULAR_DATA_WIDTH,
        linear_data_width  => c_LINEAR_DATA_WIDTH,
        stage_index        => c_STAGE_INDEX_1,
        stage_phase        => c_STAGE_PHASE_1
    ) port map (
        i_clk        => clk,
        i_reset      => reset,
        i_valid      => i_valid,
        i_phase      => i_phase,
        i_position_x => i_position_x,
        i_position_y => i_position_y,
        o_valid      => o_valid_1,
        o_phase      => result_phase_1,
        o_position_x => result_position_x_1,
        o_position_y => result_position_y_1
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
                expected_phase      <= (others => '0');
                expected_position_x <= (others => '0');
                expected_position_y <= (others => '0');
                wait for c_CLK_PERIOD;
                check_not_unknown(o_valid_0);
                check_not_unknown(result_phase_0);
                check_not_unknown(result_position_x_0);
                check_not_unknown(result_position_y_0);
                check_equal(o_valid_0,          '0');
                check_equal(result_phase_0,      expected_phase);
                check_equal(result_position_x_0, expected_position_x);
                check_equal(result_position_y_0, expected_position_y);
                wait for c_RESET_TIME;
                reset <= '0';
            elsif run("negative_rotation_works_stage_0") then
                i_valid <= '0';
                wait for c_CLK_PERIOD;
                i_valid <= '1';
                i_phase      <= std_logic_vector(to_unsigned(16#0826#, 15));
                i_position_x <= std_logic_vector(to_unsigned(16#136E#, 15));
                i_position_y <= std_logic_vector(to_unsigned(16#0000#, 15));
                expected_phase      <= std_logic_vector(to_unsigned(16#7826#, 15));
                expected_position_x <= std_logic_vector(to_unsigned(16#136E#, 15));
                expected_position_y <= std_logic_vector(to_unsigned(16#136E#, 15));
                wait until o_valid_0 = '1';
                check_equal(result_phase_0,      expected_phase);
                check_equal(result_position_x_0, expected_position_x);
                check_equal(result_position_y_0, expected_position_y);
            elsif run("positive_rotation_works_stage_0") then
                i_valid <= '0';
                wait for c_CLK_PERIOD;
                i_valid <= '1';
                i_phase      <= std_logic_vector(to_unsigned(16#77DA#, 15));
                i_position_x <= std_logic_vector(to_unsigned(16#136E#, 15));
                i_position_y <= std_logic_vector(to_unsigned(16#0000#, 15));
                expected_phase      <= std_logic_vector(to_unsigned(16#07DA#, 15));
                expected_position_x <= std_logic_vector(to_unsigned(16#136E#, 15));
                expected_position_y <= std_logic_vector(to_unsigned(16#6C92#, 15));
                wait until o_valid_0 = '1';
                check_equal(result_phase_0,      expected_phase);
                check_equal(result_position_x_0, expected_position_x);
                check_equal(result_position_y_0, expected_position_y);
            elsif run("negative_rotation_works_stage_1") then
                i_valid <= '0';
                wait for c_CLK_PERIOD;
                i_valid <= '1';
                i_phase      <= std_logic_vector(to_unsigned(16#07DA#, 15));
                i_position_x <= std_logic_vector(to_unsigned(16#136E#, 15));
                i_position_y <= std_logic_vector(to_unsigned(16#6C92#, 15));
                expected_phase      <= std_logic_vector(to_unsigned(16#7E68#, 15));
                expected_position_x <= std_logic_vector(to_unsigned(16#1D25#, 15));
                expected_position_y <= std_logic_vector(to_unsigned(16#7649#, 15));
                wait until o_valid_1 = '1';
                check_equal(result_phase_1,      expected_phase);
                check_equal(result_position_x_1, expected_position_x);
                check_equal(result_position_y_1, expected_position_y);
            elsif run("positive_rotation_works_stage_1") then
                i_valid <= '0';
                wait for c_CLK_PERIOD;
                i_valid <= '1';
                i_phase      <= std_logic_vector(to_unsigned(16#7826#, 15));
                i_position_x <= std_logic_vector(to_unsigned(16#136E#, 15));
                i_position_y <= std_logic_vector(to_unsigned(16#136E#, 15));
                expected_phase      <= std_logic_vector(to_unsigned(16#0198#, 15));
                expected_position_x <= std_logic_vector(to_unsigned(16#1D25#, 15));
                expected_position_y <= std_logic_vector(to_unsigned(16#09B7#, 15));
                wait until o_valid_1 = '1';
                check_equal(result_phase_1,      expected_phase);
                check_equal(result_position_x_1, expected_position_x);
                check_equal(result_position_y_1, expected_position_y);
            end if;
        end loop;

        test_runner_cleanup(runner);
    end process p_main;

    test_runner_watchdog(runner, 10 ms);

end sim;
