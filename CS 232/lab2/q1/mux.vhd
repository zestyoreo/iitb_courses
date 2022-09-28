library ieee;
use ieee.std_logic_1164.all;

entity mux is
	port(
        i0,i1,e,s: in std_logic; 
        o: out std_logic
        );
end entity;

architecture mux_arc of mux is
begin
	o<= e and (((not s) and i0) or (s and i1));
end architecture;	