--alu
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity alu is
	generic(bit_count: integer := 16);
	port(
		input1, input2: in std_logic_vector(bit_count-1 downto 0);
		output: out std_logic_vector(bit_count-1 downto 0);
		cin, sel: in std_logic;
		CY, Z: out std_logic); --
end entity;

architecture alu_arc of alu is
	signal output_temp: std_logic_vector(bit_count-1 downto 0);
	signal output_add: std_logic_vector(bit_count-1 downto 0);
	signal C: std_logic_vector(bit_count downto 1);

    component adder
        generic(
            bit_count: integer := 16;
            group_width: integer := 4);
        port(
            A, B: in std_logic_vector(bit_count-1 downto 0);
            S: out std_logic_vector(bit_count-1 downto 0);
            cin: in std_logic;
            Cout: out std_logic_vector(bit_count-1 downto 0));
    end component;

begin
	
	adder: adder
		generic map(bit_count,4)
		port map(
			A => input1, B => input2,
			cin => cin, S => output_add, Cout => C);
			
	CY <= C(bit_count);
	
	process(input1,input2,sel,output_add)
	begin
		if (sel = '0') then
			output_temp <= output_add;
		else
			output_temp <= input1 nand input2;
		end if;
	end process;
	
	Z <= '1' when (to_integer(unsigned(output_temp)) = 0) else '0';
	output <= output_temp;

		
end architecture;