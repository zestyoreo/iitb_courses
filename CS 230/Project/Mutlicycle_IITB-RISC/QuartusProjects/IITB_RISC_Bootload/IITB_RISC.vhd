library ieee;
use ieee.numeric_std.all;
use ieee.std_logic_1164.all;

library work;
use work.basic.all;
use work.add.all;

entity IITB_RISC is
    port(
		reset_bar, clk, RX, bootload_bar: in std_logic;
		P0: out std_logic_vector(15 downto 0));
end entity;

architecture ov of IITB_RISC is
    component control_path is
		port(
			reset, clk, bootload: in std_logic; 
			op_code: in std_logic_vector(3 downto 0);
			condition: in std_logic_vector(1 downto 0);
			T: out std_logic_vector(24 downto 0);
			boot: out std_logic;
			C, OV, Z, invalid_next, eq, B, finish: in std_logic);
    end component;

    component data_path is
       port(
		op_code: out std_logic_vector(3 downto 0);
		condition: out std_logic_vector(1 downto 0);
		clk, reset, RX, start: in std_logic;
		finish: out std_logic;
		T: in std_logic_vector(24 downto 0);
		S: out std_logic_vector(5 downto 0);
		P0: out std_logic_vector(15 downto 0));
    end component;
    
   signal op_code: std_logic_vector(3 downto 0);
   signal condition: std_logic_vector(1 downto 0);
   signal T: std_logic_vector(24 downto 0);
   signal C, OV, Z, invalid_next, eq, B, finish, boot, reset, bootload: std_logic;
   signal S: std_logic_vector(5 downto 0);

begin
	
	reset <= (not reset_bar);
	bootload <= (not bootload_bar);
	
	data: data_path
	port map(op_code => op_code, condition => condition, RX => RX, start => boot,
       clk => clk, reset => reset, T => T, S => S, finish => finish, P0 => P0);
   
	control: control_path
	port map(reset => reset, clk => clk, boot => boot,
		op_code => op_code, condition => condition, finish => finish,
		T => T, C => C, Z => Z, invalid_next => invalid_next, 
		eq => eq, B => B, OV => OV, bootload => bootload);
        
   -- Predicate Signal Mapping--
	--
	-- S(0)	: InValid_Next Signal from ls_multiple
	-- S(1)	: Carry
	-- S(2)	: Zero
	-- S(3)	: Bit B
	-- S(4)	: Equality
	-- S(5)	: Overflow
    
	invalid_next <= S(0);
	C <= S(1);
	Z <= S(2);
	B <= S(3);
	eq <= S(4);
	OV <= S(5);
	
end architecture;