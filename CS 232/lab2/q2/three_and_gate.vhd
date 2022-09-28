library ieee;
use ieee.std_logic_1164.all;

entity three_and_gate is
	port(
        a,b,c,e: in std_logic; 
        o: out std_logic
        );
end entity;

architecture three_and_gate_arc of three_and_gate is

    signal p,q,r,s,t: std_logic;

    component nand_gate
        port (a,b: in std_logic; c: out std_logic);
	end component;
    component not_gate
        port (a: in std_logic; o: out std_logic);
	end component;

begin

    Nand1: nand_gate
		port map (a=>a,b=>b,c=>p);
    Not1: not_gate
		port map (a=>p,o=>q);
    Nand2: nand_gate
		port map (a=>q,b=>c,c=>r);
    Not2: not_gate
		port map (a=>r,o=>s);
    Nand3: nand_gate
		port map (a=>s,b=>e,c=>t);
    Not3: not_gate
		port map (a=>t,o=>o);

end architecture;	