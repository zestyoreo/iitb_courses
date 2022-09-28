library ieee;
use ieee.std_logic_1164.all;

entity OnebitHalfAdd is
	port(
        a,b: in std_logic; 
        s,c: out std_logic
        );
end entity;

architecture OnebitHalfAdd_arc of OnebitHalfAdd is
begin
        s<= a xor b;
        c<= a and b;
end architecture;	