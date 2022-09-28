library ieee;
use ieee.std_logic_1164.all;

entity nand_gate is
	port(a,b: in std_logic; c: out std_logic);
end entity;

architecture nand_arc of nand_gate is

	signal p: std_logic;
	
	component or_gate
		port (a,b: in std_logic; c: out std_logic);
	end component;
	
	component not_gate
		port (a: in std_logic; b: out std_logic);
	end component;
	
	component and_gate
		port (a,b: in std_logic; c: out std_logic);
	end component;
	
begin
		
	AndInst1: and_gate
		port map (a=>a, b=>b, c=>p);
		
	NotInst1: not_gate
		port map(a=>p,b=>c);
		
end architecture;	