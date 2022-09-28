library ieee;
use ieee.std_logic_1164.all;

entity Comparator is
	port ( 
		a, b: in std_logic_vector (3 downto 0); 
		result: out std_logic_vector (2 downto 0)
	); 
end entity;

architecture Comparator_arc of Comparator is

	signal one_bit,sign_bit: std_logic;
    signal b_dash,diff: std_logic_vector (3 downto 0);
	
	component FourbitCarLookAheadAdd
		port ( 
			a, b : in std_logic_vector (3 downto 0); 
			cin: in std_logic;
			sum : out std_logic_vector (3 downto 0); 
			cout: out std_logic
		);
	end component;
	
begin
    one_bit<='1';
	 
    b_dash(0)<= (one_bit and not (b(0))) or (not (one_bit) and b(0));
	b_dash(1)<= (one_bit and not (b(1))) or (not (one_bit) and b(1));
    b_dash(2)<= (one_bit and not (b(2))) or (not (one_bit) and b(2));
    b_dash(3)<= (one_bit and not (b(3))) or (not (one_bit) and b(3));
	 
	FullAddSub1: FourbitCarLookAheadAdd	--finding a-b
		port map (a=>a,b=>b_dash,cin=>one_bit,sum=>diff,cout=>sign_bit);
    
    result(1)<= not ((not (sign_bit)) or diff(0) or diff(1) or diff(2) or diff(3));
    result(0)<= ((not (sign_bit)) or diff(0) or diff(1) or diff(2) or diff(3)) and (not (sign_bit));
    result(2)<= ((not (sign_bit)) or diff(0) or diff(1) or diff(2) or diff(3)) and sign_bit;

		
end architecture;	