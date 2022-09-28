library ieee;
use ieee.std_logic_1164.all;

entity EightbyThreeEncode is
    port ( 
        i : in std_logic_vector(7 downto 0); 
        en: in std_logic;
        z : out std_logic_vector(2 downto 0)
    );
end entity;

architecture EightbyThreeEncode_arc of EightbyThreeEncode is
	
	component four_and_adder
		port (i0,i1,i2,i3,e: in std_logic; o: out std_logic);
	end component;
	
begin
	And1: four_and_adder
		port map (i0=>i(4),i1=>i(5),i2=>i(6),i3=>i(7),e=>en,o=>z(2));
	And2: four_and_adder
		port map (i0=>i(2),i1=>i(3),i2=>i(6),i3=>i(7),e=>en,o=>z(1));
	And3: four_and_adder
		port map (i0=>i(1),i1=>i(3),i2=>i(5),i3=>i(7),e=>en,o=>z(0));
		
end architecture;	