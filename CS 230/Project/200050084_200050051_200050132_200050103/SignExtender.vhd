library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity SignExtender is
	generic(inp_width: integer := 6;
		op_width: integer := 16);
	port(
		SE_inp: in std_logic_vector(inp_width-1 downto 0);
		SE_op: out std_logic_vector(op_width-1 downto 0));
end entity;

architecture basic of SignExtender is
begin
	
	SE_op(inp_width-1 downto 0) <= SE_inp;
	
	extend:
	for i in inp_width to op_width-1 generate
		SE_op(i) <= SE_inp(inp_width-1);
	end generate;
	
end architecture;