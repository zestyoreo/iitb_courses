library ieee;
use ieee.std_logic_1164.all;

entity ModOnebitFullAdd is
	port ( 
		a, b, cin, passin : in std_logic; 
        a_out, b_out, sum, cout: out std_logic
	); 
end entity;

architecture ModOnebitFullAdd_arc of ModOnebitFullAdd is

	signal prod,p,q,r: std_logic;
	
	component OnebitHalfAdd
		port (
			a,b: in std_logic; 
			s,c: out std_logic
		);
	end component;
	
begin
	prod<= a and b;

	HA1: OnebitHalfAdd
		port map (a=>passin,b=>prod,s=>p,c=>q);
	HA2: OnebitHalfAdd
		port map (a=>p,b=>cin,s=>sum,c=>r);

	cout<= r or q;
	a_out<= a;
	b_out<= b;
		
end architecture;	