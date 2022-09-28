library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity carry_generator is
	generic(group_width: integer := 4);
	port(
		P, G: in std_logic_vector(group_width-1 downto 0);  --propagator and generator
		cin: in std_logic;
		cout: out std_logic_vector(group_width-1 downto 0));
end entity;

architecture carry_generator_arc of carry_generator is
	signal Carry: std_logic_vector(group_width downto 0);
begin
	
	Carry(0) <= cin;
	for i in 1 to group_width generate
		Carry(i) <= G(i-1) or (P(i-1) and Carry(i-1)); 
	end generate;

	cout <= Carry(group_width downto 1);
end architecture;