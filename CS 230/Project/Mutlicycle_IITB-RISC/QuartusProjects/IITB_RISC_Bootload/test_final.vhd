library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
--use std.textio.all ;
--use ieee.std_logic_textio.all; -- to compile add option --ieee=synopsys

entity test_final is
end entity;

architecture test of test_final is
    component IITB_RISC is
    port(
    reset, clk: in std_logic;
	 op_code_out: out std_logic_vector(3 downto 0);
	 T_out: out std_logic_vector(24 downto 0));
end component;
    signal clk, reset: std_logic := '0';
	signal op_code: std_logic_vector(3 downto 0);
	signal T: std_logic_vector(24 downto 0);
begin
    process
    begin
        wait for 10 ns;
        clk <= not clk;
		report "Switch" severity note;
    end process;
    
    process
    begin
        reset <= '1';
        wait until (clk = '1');
        wait until (clk = '0');
        reset <= '0';
        wait;
    end process;

    risc_instance: IITB_RISC
    port map(reset => reset, clk => clk, op_code_out => op_code, T_out => T);
    
end architecture;