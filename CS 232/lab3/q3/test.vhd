library ieee;
use ieee.std_logic_1164.all;

entity test is
end test;

architecture beh of test is

	signal a_s,b_s,sum_s : std_logic_vector(3 downto 0); 
	signal cin_s,cout_s: std_logic;   -- signals
	
   component FourbitRipCarAddSub
		port ( 
			a, b : in std_logic_vector (3 downto 0); 
			cin: in std_logic;
			sum : out std_logic_vector (3 downto 0); 
			cout: out std_logic
		);
	end component;
	
begin  

fourbitadder1 : FourbitRipCarAddSub
	port map (a => a_s,b => b_s,cin => cin_s,sum=> sum_s,cout=> cout_s);
	
	process
   begin
		 cin_s<='0';
       a_s<="0000";
       b_s<="0001";
       wait for 100 ns;
       a_s<="1000";
       b_s<="0101";
       wait for 100 ns;
       a_s<="1111";
       b_s<="1111";
       wait for 100 ns;
       cin_s<='1';
       a_s<="0010";
       b_s<="0001";
       wait for 100 ns;
       a_s<="1000";
       b_s<="0101";
       wait for 100 ns;
       a_s<="1110";
       b_s<="1111";
       wait for 100 ns;
    end process;
end beh;