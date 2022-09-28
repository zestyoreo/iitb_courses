--adder.vhd
library ieee;
use ieee.std_logic_1164.all;
use ieee.math_real.all;
use ieee.numeric_std.all;

entity adder is
	generic(
		bit_count: integer := 16;
		group_width: integer := 4);	--This better be a factor of bit_count
	port(
		A, B: in std_logic_vector(bit_count-1 downto 0);
		S: out std_logic_vector(bit_count-1 downto 0);
		cin: in std_logic;
		Cout: out std_logic_vector(bit_count-1 downto 0));
end entity;

architecture look_ahead of adder is
	signal C: std_logic_vector(bit_count downto 0);
	signal P, G: std_logic_vector(bit_count-1 downto 0);

    component full_adder
        port(
            a, b, cin: in std_logic;
            s, p, g: out std_logic);
    end component;

    component carry_generator
        generic(group_width: integer := 4);
        port(
            P, G: in std_logic_vector(group_width-1 downto 0);  --propagator and generator
            cin: in std_logic;
            cout: out std_logic_vector(group_width-1 downto 0));
    end component;

begin

	C(0) <= cin;
	
	adder_element:
	for i in 0 to bit_count-1 generate
		ADDX: full_adder
			port map(a => A(i), b => B(i), cin => C(i),
				s => S(i), p => P(i), g => G(i));
	end generate;
	
	carry_element:
	for i in 0 to (bit_count/group_width)-1 generate
		CARRYX: carry_generate
			generic map(group_width)
			port map(P => P((i+1)*group_width-1 downto i*group_width),
				G => G((i+1)*group_width-1 downto i*group_width),
				cin => C(i*group_width), cout => C((i+1)*group_width downto i*group_width+1));
	end generate;
	
	Cout <= C(bit_count downto 1);
	
end architecture;

