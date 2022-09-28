library ieee;
use ieee.std_logic_1164.all;

entity EightOneMux is
	port(
      i0,i1,i2,i3,i4,i5,i6,i7: in std_logic_vector (7 downto 0); 
      sel: in std_logic_vector (2 downto 0);
      o: out std_logic_vector (7 downto 0)
    );
end entity;

architecture EightOneMux_arc of EightOneMux is
    
    signal o00,o01,o02,o03,o11,o10: std_logic_vector (7 downto 0);

    component mux
		port ( 
			    i0,i1: in std_logic_vector (7 downto 0); 
          s: in std_logic;
          o: out std_logic_vector (7 downto 0)
		);
	end component;

begin
	mux0_1: mux
		port map(i0=>i0,i1=>i1,s=>sel(0),o=>o00);
    mux0_2: mux
		port map(i0=>i2,i1=>i3,s=>sel(0),o=>o01);
    mux0_3: mux
		port map(i0=>i4,i1=>i5,s=>sel(0),o=>o02);
    mux0_4: mux
		port map(i0=>i6,i1=>i7,s=>sel(0),o=>o03);
    
    mux1_1: mux
		port map(i0=>o00,i1=>o01,s=>sel(1),o=>o10);
    mux1_2: mux
		port map(i0=>o02,i1=>o03,s=>sel(1),o=>o11);
    
    mux2_1: mux
		port map(i0=>o10,i1=>o11,s=>sel(2),o=>o);
end architecture;	