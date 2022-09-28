library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity TrafficLightsController is
	port(clk, rst, tr1, tr4 : in std_logic;
	r, g, y: out std_logic_vector (4 downto 0));
end entity;

architecture TrafficLightsController_arch of TrafficLightsController is

	signal state: integer := 4;		
	signal time_on: integer := 0;

begin

process(clk)
begin
	if(rising_edge(clk)) then
		if(rst = '1') then
			state <= 4;
			time_on <= 0;

		else
			if(state <= 0) then
				if(time_on = 60) then
					state <= 1;
					time_on <= 1;
				else
					time_on <= time_on + 1;
				end if;

			elsif(state <= 1) then
				if(time_on = 5) then
					if(tr1 = '1') then
						state <= 2;
					else
						state <= 4;
					end if;
					time_on <= 1;
				else
					time_on <= time_on + 1;
				end if;

			elsif(state <= 2) then
				if(time_on = 30) then
					state <= 3;
					time_on <= 1;
				else
					time_on <= time_on + 1;
				end if;

			elsif(state <= 3) then
				if(time_on = 5) then
					state <= 4;
					time_on <= 1;
				else
					time_on <= time_on + 1;
				end if;

			elsif(state <= 4) then
				if(time_on = 60) then
					state <= 5;
					time_on <= 1;
				else
					time_on <= time_on + 1;
				end if;

			elsif(state <= 5) then
				if(time_on = 5) then
					state <= 6;
					time_on <= 1;
				else
					time_on <= time_on + 1;
				end if;

			elsif(state <= 6) then
				if(time_on = 60) then
					state <= 7;
					time_on <= 1;
				else
					time_on <= time_on + 1;
				end if;

			elsif(state <= 7) then
				if(time_on = 5) then
					if(tr4 = '1') then
						state <= 8;
					else
						state <= 0;
					end if;
					time_on <= 1;
				else
					time_on <= time_on + 1;
				end if;

			elsif(state <= 8) then
				if(time_on = 30) then
					state <= 9;
					time_on <= 1;
				else
					time_on <= time_on + 1;
				end if;

			elsif(state <= 9) then
				if(time_on = 5) then
					state <= 0;
					time_on <= 1;
				else
					time_on <= time_on + 1;
				end if;
			end if;
		end if;
	end if;
end process;
	
process(rst, state)
begin
	if(rst = '1') then				--momentary all red state
		r <= "11111";
		g <= "00000";
		y <= "00000";
	else
		if(state = 0) then 			--L0 green
			r <= "01111";
			g <= "10000";
			y <= "00000";
		elsif(state = 1) then		--L0 yellow
			r <= "01111";
			g <= "00000";
			y <= "10000";
		elsif(state = 2) then		--L1 green
			r <= "10111";
			g <= "01000";
			y <= "00000";
		elsif(state = 3) then		--L1 yellow`
			r <= "10111";
			g <= "00000";
			y <= "01000";
		elsif(state = 4) then		--L2 green
			r <= "11011";
			g <= "00100";
			y <= "00000";
		elsif(state = 5) then		--L2 yellow
			r <= "11011";
			g <= "00000";
			y <= "00100";
		elsif(state = 6) then		--L3 green
			r <= "11101";
			g <= "00010";
			y <= "00000";
		elsif(state = 7) then		--L3 yellow
			r <= "11101";
			g <= "00000";
			y <= "00010";
		elsif(state = 8) then		--L4 green
			r <= "11110";
			g <= "00001";
			y <= "00000";
		elsif(state = 9) then		--L4 yellow
			r <= "11110";
			g <= "00000";
			y <= "00001";
		else						--momentary all red state
			r <= "11111";
			g <= "00000";
			y <= "00000";
		end if;
	end if;
end process;

end architecture;