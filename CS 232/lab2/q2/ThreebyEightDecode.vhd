library ieee;
use ieee.std_logic_1164.all;

entity ThreebyEightDecode is
    port ( 
        i : in std_logic_vector(2 downto 0); 
        en: in std_logic;
        z : out std_logic_vector(7 downto 0)
    );
end entity;

architecture ThreebyEightDecode_arc of ThreebyEightDecode is

	signal a,b,c,p,q,r: std_logic;
	
	component not_gate
        port (a: in std_logic; o: out std_logic);
	end component;
	component three_and_gate
        port (a,b,c,e: in std_logic; o: out std_logic);
	end component;
	
begin

	a<=i(2);
	b<=i(1);
	c<=i(0);
	
	Not1: not_gate
		port map (a=>a,o=>p);
	Not2: not_gate
		port map (a=>b,o=>q);
	Not3: not_gate
		port map (a=>c,o=>r);

	Out0: three_and_gate
		port map(a=>p,b=>q,c=>r,o=>z(0),e=>en);
	Out1: three_and_gate
		port map(a=>p,b=>q,c=>c,o=>z(1),e=>en);
	Out2: three_and_gate
		port map(a=>p,b=>b,c=>r,o=>z(2),e=>en);
	Out3: three_and_gate
		port map(a=>p,b=>b,c=>c,o=>z(3),e=>en);
	Out4: three_and_gate
		port map(a=>a,b=>q,c=>r,o=>z(4),e=>en);
	Out5: three_and_gate
		port map(a=>a,b=>q,c=>c,o=>z(5),e=>en);
	Out6: three_and_gate
		port map(a=>a,b=>b,c=>r,o=>z(6),e=>en);
	Out7: three_and_gate
		port map(a=>a,b=>b,c=>c,o=>z(7),e=>en);
		
end architecture;	