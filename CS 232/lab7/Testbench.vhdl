library std;
use std.textio.all;

library ieee;
use ieee.std_logic_1164.all;

entity Testbench is
end entity;
architecture Behave of Testbench is
  ----------------------------------------------------------------
  --  edit the following lines to set the number of i/o's of your
  --  DUT.
  ----------------------------------------------------------------
  constant number_of_inputs  : integer := 2;  -- # input bits to your design.
  constant number_of_outputs : integer := 15;  -- # output bits from your design.
  ----------------------------------------------------------------
  ----------------------------------------------------------------
  -- Note that you will have to wrap your design into the DUT
  -- as indicated in class.
  
  component TrafficLightsController is
	  port(clk, rst, tr1, tr4 : in std_logic;
	  r, g, y: out std_logic_vector (4 downto 0));
  end component;
  
  constant MAX_CYCLES : integer := 550;
  signal clk, rst: std_logic;
  signal input_vector  : std_logic_vector(number_of_inputs-1 downto 0);
  signal output_vector : std_logic_vector(number_of_outputs-1 downto 0);
  
  -- bit-vector to std-logic-vector and vice-versa
  function to_std_logic_vector(x: bit_vector) return std_logic_vector is
     alias lx: bit_vector(1 to x'length) is x;
     variable ret_val: std_logic_vector(1 to x'length);
  begin
     for I in 1 to x'length loop
        if(lx(I) = '1') then
          ret_val(I) := '1';
        else
          ret_val(I) := '0';
        end if;
     end loop; 
     return ret_val;
  end to_std_logic_vector;

  function to_bit_vector(x: std_logic_vector) return bit_vector is
     alias lx: std_logic_vector(1 to x'length) is x;
     variable ret_val: bit_vector(1 to x'length);
  begin
     for I in 1 to x'length loop
        if(lx(I) = '1') then
          ret_val(I) := '1';
        else
          ret_val(I) := '0';
        end if;
     end loop; 
     return ret_val;
  end to_bit_vector;

begin
	
	TLC_1: TrafficLightsController
		port map (clk, rst, input_vector(0), input_vector(1), output_vector(14 downto 10), output_vector(9 downto 5), output_vector(4 downto 0));
	
	clock_process :process
		 variable CYCLES_COUNT: integer := 0;
	begin
		while CYCLES_COUNT < MAX_CYCLES loop
			clk <= '0';
			wait for 500 ms;
			clk <= '1';
			wait for 500 ms;
			CYCLES_COUNT := CYCLES_COUNT + 1;
		end loop;
		wait;
	end process;

	reset_process :process
	begin
		rst <= '1';
		wait for 100 ns;
		rst <= '0';
		wait;
	end process;

	controller_process :process 
		 FILE OUTFILE: text  open write_mode is 	"../../output.txt";-- Same directory as vhdl file

		 -- for read/write.
		 variable OUTPUT_LINE: Line;
		 variable CYCLES_COUNT: integer := 0;
	 
	begin
		input_vector <= "11";
		wait for 100 ps;
		while CYCLES_COUNT < MAX_CYCLES/2 loop
			wait for 600 ms;
			write(OUTPUT_LINE, to_bit_vector(output_vector));
			writeline(OUTFILE, OUTPUT_LINE);		
			wait for 400 ms;
			CYCLES_COUNT := CYCLES_COUNT + 1;
		end loop;
		input_vector <= "00";
		while CYCLES_COUNT < MAX_CYCLES loop
			wait for 600 ms;
			write(OUTPUT_LINE, to_bit_vector(output_vector));
			writeline(OUTFILE, OUTPUT_LINE);	
			wait for 400 ms;
			CYCLES_COUNT := CYCLES_COUNT + 1;
		end loop;
		wait;
	end process;

end Behave;
