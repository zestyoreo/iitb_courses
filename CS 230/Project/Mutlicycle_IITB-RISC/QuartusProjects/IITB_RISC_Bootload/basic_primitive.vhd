library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity my_reg_prim is
	generic ( data_width : integer);
	port(
		clk, ena: in std_logic;
		Din: in std_logic_vector(data_width-1 downto 0);
		Dout: out std_logic_vector(data_width-1 downto 0));
end entity;

architecture myOwn of my_reg_prim is
begin
	process(clk)	
	begin
		if(clk'event and clk='1') then
			if (ena='1') then
				Dout <= Din;
			end if;
		end if;
	end process;
	
end myOwn;