library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.ALL;

library vunit_lib;
context vunit_lib.vunit_context;

library cordic_lib;

entity cordic_pipeline_tb is
    generic(
        runner_cfg : string
    );
end cordic_pipeline_tb;


architecture sim of cordic_pipeline_tb is

-- Constants
constant c_CLK_PERIOD         : time := 10 us;
constant c_RESET_TIME         : time := 104 us;
constant c_ANGULAR_DATA_WIDTH : integer := 15;
constant c_LINEAR_DATA_WIDTH  : integer := 15;
constant c_PIPELINE_SIZE      : integer := 12;

-- Inputs
signal clk          : std_logic := '0';
signal reset        : std_logic := '0';
signal i_position_x : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0) := (others => 'U');
signal i_position_y : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0) := (others => 'U');
signal i_phase      : std_logic_vector(c_ANGULAR_DATA_WIDTH-1 downto 0) := (others => 'U');

-- Output
signal result_phase        : std_logic_vector(c_ANGULAR_DATA_WIDTH-1 downto 0);
signal result_position_x   : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal result_position_y   : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal expected_phase      : std_logic_vector(c_ANGULAR_DATA_WIDTH-1 downto 0);
signal expected_position_x : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);
signal expected_position_y : std_logic_vector(c_LINEAR_DATA_WIDTH-1 downto 0);

begin

    dut : entity cordic_lib.cordic_pipeline
    generic map (
        angular_data_width => c_ANGULAR_DATA_WIDTH,
        linear_data_width  => c_LINEAR_DATA_WIDTH
    ) port map (
        i_clk        => clk,
        i_reset      => reset,
        i_phase      => i_phase,
        i_position_x => i_position_x,
        i_position_y => i_position_y,
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
            if run("synchronous_reset_works") then
                reset <= '1';
                expected_phase      <= (others => '0');
                expected_position_x <= (others => '0');
                expected_position_y <= (others => '0');
                wait for c_CLK_PERIOD;
                check_not_unknown(result_phase);
                check_not_unknown(result_position_x);
                check_not_unknown(result_position_y);
                check_equal(result_phase,      expected_phase);
                check_equal(result_position_x, expected_position_x);
                check_equal(result_position_y, expected_position_y);
                wait for c_RESET_TIME;
                reset <= '0';
            elsif run("negative_rotation_works") then
                i_phase      <= std_logic_vector(to_unsigned(16#77DA#, 15));
                i_position_x <= std_logic_vector(to_unsigned(16#2000#, 15));
                i_position_y <= std_logic_vector(to_unsigned(16#0000#, 15));
                expected_position_x <= std_logic_vector(to_unsigned(16#308A#, 15));
                expected_position_y <= std_logic_vector(to_unsigned(16#6B7B#, 15));
                wait for c_CLK_PERIOD * c_PIPELINE_SIZE;
                check_equal(result_position_x, expected_position_x);
                check_equal(result_position_y, expected_position_y);
            elsif run("positive_rotation_works") then
                i_phase      <= std_logic_vector(to_unsigned(16#0826#, 15));
                i_position_x <= std_logic_vector(to_unsigned(16#2000#, 15));
                i_position_y <= std_logic_vector(to_unsigned(16#0000#, 15));
                expected_position_x <= std_logic_vector(to_unsigned(16#3089#, 15));
                expected_position_y <= std_logic_vector(to_unsigned(16#1485#, 15));
                wait for c_CLK_PERIOD * c_PIPELINE_SIZE;
                check_equal(result_position_x, expected_position_x);
                check_equal(result_position_y, expected_position_y);
            end if;
        end loop;

        test_runner_cleanup(runner);
    end process p_main;

end sim;
