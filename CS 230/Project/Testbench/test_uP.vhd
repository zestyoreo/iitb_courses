library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
--use std.textio.all ;
--use ieee.std_logic_textio.all; -- to compile add option --ieee=synopsys

entity test_uP is
end entity;

architecture test of test_uP is
    component uP is
        port(
        reset, clk: in std_logic);
    end component;
    signal clk, reset: std_logic := '0';
begin
    process
    begin
        wait for 5 ns;
        clk <= not clk;
		report "Switch" severity note;
    end process;
    
    process
    begin
        reset <= '1';
        wait until (clk = '1');
        wait until (clk = '1');
        reset <= '0';
        wait;
    end process;

    instance: uP
    port map(reset => reset, clk => clk);
    
end architecture;