-- Title				: Data-Path Component for multiple Load and Store 
-- Purpose				:
-- Brief Description	:
-- Author				: Shashank OV
-- Date					: Oct. 11, 2016 

library ieee;
use ieee.numeric_std.all;
use ieee.std_logic_1164.all;
use ieee.math_real.all;

library work;
use work.basic.all;

entity ls_multiple is
	generic(input_width: integer := 8);
	port(
		input: in std_logic_vector(input_width-1 downto 0);
		ena, clk, set_zero, reset: in std_logic;
		valid, invalid_next: out std_logic;
		address: out std_logic_vector(integer(ceil(log2(real(input_width))))-1 downto 0));
end entity;

architecture basic of ls_multiple is
	signal reg_in, reg_out, reg_temp: std_logic_vector(input_width-1 downto 0);
	signal reg_ena, not_zero: std_logic;
	signal addr: std_logic_vector(address'length-1 downto 0);
	
	component p_encoder is
		generic(input_width: integer := 16);
		port(
			input: in std_logic_vector(input_width-1 downto 0);
			output: out std_logic_vector(integer(ceil(log2(real(input_width))))-1 downto 0);
			valid: out std_logic);
	end component;

begin
	
	address <= addr;
	
	PE: p_encoder
		generic map(input_width)
		port map(input => reg_out, output => addr, valid => valid);
		
	reg_ena <= ena or set_zero;
	
	data_in: process(input, set_zero, reg_out, reg_temp, addr)
	begin
		reg_temp <= reg_out;
		reg_temp(to_integer(unsigned(addr))) <= '0';
		
		if(unsigned(reg_temp) = 0) then
			invalid_next <= '1';
		else
			invalid_next <= '0';
		end if;
		
		if (set_zero = '1') then
			reg_in <= reg_temp;
		else
			reg_in <= input;
		end if;
	end process;
	
	T: my_reg
		generic map(input_width)
		port map(
			Din => reg_in, Dout => reg_out,
			clk => clk, ena => reg_ena, clr => reset);
			
end architecture;
