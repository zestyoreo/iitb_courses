library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity BoothMultiplier is
	port ( 
		clk, rst : in std_logic;
		a, b : in std_logic_vector (3 downto 0);
		result : out std_logic_vector (7 downto 0) 
	);
end entity;

architecture BoothMultiplier_arc of BoothMultiplier is

	signal state, next_state: std_logic;
	signal p1, p2, sum: std_logic_vector(7 downto 0);

begin
	process(clk)
	begin
		if rising_edge(clk) then
			if(rst = '1') then
				next_state <= '0';
				sum <= "00000000";
			else
				if(state = '0') then
					next_state <= '1';
					
					if(b(1 downto 0) = "00") then
						p1 <= "00000000";
					elsif(b(1 downto 0) = "01") then
						p1 <= "0000" & a;
					elsif(b(1 downto 0) = "10") then
						p1 <= "000" & a & "0";
					elsif(b(1 downto 0) = "11") then
						p1 <= ("00"&a&"00") + Not("0000"&a) + "00000001";
					end if;
					
					if(b(3 downto 2) = "00") then
						p2 <= "00000000";
					elsif(b(3 downto 2) = "01") then
						p2 <= "00" & a & "00";
					elsif(b(3 downto 2) = "10") then
						p2 <= "0" & a & "000";
					elsif(b(3 downto 2) = "11") then
						p2 <= (a&"0000") + Not("00"&a&"11") + "00000100";
					end if;
					
				elsif(state = '1') then
					next_state <= '0';
					
					sum <= p1 + p2;
				end if;
			end if;
		end if;
	end process;
	
	process(next_state)
	begin
		state <= next_state;
	end process;
	
	process(sum)
	begin
		result <= sum;
	end process;
	
end architecture;