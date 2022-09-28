library ieee;
use ieee.numeric_std.all;
use ieee.std_logic_1164.all;
use ieee.math_real.all;

library work;
use work.basic.all;
use work.add.all;

entity data_path is
	port(
	op_code: out std_logic_vector(3 downto 0);
	condition: out std_logic_vector(1 downto 0);
	clk, reset, RX, start: in std_logic;
	finish: out std_logic;
	T: in std_logic_vector(24 downto 0);
	S: out std_logic_vector(5 downto 0);
	P0: out std_logic_vector(15 downto 0));
end entity;
	
architecture rtl of data_path is

	component sign_extend is
		generic(input_width: integer := 6;
			output_width: integer := 16);
		port(
			input: in std_logic_vector(input_width-1 downto 0);
			output: out std_logic_vector(output_width-1 downto 0));
	end component;

	component register_file is
		generic(
			word_length: integer := 16;
			num_words: integer := 8);
			
		port(
			data_in: in std_logic_vector(word_length-1 downto 0);
			data_out1, data_out2, R7, R0: out std_logic_vector(word_length-1 downto 0);
			sel_in, sel_out1, sel_out2: in std_logic_vector(integer(ceil(log2(real(num_words))))-1 downto 0);
			clk, wr_ena, reset: in std_logic);
			
	end component;

	component ls_multiple is
		generic(input_width: integer := 8);
		port(
			input: in std_logic_vector(input_width-1 downto 0);
			ena, clk, set_zero, reset: in std_logic;
			valid, invalid_next: out std_logic;
			address: out std_logic_vector(integer(ceil(log2(real(input_width))))-1 downto 0));
	end component;

	component alu is
		generic(word_length: integer := 16);
		port(
			input1, input2: in std_logic_vector(word_length-1 downto 0);
			output: out std_logic_vector(word_length-1 downto 0);
			cin, sel: in std_logic;
			CY, OV, Z: out std_logic);
	end component;
			
	component ram
		PORT
		(
			aclr		: IN STD_LOGIC  := '0';
			address	: IN STD_LOGIC_VECTOR (14 DOWNTO 0);
			clock		: IN STD_LOGIC  := '1';
			data		: IN STD_LOGIC_VECTOR (15 DOWNTO 0);
			wren		: IN STD_LOGIC ;
			q			: OUT STD_LOGIC_VECTOR (15 DOWNTO 0)
		);
	end component;
	
	component bootload is 
		port(
			start, clk, reset, RX: in std_logic;
			address: out std_logic_vector(15 downto 0);
			data: out std_logic_vector(15 downto 0);
			enable, finish: out std_logic);
	end component;
	
	signal I, D1, D2, D3, SEs, SEl, LS, ALU_A, ALU_B, ALU_S, T1, T2: std_logic_vector(15 downto 0) := (others => '0');
	signal A_IM, A_DM, DO_IM, DO_DM, DI_DM, T1_IN, E1, E2, PC, PC_IN, R7, R0, d_boot, a_boot: std_logic_vector(15 downto 0) := (others => '0');
	signal A1, A2, A3, A3_int, PE: std_logic_vector(2 downto 0) := (others => '0');
	signal CY, OV, Z, B_IN, B: std_logic_vector(0 downto 0) := (others => '0');
	signal carry_ena, zero_ena, alu_op, b_ena, temp, wren, pc_ena, ena_boot: std_logic;

begin

	--Bootloader
	bootload_instance: bootload
	port map(
		start => start, clk => clk, reset => reset, RX => RX, 
		data => d_boot, address => a_boot, enable => ena_boot, finish => finish);
	
	-- Transfer Signal Mapping--
	--
	-- T(0)		: Data Memory Address
	--		0 	- D2
	--		1 	- ALU_S
	--
	-- T(1)		: Instruction Register Enable
	-- T(2)		: Register File Write Enable
	-- T(3)		: LS_Multiple Write Enable
	-- T(4)		: LS_Multiple Set-Zero
	-- T(5)		: Data Memory Write Enable
	-- T(7)		: T1 Register Enable
	-- T(8)		: T2 Register Enable
	-- T(9)		: PC Register Enable
	-- T(10)	: Flags Set
	-- T(11)	: A2 Input Select
	--		0 	- I(11-9)
	--		1	- PE
	--
	-- T(13:12)	: A3 Input Select
	--		00 - "111"
	--		01 - I(11-9)
	--		10 - PE
	--		11 - I(5-3)
	--
	-- T(16:14)	: D3 Input Select
	--		000 - PC
	--		001 - T1
	--		010 - LS
	--		011 - T2
	--		100 - R7
	--		101 - Data Memory Data Out
	--
	-- T(19:17)	: ALU_B Input Select
	--		000 - 0
	--		001 - 1
	--		010 - E2
	--		011 - SE(6-16)
	--		100 - SE(9-16)
	--
	-- T(21:20)	: ALU_A Input Select
	--		00	- T2
	--		01	- T1
	--		10	- E1
	--		11	- R7
	--
	-- T(22)	: PC_IN Multiplexor Signal
	--		1 - ALU Output
	--		0 - D1
	--
	-- T(23)	: T1 Input Select
	--		1 - ALU Output
	--		0 - D2
	--
	-- T(24)	: Op_Code Forwarding
	--		1 - Forwarded
	--		0 - From IR
	
	-- Predicate Signal Mapping--
	--
	-- S(0)	: InValid_Next Signal from ls_multiple
	-- S(1)	: Carry
	-- S(2)	: Zero
	-- S(3)	: Bit B
	-- S(4)	: Equality
	--
	
	--Instruction Memory
	--ins_mem: rom
	--	port map(q => DO_IM, address => A_IM, clock => clk, aclr => reset);
	
	--Instruction Register
	instruction_register: my_reg
		generic map(16)
		port map(clk => clk, clr => reset, Din => DO_IM, Dout => I, ena => T(1));
	
	--Register File
	rf: register_file
		port map(clk => clk, reset => reset, wr_ena => T(2), data_in => D3, R7 => R7, R0 => R0,
			data_out1 => D1, data_out2 => D2, sel_in => A3, sel_out1 => A1, sel_out2 => A2);
	
	--Priority Encoder Block
	pe_block: ls_multiple
		port map( input => I(7 downto 0), ena => T(3), clk => clk, set_zero => T(4),
			reset => reset, invalid_next => S(0), address => PE);
			
	--Sign Extend 6 to 16
	sign_extend_1: sign_extend
		generic map(6,16)
		port map(input => I(5 downto 0), output => SEl);
		
	--Sign Extend 9 to 16
	sign_extend_2: sign_extend
		generic map(9,16)
		port map(input => I(8 downto 0), output => SEs);
		
	--Arithmetic Logic Unit
	alu_instance: alu
		port map(input1 => ALU_A, input2 => ALU_B, output => ALU_S, cin => '0',
			sel => alu_op, CY => CY(0), Z => Z(0), OV => OV(0));
			
	--Memory
	mem: ram
		port map(q => DO_DM, data => DI_DM, address => A_DM(14 downto 0), wren => wren,
			aclr => reset, clock => clk);
		
	--Temporary Register 1
	T1_Reg: my_reg
		generic map(16)
		port map(Din => T1_IN, Dout => T1, ena => T(7), clk => clk, clr => reset);
		
	--Temporary Register 2
	T2_reg: my_reg
		generic map(16)
		port map(Din => DO_DM, Dout => T2, ena => T(8), clr => reset, clk => clk);
		
	--Condtion Code Register: Carry
	Carry_CCR: my_reg
		generic map(1)
		port map(Din => CY, Dout => S(1 downto 1), ena => carry_ena, clr => reset, clk => clk);
		
	--Condition Code Register: Zero	
	Zero_CCR: my_reg
		generic map(1)
		port map(Din => Z, Dout => S(2 downto 2), ena => zero_ena, clr => reset, clk => clk);
		
	--Condition Code Register: Overflow
	Overflow_CCR: my_reg
		generic map(1)
		port map(Din => OV, Dout => S(5 downto 5), ena => carry_ena, clr => reset, clk => clk);
		
	--Temporary Register E1
	E1_reg: my_reg
		generic map(16)
		port map(Din => D1, Dout => E1, ena => '1', clr => reset, clk => clk);
		
	--Temporary Register E2
	E2_reg: my_reg
		generic map(16)
		port map(Din => D2, Dout => E2, ena => '1', clr => reset, clk => clk);
		
	--Register PC
	PC_reg: my_reg
		generic map(16)
		port map(Din => PC_IN, Dout => PC, ena => pc_ena, clr => reset, clk => clk);
		
	--B Signal Flop - R7 Write
	B_flop: my_reg
		generic map(1)
		port map(Din => B_IN, Dout => B, ena => b_ena, clr => reset, clk => clk);
		
		
	--PC Enable
	pc_ena <= temp or T(9);
	--Carry Enable
	carry_ena <= '1' when ((I(15 downto 13) = "000") and (T(10) = '1')) else '0';
	--Zero Enable
	zero_ena <= '1' when (((I(15 downto 14) = "00") and ((I(13) and I(12)) = '0') and (T(10) = '1')) or I(15 downto 12) = "0100") else '0';
	--ALU Operation 
	alu_op <= '1' when (I(15 downto 12) = "0010") else '0';
	--Temporary Signal
	temp <= (A3(2) and A3(1) and A3(0) and T(2));
	--B Register Enable
	b_ena <= T(9) or temp;
	--B Signal
	S(3) <= B(0) or temp;
	
	wren <= ena_boot when (start = '1') else
		T(5) when ((I(12) and I(14)) = '1') else '0';
	
	--Left Shifter Input
	--LS <= SEs(8 downto 0) & "0000000";
	--Added an extra multiplexor to accomodate Lli
	LS <= I(8 downto 0) & "0000000" when (I(15) = '0') else
		"0000000" & I(8 downto 0);
	
	--Equality Check
	S(4) <= '1' when (D1 = D2) else '0';
	
	--Address In 1 of Register File
	A1 <= I(8 downto 6);
		
	--Address In 2 of Register File
	A2 <= PE when (T(11) = '1') else
		I(11 downto 9);
	
	--Address In 3 of Register File
	A3_int <= "111" when (T(13 downto 12) = "00") else
		I(11 downto 9) when (T(13 downto 12) = "01") else
		PE when (T(13 downto 12) = "10") else
		I(5 downto 3);
	
	--Data In of Register File
	D3 <= PC when (T(16 downto 14) = "000") else
		T1 when (T(16 downto 14) = "001") else
		LS when (T(16 downto 14) = "010") else
		T2 when (T(16 downto 14) = "011") else
		R7 when (T(16 downto 14) = "100") else
		DO_DM;

	--Workaround to accomodate ADI write to REGB	
	A3 <= I(8 downto 6) when ((I(15 downto 12) = "0001") and (T(13 downto 12) = "11")) else A3_int;

	--Input 2 of ALU
	ALU_B <= (others => '0') when (T(19 downto 17) = "000") else
		std_logic_vector(to_unsigned(1,16)) when (T(19 downto 17) = "001") else
		E2 when (T(19 downto 17) = "010") else
		SEl when (T(19 downto 17) = "011") else
		SEs;
	
	--Input 1 of ALU
	ALU_A <= T2 when (T(21 downto 20)= "00") else
		T1 when (T(21 downto 20) = "01") else
		E1 when (T(21 downto 20) = "10") else
		R7;
    
	--Input of Temporary Register 1
	T1_IN <= ALU_S when (T(23) = '1') else
		D2;
		
	PC_IN <= D3 when (temp = '1') else
		ALU_S when (T(22) = '1') else
		D1;
		
	B_IN <= "1" when (temp = '1') else "0";
	
	A_IM <= R7 when (B = "1") else 
		D3;
	
	A_DM <= a_boot when (start = '1') else
		ALU_S when (T(0) = '1' and T(6) = '0') else
		T1 when (T(0) = '0' and T(6) = '1') else
		D2 when (T(0) = '1' and T(6) = '1') else
		A_IM;
	
	DI_DM <= d_boot when (start = '1') else
		D2;
		
	--Send Operation Code to the control path
	op_code <= I(15 downto 12) when (T(24) = '0') else
		DO_IM(15 downto 12);
	--Send the Conditional Execution Data to control path
	condition <= I(1 downto 0);
	DO_IM <= DO_DM;
	P0 <= R0;
	
end architecture;
