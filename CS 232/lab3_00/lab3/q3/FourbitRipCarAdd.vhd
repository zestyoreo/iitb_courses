library ieee;
use ieee.std_logic_1164.all;

entity FourbitRipCarAdd is
	port ( 
		a, b : in std_logic_vector (3 downto 0); 
		cin: in std_logic;
		sum : out std_logic_vector (3 downto 0); 
		cout: out std_logic
	);
end entity;

architecture FourbitRipCarAdd_arc of FourbitRipCarAdd is

	signal c_1,c_2,c_3: std_logic;
	
	component OnebitFullAdd
		port (a, b, cin : in std_logic; sum, cout: out std_logic);
	end component;
	
begin

	FA1: OnebitFullAdd
		port map (a=>a(0),b=>b(0),cin=>cin,sum=>sum(0),cout=>c_1);
	FA2: OnebitFullAdd
		port map (a=>a(1),b=>b(1),cin=>c_1,sum=>sum(1),cout=>c_2);
	FA3: OnebitFullAdd
		port map (a=>a(2),b=>b(2),cin=>c_2,sum=>sum(2),cout=>c_3);
	FA4: OnebitFullAdd
		port map (a=>a(3),b=>b(3),cin=>c_3,sum=>sum(3),cout=>cout);
		
end architecture;	