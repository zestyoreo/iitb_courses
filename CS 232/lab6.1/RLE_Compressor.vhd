library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity RLE_Compressor is
	port(clk, rst: in std_logic;
	input: in std_logic_vector(7 downto 0);
	DataValid: out std_logic;
	output: out std_logic_vector(7 downto 0));
end entity;

architecture RLE_Compressor_arc of RLE_Compressor is
	constant ESC : std_logic_vector(7 downto 0) := "00011011";
	constant ZERO : std_logic_vector(7 downto 0) := "00000000";
	constant ONE : std_logic_vector(7 downto 0) := "00000001";

	signal tot_count, read_count, state : integer := 0;
	type in_buffer is array(63 downto 0) of std_logic_vector(7 downto 0);
	signal input_buff : in_buffer;
	signal curr_char, curr_count: std_logic_vector(7 downto 0);
	
begin
	process (clk)
	begin
	if(rising_edge(clk)) then
		if(rst = '1') then
		else
			if(tot_count < 64) then
				input_buff(tot_count) <= input;
				tot_count <= tot_count + 1;
			end if;
		end if;
	end if;
	end process;
	
	process (clk)
	begin
	if(rising_edge(clk)) then
		if (rst = '1') then
			curr_count <= ZERO;
			DataValid <= '0';
			output <= ESC;
			curr_char <= ESC;
		else
			if(state = 0) then
				DataValid <= '0';
				if(read_count + 1 < tot_count ) then 
					curr_char <= input_buff(read_count);
					curr_count <= curr_count + ONE;
					read_count <= read_count + 1;
					if(input_buff(read_count) /= input_buff(read_count + 1)) then
						if(input_buff(read_count) /= ESC) then	
							if(curr_count = ZERO) then
								state <= 1; -- One current output
							elsif(curr_count = ZERO + ONE) then
								state <= 2; -- Two current output
							else
								state <= 3; -- ESC output
							end if;
						else
							state <= 3; -- ESC output
						end if;
					elsif(input_buff(read_count) /= ESC and curr_count = ZERO + "00000100") then
						state <= 3; -- ESC output
					elsif(input_buff(read_count) = ESC and curr_count = ZERO + "00000101") then
						state <= 3; -- ESC output
					end if;
				elsif(read_count = 63 and tot_count = 64) then
					curr_char <= input_buff(read_count);
					curr_count <= curr_count + ONE;
					read_count <= read_count + 1;
					if(input_buff(read_count) /= ESC) then	
						if(curr_count = ZERO) then
							state <= 1; -- One current output
						elsif(curr_count = ZERO + ONE) then
							state <= 2; -- Two current output
						else
							state <= 3; -- ESC output
						end if;
					else
						state <= 3; -- ESC output
					end if;
				end if;
			elsif(state = 1) then
				DataValid <= '1';
				output <= curr_char;
				state <= 0; -- read now
				curr_count <= ZERO;
			elsif(state = 2) then
				DataValid <= '1';
				output <= curr_char;
				state <= 1; -- one char output
			elsif(state = 3) then
				DataValid <= '1';
				output <= ESC;
				state <= 4; -- count output
			elsif(state = 4) then
				DataValid <= '1';
				output <= curr_count;
				state <= 1; -- one char output
			end if;
		end if;
	end if;
	end process;
	
end architecture;