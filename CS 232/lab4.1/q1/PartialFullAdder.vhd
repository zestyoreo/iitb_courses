library ieee;
use ieee.std_logic_1164.all;
 
entity PartialFullAdder is
    port (
		a,b,cin : in std_logic;
		s,p,g: out std_logic
	);
end entity;
 
architecture PartialFullAdder_arc of PartialFullAdder is

begin
    
    p<= a xor b; -- a xor b 
    s<= a xor b xor cin; -- a xor b xor cin
    g<= a and b;
 
end architecture;
