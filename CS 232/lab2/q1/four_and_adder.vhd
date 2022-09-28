library ieee;
use ieee.std_logic_1164.all;

entity four_and_adder is
	port(
        i0,i1,i2,i3: in std_logic; 
        e: in std_logic;
        o: out std_logic
        );
end entity;

architecture four_and_adder_arc of four_and_adder is
    signal p,q:  std_logic;

    component mux
		port (i0,i1,e,s: in std_logic; o: out std_logic);
	end component;

begin
    Mux1: mux
		port map (i0=>i0,i1=>i1,e=>e,s=>i1,o=>p);
    Mux2: mux
		port map (i0=>p,i1=>i2,e=>e,s=>i2,o=>q);
    Mux3: mux
		port map (i0=>q,i1=>i3,e=>e,s=>i3,o=>o);
end architecture;	