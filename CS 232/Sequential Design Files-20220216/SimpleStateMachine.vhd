library ieee;
use ieee.std_logic_1164.all;

entity SimpleStateMachine is
	port (clk, rst, x: in std_logic;
			y: out std_logic);
end entity;

architecture simple of SimpleStateMachine is
	
	signal state, next_state: std_logic;

begin

	process (clk)
	begin
		if rising_edge(clk) then
			if rst = '1' then
				state <= '0';
			else
				state <= next_state;
			end if;
		end if;
	end process;
	
	process (x, state)
	begin
		if state = '0' then
			if x = '1' then
				next_state <= '1';
			else
				next_state <= '0';
			end if;
		else
			if x = '0' then
				next_state <= '0';
			else
				next_state <= '1';
			end if;
		end if;
	end process;
	
	process (state)
	begin
		if state = '0' then
			y <= '1';
		else
			y <= '0';
		end if;
	end process;

end architecture;