library ieee;
use ieee.std_logic_1164.all;

entity FourbitRipCarAddSub is
	port ( 
		a, b : in std_logic_vector (3 downto 0); 
		cin: in std_logic;
		sum : out std_logic_vector (3 downto 0); 
		cout: out std_logic
	);
end entity;

architecture FourbitRipCarAddSub_arc of FourbitRipCarAddSub is

	signal b_dash: std_logic_vector (3 downto 0);
	
	component FourbitRipCarAdd
		port ( 
			a, b : in std_logic_vector (3 downto 0); 
			cin: in std_logic;
			sum : out std_logic_vector (3 downto 0); 
			cout: out std_logic
		);
	end component;
	
begin
	b_dash(0)<= b(0) xor cin;
	b_dash(1)<= b(1) xor cin;
	b_dash(2)<= b(2) xor cin;
	b_dash(3)<= b(3) xor cin; 

	FBRA1: FourbitRipCarAdd
		port map(a=>a,b=>b_dash,cin=>cin,sum=>sum,cout=>cout);
		
end architecture;	