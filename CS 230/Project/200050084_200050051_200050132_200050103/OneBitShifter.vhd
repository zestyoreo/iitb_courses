--One bit shifter

library ieee;
use ieee.std_logic_1164.all ;
use ieee.numeric_std.all ;

entity OneBitShifter is
port(
	inp : in std_logic_vector(15 downto 0) ;
	op1,op2 : out std_logic ;
	op : out std_logic_vector(15 downto 0) 
);
end entity;

architecture OBS_ARCH of OneBitShifter is

begin

	op1 <= inp(15) ;
	--op <= std_logic_vector(shift_left(to_unsigned(inp),1)) ;
	GEN:
		for i in 1 to 15 generate
			op(i) <= inp(i-1) ;
	end generate GEN;

	process(inp)
	begin
	
	if inp = "1000000000000000" then
		op2 <= '1' ;
	else
		op2 <= '0' ;
	end if;
	
	end process;
end OBS_ARCH ;