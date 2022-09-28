-- Title				: Priority Encoder 
-- Purpose				:
-- Brief Description	:
-- Author				: Shashank OV
-- Date					: Oct. 8, 2016 

library ieee;
use ieee.numeric_std.all;
use ieee.math_real.all;
use ieee.std_logic_1164.all;

entity p_encoder is
	generic(input_width: integer := 16);
	port(
		input: in std_logic_vector(input_width-1 downto 0);
		output: out std_logic_vector(integer(ceil(log2(real(input_width))))-1 downto 0);
		valid: out std_logic);
end entity;

architecture behave_ov of p_encoder is
	signal output_temp: std_logic_vector(output'length-1 downto 0);
begin

	main: process(input)
	begin
		output_temp <= (others => '0');
		for i in input_width-1 downto 0 loop
			if input(i) = '1' then
				output_temp <= std_logic_vector(to_unsigned(i,output'length));
			end if;
		end loop;
	end process;
	
	output <= output_temp;
	valid <= '0' when (to_integer(unsigned(output_temp)) = 0 and input(0) = '0') else '1';
	
end architecture;


-- architecture behave_brahma of p_encoder is

-- type integer_array is array (0 to output'length-1) of integer range 0 to 255;

-- begin
	
	-- main: process(input)
	
	-- variable output_temp: std_logic_vector(output'length-1 downto 0);
	-- variable flag_var: integer_array;
	-- variable invert_var : std_logic_vector(output'length-1 downto 0);
	-- variable not_var    : std_logic;
	-- variable valid_var  : std_logic;
	-- begin
		-- not_var     := not input(0);
		-- output_temp := (others => '0');
		-- valid_var   := input(0);
		
		-- for i in 0 to output'length - 1 loop
			-- flag_var(i) :=  2**i - 1;
			-- invert_var(i) := '0';
		-- end loop;

		-- for i in 1 to input_width-1 loop
			
			-- for j in 0 to output'length-1 loop
				
				-- if (flag_var(j) = 0) then
						-- invert_var(j) := not invert_var(j);
						-- flag_var(j)   := 2**j;
				-- end if;
				-- if(invert_var(j) = '1') then
						-- output_temp(j) := output_temp(j) or (input(i) and not_var);
				-- end if;
								
				-- flag_var(j) := flag_var(j) - 1;
					
			-- end loop;
			
			-- not_var := not_var and (not input(i));
			-- valid_var := valid_var or input(i);
			
			
		-- end loop;
		-- output <= output_temp;
		-- valid <= valid_var ;
	-- end process;

-- end architecture;

