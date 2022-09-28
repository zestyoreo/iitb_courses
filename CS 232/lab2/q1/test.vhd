library ieee;
use ieee.std_logic_1164.all;

entity test is
end test;

architecture beh of test is

	signal i_s : std_logic_vector(7 downto 0);  -- input signal
	signal e_s : std_logic; --enabler signal
   signal o_s : std_logic_vector(2 downto 0);  -- output signal
	
   component EightbyThreeEncode
      port ( 
        i : in std_logic_vector(7 downto 0); 
        en: in std_logic;
        z : out std_logic_vector(2 downto 0)
			);

	end component;
	
begin  

encoder1 : EightbyThreeEncode 
	port map (i => i_s,z => o_s,en => e_s);
	
	process
   begin
		 e_s<='1';
       i_s<="00000001";
       wait for 100 ns;
       i_s<="00000010";
       wait for 100 ns;
       i_s<="00000100";
       wait for 100 ns;
       i_s<="00001000";
       wait for 100 ns;
       i_s<="00010000";
       wait for 100 ns;
       i_s<="00100000";
       wait for 100 ns;
       i_s<="01000000";
       wait for 100 ns;
       i_s<="10000000";
       wait for 100 ns;
		 e_s<='0';
		 wait for 100 ns;
    end process;
end beh;