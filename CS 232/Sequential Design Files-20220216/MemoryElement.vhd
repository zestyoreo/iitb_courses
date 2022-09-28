library ieee;
use ieee.std_logic_1164.all;

entity MemoryElement is
	port (clk, rst, D: in std_logic;
			Q: out std_logic);
end entity;

architecture memory of MemoryElement is
begin
	process (clk, rst, D)
	begin
		if rising_edge(clk) then
			if rst = '0' then
				Q <= '0';
			else
				Q <= D;
			end if;
		end if;
	end process;
end architecture;