library ieee;
use ieee.std_logic_1164.all;

entity mux is
	port(
        i0,i1: in std_logic_vector (7 downto 0); 
        s: in std_logic;
        o: out std_logic_vector (7 downto 0)
        );
end entity;

architecture mux_arc of mux is
begin
	o(0)<= ((not s) and i0(0)) or (s and i1(0));
        o(1)<= ((not s) and i0(1)) or (s and i1(1));
        o(2)<= ((not s) and i0(2)) or (s and i1(2));
        o(3)<= ((not s) and i0(3)) or (s and i1(3));
        o(4)<= ((not s) and i0(4)) or (s and i1(4));
        o(5)<= ((not s) and i0(5)) or (s and i1(5));
        o(6)<= ((not s) and i0(6)) or (s and i1(6));
        o(7)<= ((not s) and i0(7)) or (s and i1(7));
end architecture;	