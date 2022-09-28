library ieee;
use ieee.std_logic_1164.all;

entity nor_gate is
	port(a,b: in std_logic; c: out std_logic);
end entity;

architecture nor_arc of nor_gate is

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
		
	OrInst1: or_gate
		port map (a=>a, b=>b, c=>p);
		
	NotInst1: not_gate
		port map(a=>p,b=>c);
		
end architecture;	