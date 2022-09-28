library ieee;
use ieee.numeric_std.all;
use ieee.std_logic_1164.all;

library work;
use work.basic.all;
use work.add.all;

entity uP is
    port(
    reset, clk: in std_logic);
end entity;

architecture ov of uP is
    component control_path is
        port(
            reset, clk: in std_logic; 
            op_code: in std_logic_vector(3 downto 0);
            condition: in std_logic_vector(1 downto 0);
            T: out std_logic_vector(25 downto 0);
            C, Z, invalid_next, eq, B: in std_logic);
    end component;

    component data_path is
        port(
        op_code: out std_logic_vector(3 downto 0);
        condition: out std_logic_vector(1 downto 0);
        clk, reset: in std_logic;
        T: in std_logic_vector(25 downto 0);
        S: out std_logic_vector(4 downto 0));
    end component;
    
   signal op_code: std_logic_vector(3 downto 0);
   signal condition: std_logic_vector(1 downto 0);
   signal T: std_logic_vector(25 downto 0);
   signal C, Z, invalid_next, eq, B: std_logic;
   signal S: std_logic_vector(4 downto 0);

begin

    data: data_path
    port map(op_code => op_code, condition => condition,
        clk => clk, reset => reset, T => T, S => S);
    
    control: control_path
    port map(reset => reset, clk => clk,
        op_code => op_code, condition => condition, 
        T => T, C => C, Z => Z, invalid_next => invalid_next, 
        eq => eq, B => B);
        
   -- Predicate Signal Mapping--
	--
	-- S(0)	: InValid_Next Signal from ls_multiple
	-- S(1)	: Carry
	-- S(2)	: Zero
	-- S(3)	: Bit B
	--	S(4)	: Equality
	--
    
   invalid_next <= S(0);
   C <= S(1);
   Z <= S(2);
   B <= S(3);
   eq <= S(4);
end architecture;