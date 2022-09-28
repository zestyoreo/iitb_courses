library ieee;
use ieee.std_logic_1164.all;

entity BitwiseNOR is
	port ( 
		a, b: in std_logic_vector (3 downto 0);
		c: out std_logic_vector (3 downto 0)
	);
	end entity;

architecture BitwiseNOR_arc of BitwiseNOR is
	
begin
	c(0)<= not(a(0) or b(0));
	c(1)<= not(a(1) or b(1));
    c(2)<= not(a(2) or b(2));
    c(3)<= not(a(3) or b(3));
		
end architecture;	