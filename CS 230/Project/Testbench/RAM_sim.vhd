library ieee;
use ieee.std_logic_1164.all;
use ieee.math_real.all;
use ieee.numeric_std.all;

library work;
use work.basic.all;

entity RAM_SIM is
	generic(
		word_length: integer := 16;
		num_words: integer := 65536);
		
	port(
		data_in: in std_logic_vector(word_length-1 downto 0);
		data_out : out std_logic_vector(word_length-1 downto 0);
		address: in std_logic_vector(integer(ceil(log2(real(num_words))))-1 downto 0);
		clk, wr_ena, rd_ena, reset: in std_logic);
		
end entity;

architecture struct of RAM_SIM is
	type word_bus is array(num_words-1 downto 0) of std_logic_vector(word_length-1 downto 0);
	signal reg_out: word_bus;
	signal ena: std_logic_vector(num_words-1 downto 0);
	
begin
	
	GEN_REG: 
	for i in 0 to num_words-1 generate
		REG: my_reg
			generic map(word_length)
			port map(clk => clk, ena => ena(i), 
				Din => data_in, Dout => reg_out(i), clr => reset);
	end generate GEN_REG;
	
	in_decode: process(address, wr_ena)
	begin
		ena <= (others => '0');
		ena(to_integer(unsigned(address))) <= wr_ena;	
	end process;
	
	data_out <= reg_out(to_integer(unsigned(address))) when (rd_ena = '1')
		else (others => 'Z');
	
end architecture;