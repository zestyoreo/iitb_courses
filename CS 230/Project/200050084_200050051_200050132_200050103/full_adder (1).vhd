--full adder
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity full_adder is
	port(
		a, b, cin: in std_logic;
		s, p, g: out std_logic);
end entity;

architecture basic of full_adder is
    signal intermed: std_logic;
begin
	
	g <= a and b;
	p <= a or b;
   intermed <= a xor b ;
	s <=  intermed xor cin;
	
end architecture;