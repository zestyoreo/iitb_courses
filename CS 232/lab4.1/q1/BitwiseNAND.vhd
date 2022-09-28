library ieee;
use ieee.std_logic_1164.all;

entity BitwiseNAND is
	port ( 
		a, b: in std_logic_vector (3 downto 0);
		c: out std_logic_vector (3 downto 0)
	);
	end entity;

architecture BitwiseNAND_arc of BitwiseNAND is
	
begin
	c(0)<= not(a(0) and b(0));
	c(1)<= not(a(1) and b(1));
    c(2)<= not(a(2) and b(2));
    c(3)<= not(a(3) and b(3));
		
end architecture;	