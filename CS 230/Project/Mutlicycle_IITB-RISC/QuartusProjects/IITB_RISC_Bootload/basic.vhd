-- Title				: Basic Logic Components 
-- Purpose				:
-- Brief Description	:
-- Author				: Shashank OV
-- Date					: Apr. 11, 2016 

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

package basic is

	component fulladder is
		port(
			a, b, c0: in std_logic;	--input bits to be added and input carry
			c1, s: out std_logic);	--output carry and sum bit
	end component;
	
	component clk_divider is
		generic(ratio: integer := 5);
		port(
			clk_in: in std_logic;
			clk_out: out std_logic);		
	end component;
	
	component my_reg is
	generic ( data_width : integer);
	port(
		clk, ena, clr: in std_logic;
		Din: in std_logic_vector(data_width-1 downto 0);
		Dout: out std_logic_vector(data_width-1 downto 0));
	end component;

	component adder2Bit is
		port(
			a0, a1, b0, b1, c0: in std_logic;	--input pins
			s0, s1, c2: out std_logic);	--output pins
	end component;

	component adder8Bit is
		port(
			A, B: in std_logic_vector(7 downto 0);	--input numbers to be added
			S: out std_logic_vector(7 downto 0);	--result
			c0: in std_logic;	--input carry
			c8: out std_logic);	--ouput carry
	end component;

	component Sub16 is	--subtracter
		port(
			A, B: in std_logic_vector(15 downto 0);	--input numbers
			S: out std_logic_vector(15 downto 0);	--output result
			c16: out std_logic);	-- output overflow/carry
	end component;

	component equal_to is
		generic ( data_width : integer := 16);
		port (
			A, B: in std_logic_vector(data_width-1 downto 0);
			R: out std_logic);
	end component;
	
	component greater_than is
	generic ( data_width : integer := 16);
	port (
		A, B: in std_logic_vector(data_width-1 downto 0);
		R: out std_logic);
	end component;
	
	component decr4 is
	port(
		A : in std_logic_vector(3 downto 0);
		B : out std_logic_vector(3 downto 0));
	end component;

	component mux4 is
		generic(input_width: integer := 16);
		port(
			inp1, inp2, inp3, inp4: in std_logic_vector(input_width-1 downto 0) := (others => '0');
			sel: in std_logic_vector(1 downto 0);
			output: out std_logic_vector(input_width-1 downto 0));
	end component;

	component mux8 is
		generic(input_width: integer := 16);
		port(
			inp1, inp2, inp3, inp4, inp5, inp6, inp7, inp8: in std_logic_vector(input_width-1 downto 0) := (others => '0');
			sel: in std_logic_vector(2 downto 0);
			output: out std_logic_vector(input_width-1 downto 0));
	end component;

end package;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity decr4 is
	port(
		A : in std_logic_vector(3 downto 0);
		B : out std_logic_vector(3 downto 0));
end entity;

architecture myOwn of decr4 is
	signal c1, c2, c3 : std_logic;
	
begin

	B(0) <= (not A(0));	
	c1 <= (A(0));		
	
	B(1) <= ((A(1) and c1) or ((not A(1)) and (not c1)));
	c2 <= (A(1) or c1);
	
	B(2) <= ((A(2) and c2) or ((not A(2)) and (not c2)));
	c3 <= (A(2) or c2);
	
	B(3) <= ((A(3) and c3) or ((not A(3)) and (not c3)));
	
end myOwn;
	
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity fulladder is
	port(
		a, b, c0: in std_logic;	--input bits to be added and input carry
		c1, s: out std_logic);	--output carry and sum bit
end entity;

architecture myOwn of fulladder	is
	signal abxor: std_logic;	--xor of a and b
begin

	abxor <= (((not a) and b) or (a and (not b)));	--xor of a and b
	s <= (((not abxor) and c0) or (abxor and (not c0)));	--xor of a,b and c0
	c1 <= (((a and b) or (a and c0)) or (c0 and b));	--ab+ bc0+ ac0

end myOwn;	 	

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

library work;
use work.basic.all;

entity adder2Bit is
	port(
		a0, a1, b0, b1, c0: in std_logic;	--input pins
		s0, s1, c2: out std_logic);	--output pins
end entity;

architecture myOwn of adder2Bit is
	signal c1: std_logic;
begin
	full1: fullAdder port map( a =>a0, b=>b0, s => s0, c0 => c0, c1 => c1);	--first full adder
	full2: fullAdder port map( a =>a1, b=>b1, s => s1, c0 => c1, c1 => c2);	--second full adder
end myOwn;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

library work;
use work.basic.all;

entity adder8Bit is
	port(
		A, B: in std_logic_vector(7 downto 0);	--input numbers to be added
		S: out std_logic_vector(7 downto 0);	--result
		c0: in std_logic;	--input carry
		c8: out std_logic);	--ouput carry
end entity;

architecture myOwn of adder8Bit is
	signal c2, c4, c6: std_logic;	--intermediate carries
	
begin
	--4 full adders in cascade
	full21: adder2Bit port map( a0 =>A(0), a1 =>A(1), b0 =>B(0), b1 =>B(1), c0 =>c0, c2 =>c2, s0 =>S(0), s1 =>S(1));
	full22: adder2Bit port map( a0 =>A(2), a1 =>A(3), b0 =>B(2), b1 =>B(3), c0 =>c2, c2 =>c4, s0 =>S(2), s1 =>S(3));
	full23: adder2Bit port map( a0 =>A(4), a1 =>A(5), b0 =>B(4), b1 =>B(5), c0 =>c4, c2 =>c6, s0 =>S(4), s1 =>S(5));
	full24: adder2Bit port map( a0 =>A(6), a1 =>A(7), b0 =>B(6), b1 =>B(7), c0 =>c6, c2 =>c8, s0 =>S(6), s1 =>S(7));

end myOwn;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity greater_than is
	generic ( data_width : integer := 16);
	port (
		A, B: in std_logic_vector(data_width-1 downto 0);
		R: out std_logic);
end entity;

architecture Serial of greater_than is
	signal not_equal, temp2: std_logic_vector(data_width-1 downto 0);
begin
	
	not_equal <= ((A and (not B)) or ((not A) and B));
	temp2(data_width-1) <= (not not_equal(data_width-1)) or A(data_width-1); 
	gen: for i in data_width-2 downto 0 generate
		temp2(i) <= ((A(i) or (not not_equal(i))) and temp2(i+1)); 
	end generate;
	
	R <= (temp2(0) and not_equal(0));
end architecture;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity equal_to is
	generic ( data_width : integer := 16);
	port (
		A, B: in std_logic_vector(data_width-1 downto 0);
		R: out std_logic);
end entity;

architecture myOwn of equal_to is
	signal int, temp: std_logic_vector(data_width-1 downto 0);
begin
	int <= ((A and (not B)) or ((not A) and B));	--XOR operation
	
	--taking and of all bits in int
	temp(0) <= int(0);
    gen: for i in 1 to data_width-1 generate
        temp(i) <= temp(i-1) or int(i);
    end generate; 
    
    R <= not temp(data_width-1);
end myOwn;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity my_reg is
	generic ( data_width : integer);
	port(
		clk, ena, clr: in std_logic;
		Din: in std_logic_vector(data_width-1 downto 0);
		Dout: out std_logic_vector(data_width-1 downto 0));
end entity;

architecture myOwn of my_reg is
begin
	process(clk, clr)	
	begin
		if(clk'event and clk='1') then
			if (ena='1') then
				Dout <= Din;
			end if;
		end if;
		if(clr = '1') then
			Dout <= (others => '0');
		end if;
	end process;
	
end myOwn;		

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

library work;
use work.basic.all;

entity Sub16 is
	port(
		A, B: in std_logic_vector(15 downto 0);	--input numbers to be added
		S: out std_logic_vector(15 downto 0);	--result
		c16: out std_logic);	--ouput carry
end entity;

architecture myOwn of Sub16 is
	signal notB: std_logic_vector(15 downto 0);
	signal cint : std_logic;
begin
	
	notB <= not B;
	
	adder1: adder8Bit port map( A => A(7 downto 0), B => notB(7 downto 0), c0 => '1', c8 => cint, S => S(7 downto 0));	--8-bit adder
	adder2: adder8Bit port map( A => A(15 downto 8), B => notB(15 downto 8), c0 => cint, c8 => c16, S => S(15 downto 8));	--8-bit adder
	
end architecture;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

library work;
use work.basic.all;

entity clk_divider is
	generic(ratio: integer := 5);
	port(
		clk_in: in std_logic;
		clk_out: out std_logic);		
end entity;

architecture divider of clk_divider is
	signal inf, outf: std_logic_vector(ratio-1 downto 0);
	
begin
	inf <= std_logic_vector(unsigned(outf) + 1);
	process(clk_in)
	begin
	
		if(clk_in = '1') then
			outf <= inf;
		end if;
	end process;
	clk_out <= outf(ratio - 1);
	
end architecture;


library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity mux4 is
	generic(input_width: integer := 16);
	port(
		inp1, inp2, inp3, inp4: in std_logic_vector(input_width-1 downto 0) := (others => '0');
		sel: in std_logic_vector(1 downto 0);
		output: out std_logic_vector(input_width-1 downto 0));
end entity;

architecture behave of mux4 is
begin
	output <= inp1 when (sel = "00") else
		inp2 when (sel = "01") else
		inp3 when (sel = "10") else
		inp4;
end;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity mux8 is
	generic(input_width: integer := 16);
	port(
		inp1, inp2, inp3, inp4, inp5, inp6, inp7, inp8: in std_logic_vector(input_width-1 downto 0) := (others => '0');
		sel: in std_logic_vector(2 downto 0);
		output: out std_logic_vector(input_width-1 downto 0));
end entity;

architecture behave of mux8 is
begin
	output <= inp1 when (sel = "000") else
		inp2 when (sel = "001") else
		inp3 when (sel = "010") else
		inp4 when (sel = "011") else
		inp5 when (sel = "100") else
		inp6 when (sel = "101") else
		inp7 when (sel = "110") else
		inp8;
end;
