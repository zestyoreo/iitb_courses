library ieee;
use ieee.std_logic_1164.all;

entity xor_gate is
	port(a,b: in std_logic; c: out std_logic);
end entity;

architecture xor_arc of xor_gate is

	signal p,q,r: std_logic;
	
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
		
	OrInst1: or_gate
		port map (a=>a, b=>b, c=>q);
		
	NotInst1: not_gate
		port map(a=>p,b=>r);
		
	AndInst2: and_gate
		port map (a=>q, b=>r, c=>c);
		
end architecture;	