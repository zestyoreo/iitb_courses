library ieee;
use ieee.std_logic_1164.all;

entity test is
end test;

architecture beh of test is

	signal a_s,b_s : std_logic_vector(3 downto 0); 
   signal sel_s : std_logic_vector(2 downto 0); 
   signal result_s : std_logic_vector(7 downto 0); 
	
   component FourbitALU
      port ( 
         a, b: in std_logic_vector (3 downto 0); 
         sel: in std_logic_vector (2 downto 0);
         result: out std_logic_vector (7 downto 0)
      );
	end component;
	
begin  

ALU1 : FourbitALU
	port map (a => a_s,b => b_s,sel => sel_s,result=> result_s);
	
	process
   begin
      --add
		 sel_s<="000";
       a_s<="0010";
       b_s<="0001";
       wait for 100 ns;
       a_s<="0001";
       b_s<="0100";
       wait for 100 ns;
       a_s<="1011";
       b_s<="1011";
       wait for 100 ns;

      --subtract 
       sel_s<="001";
       a_s<="0010";
       b_s<="0001";
       wait for 100 ns;
       a_s<="0001";
       b_s<="0100";
       wait for 100 ns;
       a_s<="1011";
       b_s<="1011";
       wait for 100 ns;

      --multiply 
       sel_s<="010";
       a_s<="0010";
       b_s<="0001";
       wait for 100 ns;
       a_s<="0001";
       b_s<="0100";
       wait for 100 ns;
       a_s<="1011";
       b_s<="1011";
       wait for 100 ns;

      --compare
       sel_s<="011";
       a_s<="0010";
       b_s<="0001";
       wait for 100 ns;
       a_s<="0001";
       b_s<="0100";
       wait for 100 ns;
       a_s<="1011";
       b_s<="1011";
       wait for 100 ns;

      --bitwise NAND
       sel_s<="100";
       a_s<="0010";
       b_s<="0001";
       wait for 100 ns;
       a_s<="0001";
       b_s<="0100";
       wait for 100 ns;
       a_s<="1011";
       b_s<="1011";
       wait for 100 ns;

      --bitwise NOR
       sel_s<="101";
       a_s<="0010";
       b_s<="0001";
       wait for 100 ns;
       a_s<="0001";
       b_s<="0100";
       wait for 100 ns;
       a_s<="1011";
       b_s<="1011";
       wait for 100 ns;
      
       --bitwise XOR
       sel_s<="110";
       a_s<="0010";
       b_s<="0001";
       wait for 100 ns;
       a_s<="0001";
       b_s<="0100";
       wait for 100 ns;
       a_s<="1011";
       b_s<="1011";
       wait for 100 ns;

      --bitwise XNOR
       sel_s<="111";
       a_s<="0010";
       b_s<="0001";
       wait for 100 ns;
       a_s<="0001";
       b_s<="0100";
       wait for 100 ns;
       a_s<="1011";
       b_s<="1011";
       wait for 100 ns;
       
    end process;
end beh;