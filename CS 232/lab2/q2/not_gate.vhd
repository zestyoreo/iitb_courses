library ieee;
use ieee.std_logic_1164.all;

entity not_gate is
	port(
        a: in std_logic; 
        o: out std_logic
        );
end entity;

architecture not_arc of not_gate is

    component nand_gate
        port (a,b: in std_logic; c: out std_logic);
	end component;

begin

    Nand1: nand_gate
		port map (a=>a,b=>a,c=>o);

end architecture;	