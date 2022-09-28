library ieee;
use ieee.std_logic_1164.all;

entity Multiplier is
	port ( 
		a, b : in std_logic_vector (3 downto 0); 
		result: out std_logic_vector (7 downto 0)
	);
end entity;

architecture Multiplier_arc of Multiplier is

	signal a1b0,a2b0,a3b0: std_logic;		--signals for 1bit products
	signal a0b1,a1b1,a2b1,a3b1: std_logic;	--signals for 1bit products
	signal a0b2,a1b2,a2b2,a3b2: std_logic;	--signals for 1bit products
	signal a0b3,a1b3,a2b3,a3b3: std_logic;	--signals for 1bit products
	signal c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11: std_logic;	--signals for keeping track of any carry
	signal s1,s2,s3,s4,s5,s6: std_logic;	--signals for keeping track of partial sum

	component OnebitHalfAdd
		port(a,b: in std_logic; s,c: out std_logic);
	end component;

	component OnebitFullAdd
		port(a,b,cin: in std_logic; sum,cout: out std_logic);
	end component;

begin
		result(0) <= a(0) and b(0);
		a1b0 <= a(1) and b(0);
		a2b0 <= a(2) and b(0);
		a3b0 <= a(3) and b(0);
		
		a0b1 <= a(0) and b(1);
		a1b1 <= a(1) and b(1);
		a2b1 <= a(2) and b(1);
		a3b1 <= a(3) and b(1);
		
		a0b2 <= a(0) and b(2);
		a1b2 <= a(1) and b(2);
		a2b2 <= a(2) and b(2);
		a3b2 <= a(3) and b(2);
		
		a0b3 <= a(0) and b(3);
		a1b3 <= a(1) and b(3);
		a2b3 <= a(2) and b(3);
		a3b3 <= a(3) and b(3);
		
		HA1: OnebitHalfAdd
		port map(a1b0,a0b1,result(1),c1);
		
		FA2: OnebitFullAdd
		port map(a2b0,a1b1,c1,s1,c2);
		HA3: OnebitHalfAdd
		port map(s1,a0b2,result(2),c3);
		
		FA4: OnebitFullAdd
		port map(a3b0,a2b1,c2,s2,c4);
		FA5: OnebitFullAdd
		port map(s2,a1b2,c3,s3,c5);
		HA6: OnebitHalfAdd
		port map(s3,a0b3,result(3),c6);
		
		HA7: OnebitHalfAdd
		port map(a3b1,c4,s4,c7);
		FA8: OnebitFullAdd
		port map(s4,a2b2,c5,s5,c8);
		FA9: OnebitFullAdd
		port map(s5,a1b3,c6,result(4),c9);
		
		FA10: OnebitFullAdd
		port map(c7,a3b2,c8,s6,c10);
		FA11: OnebitFullAdd
		port map(s6,a2b3,c9,result(5),c11);
		
		FA12: OnebitFullAdd
		port map(c10,a3b3,c11,result(6),result(7));
		
end architecture;	