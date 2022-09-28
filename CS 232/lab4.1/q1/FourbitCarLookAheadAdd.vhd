library ieee;
use ieee.std_logic_1164.all;

entity FourbitCarLookAheadAdd is
	port ( 
		a, b : in std_logic_vector (3 downto 0); 
		cin: in std_logic;
		sum : out std_logic_vector (3 downto 0); 
		cout: out std_logic
	);
end entity;

architecture FourbitCarLookAheadAdd_arc of FourbitCarLookAheadAdd is

	signal c1,c2,c3: std_logic;
	signal p,g: std_logic_vector(3 downto 0); 
	
	component PartialFullAdder
		port (
		a,b,cin : in std_logic;
		s,p,g: out std_logic
	);
	end component;
	
begin

	PFA1: PartialFullAdder 
		port map( a=>a(0), b=>b(0), cin=>cin, s=>sum(0), p=>p(0), g=>g(0));
	PFA2: PartialFullAdder 
		port map( a=>a(1), b=>b(1), cin=>c1, s=>sum(1), p=>p(1), g=>g(1));
	PFA3: PartialFullAdder 
		port map( a=>a(2), b=>b(2), cin=>c2, s=>sum(2), p=>p(2), g=>g(2));
	PFA4: PartialFullAdder 
		port map( a=>a(3), b=>b(3), cin=>c3, s=>sum(3), p=>p(3), g=>g(3));
 
	c1 <= g(0) or (p(0) and cin);
	c2 <= g(1) or (p(1) and g(0)) or (p(1) and p(0) and cin);
	c3 <= g(2) or (p(2) and g(1)) or (p(2) and p(1) and g(0)) or (p(2) and p(1) and p(0) and cin);
	cout <= g(3) or (p(3) and g(2)) or (p(3) and p(2) and g(1)) or (p(3) and p(2) and p(1) and g(0)) or (p(3) and p(2) and p(1) and p(0) and cin);
		
end architecture;	

