library ieee;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity uart_receive is 
	port(
		data: out std_logic_vector(7 downto 0); 
		received: out std_logic;
		clock, reset: in std_logic;
		RX: in std_logic);
end entity;

architecture receive of uart_receive is
	component control_path_receive is
		port(
			received: out std_logic;
			clk, reset: in std_logic;
			T: out std_logic_vector(3 downto 0);
			S: in std_logic_vector(3 downto 0));
	end component;
	
	component data_path_receive is
		port(
			clk, reset: in std_logic;
			data: out std_logic_vector(7 downto 0);
			T: in std_logic_vector(3 downto 0);
			S: out std_logic_vector(3 downto 0);
			RX: in std_logic_vector(0 downto 0));
	end component;

	signal T: std_logic_vector(3 downto 0);
	signal S: std_logic_vector(3 downto 0);
	signal send, clk, receive1, receive2: std_logic := '1';
begin

	clk_divide: process(clock)
		variable count: unsigned(8 downto 0) := "101000101";
	begin
		if clock = '1' then
			if count = "000000000" then
				if clk = '1' then
					count := "101000101";
				else
					count := "101000110";
				end if;
				clk <= not clk;
			else
				count := count - 1;
			end if;
		end if;
	end process;
	
	process(clock, receive1)
	begin
		if(clock'event and clock = '1') then
			receive2 <= receive1;
		end if;
	end process;
	received <= ((not receive2) and receive1);
	
	d: data_path_receive
		port map(
			clk => clk, data => data,
			T => T, S => S,
			RX(0) => RX, reset => reset);
			
	c: control_path_receive
		port map(
			clk => clk, received => receive1,
			T => T, S => S, reset => reset);
			
	
end architecture;
			
			
library ieee;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity control_path_receive is
	port(
		received: out std_logic;
		clk, reset: in std_logic;
		T: out std_logic_vector(3 downto 0);
		S: in std_logic_vector(3 downto 0));
end entity;

architecture control of control_path_receive is
	type state is (ready, receive_chk, receive, valid_chk);
	signal Q,  nQ: state := ready;
begin
	
	delay: process(clk)
	begin
		if clk = '1' then
			Q <= nQ;
		end if;
	end process;
	
	main: process(Q, S)
	begin
		
		nQ <= Q;
		T <= (others => '0');
		received <= '0';
		if (reset = '1') then
			nQ <= ready;
		else
			case Q is
				when ready =>
					if S(0) = '1' then
						nQ <= receive_chk;
						T(0) <= '1';
					end if;
		
				when receive_chk =>
					if S(0) = '0' then
						nQ <= ready;
					elsif S(1) = '0' then
						T(1) <= '1';
					else
						nQ <= receive;
						T(2) <= '1';
					end if;
					
				when receive =>
					if S(1) = '1' then
						nQ <= valid_chk;
					elsif S(2) = '0' then
						T(3) <= '1';
					else
						T(1) <= '1';
					end if;
					
				when valid_chk =>
					if S(3) = '1' then
						received <= '1';
					end if;
					nQ <= ready;
			end case;	
		end if;
	end process;
	
end architecture;
  
library ieee;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

library work;
use work.basic.all;

entity data_path_receive is
	port(
		clk, reset: in std_logic;
		data: out std_logic_vector(7 downto 0);
		T: in std_logic_vector(3 downto 0);
		S: out std_logic_vector(3 downto 0);
		RX: in std_logic_vector(0 downto 0));
end entity;

architecture data of data_path_receive is	
	signal rx_in: std_logic_vector(0 downto 0);
	signal data_ena, cnt1_ena, cnt2_ena: std_logic;
	signal data_in, data_out: std_logic_vector(9 downto 0);
	signal cnt1_in, cnt1_out: std_logic_vector(3 downto 0);
	signal cnt2_in, cnt2_out: std_logic_vector(2 downto 0);
begin
	
	rx_reg: my_reg
		generic map(1)
		port map(clk => clk, ena => '1', Din => RX, Dout => rx_in, clr => reset);
	
	S(0) <= not rx_in(0);
	
	data_ena <= T(1) or T(2);
	data_in <= "0000000000" when T(2) = '1'
		else rx_in(0) & data_out(9 downto 1);
	data_reg: my_reg
		generic map(10)
		port map(clk => clk, ena => data_ena, Din => data_in, Dout => data_out, clr => reset);
		
	S(3) <= data_out(9) and data_out(8);
	
	cnt1_ena <= T(0) or T(1) or T(2);
	cnt1_in <= std_logic_vector(unsigned(cnt1_out) - 1) when T(1) = '1'
		else "0011" when T(0) = '1' 
		else "1010";
	cnt1_reg: my_reg
		generic map(4)
		port map( clk => clk, ena => cnt1_ena, Din => cnt1_in, Dout => cnt1_out, clr => reset);
	
	S(1) <= '1' when cnt1_out = "0000"
		else '0';
		 
	cnt2_ena <= T(1) or T(2) or T(3);
	cnt2_in <= std_logic_vector(unsigned(cnt2_out) - 1) when T(3) = '1'
		else "111";
	cnt2_reg: my_reg
		generic map(3)
		port map(clk => clk, ena => cnt2_ena, Din => cnt2_in, Dout => cnt2_out, clr => reset);
		
	S(2) <= '1' when cnt2_out = "000"
		else '0';
		
	data <= data_out(7 downto 0);
end architecture;
	
