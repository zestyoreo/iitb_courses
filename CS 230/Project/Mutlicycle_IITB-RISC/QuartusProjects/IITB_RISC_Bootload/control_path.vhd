library ieee;
use ieee.numeric_std.all;
use ieee.std_logic_1164.all;

entity control_path is
	port(
		reset, clk, bootload: in std_logic; 
		op_code: in std_logic_vector(3 downto 0);
		condition: in std_logic_vector(1 downto 0);
		T: out std_logic_vector(24 downto 0);
		boot: out std_logic;
		C, OV, Z, invalid_next, eq, B, finish: in std_logic);
end entity;

architecture fsm of control_path is
	type fsm_state is (B0, B1, S0, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14, S15, S16);
	signal Q, nQ: fsm_state := S0;
begin

	clocked:
	process(clk, nQ)
	begin
		if (clk'event and clk = '1') then
			Q <= nQ;
		end if;
	end process;
	
	outputs:
	process(op_code, Q)
	begin
		T <= (others => '0');
		boot <= '0';
		case Q is
			when B0 => boot <= '1';
			when B1 => boot <= '1';
		   when S0 => 
				T <= (others => '0');
			when S1 =>
				T(19 downto 17) <= "001";	--ALU_B = 1
				T(21 downto 20) <= "11"; 	--ALU_A = R7
				T(22) <= '1';					--Send ALU Output to PC
				T(9) <= '1';					--Enable PC Register
				T(1) <= '1';					--Instruction Register Enable
				T(24) <= '1';					--Fetch OpCode from Memory Output
			when S2 =>
				T(0) <= '1';					--A_DM = D2
				T(6) <= '1';
				T(3) <= '1';					--Send Input to the PE
				T(23) <= '0';					--Put D2 in T1
				T(7) <= '1';					--Enable T1
				T(11) <= '0';					--A2 = I(9-11)
			when S3 =>
				T(21 downto 20) <= "10";	--ALU_A = E1
				T(19 downto 17) <= "010";	--ALU_B = E2
				T(23) <= '1';					--Put ALU_S in T1
				T(7) <= '1';					--Enable T1
				T(10) <= '1';					--Set Flags according to the Instruction
			when S4 =>
				T(13 downto 12) <= "11";	--A3 = I(6-8)/I(3-5)
				T(16 downto 14) <= "001";	--D3 = T1
				T(2) <= '1';					--Enable Register Write
			when S5 =>
				T(16 downto 14) <= "000";	--D3 = PC
				T(13 downto 12) <= "00";	--A3 = "111"
				T(2) <= '1';					--Enable Register Write
				T(21 downto 20) <= "00";	--ALU_A = T2
				T(19 downto 17) <= "000";	--ALU_B = 0				
			when S6 =>
				T(16 downto 14) <= "010";	--D3 = LS
				T(13 downto 12) <= "01";	--A3 = I(9-11)
				T(2) <= '1';					--Enable Register Write
			when S7 =>
				T(21 downto 20) <= "10";	--ALU_A = E1
				T(19 downto 17) <= "011";	--ALU_B = SE(6-16)
				T(23) <= '1';					--T1 = ALU_S
				T(7) <= '1';					--Enable T1
				T(10) <= '1';					--Set flags according to the instruction
				T(0) <= '1';					--A_DM = ALU_S
				T(5) <= '1';					--Data Memory Write Enable
			when S8 =>
				T(16 downto 14) <= "101";	--D3 = DM_DO
				T(8)  <= '1';					--Enable T2
				T(13 downto 12) <= "01";	--A3 = I(9-11)
				T(2) <= '1';					--Enable Register Write
			when S9 =>
				T(16 downto 14) <= "000";	--D3 = PC
				T(13 downto 12) <= "00";	--A3 = "111"
				T(2) <= '1';					--Enable Register Write
			when S10 =>
				T(8)  <= '1';					--Enable T2		
			when S11 =>
				T(16 downto 14) <= "011";	--D3 = T2
				T(13 downto 12) <= "10";	--A3 = PE
				T(2) <= '1';					--Enable Register Write
				T(21 downto 20) <= "01";	--ALU_A = T1
				T(19 downto 17) <= "001";	--ALU_B = 1
				T(23) <= '1';					--T1 = ALU_S
				T(7) <= '1';					--Enable T1
				T(4) <= '1';					--LS Multiple Set Zero
				T(0) <= '1';					--A_DM = ALU_S
			when S12 =>
				T(11) <= '1';					--A2 = PE
				T(5) <= '1';					--Data Memory Write Enable
				T(6) <= '1';					--A_DM = T1
			when S13 =>
				T(21 downto 20) <= "01";	--ALU_A = T1
				T(19 downto 17) <= "001";	--ALU_B = 1
				T(23) <= '1';					--T1 = ALU_S
				T(7) <= '1';					--Enable T1
				T(4) <= '1';					--LS Multiple Set Zero
			when S14 =>
				T(21 downto 20) <= "11";	--ALU_A = R7
				T(19 downto 17) <= "011";	--ALU_B = SE(6-16)
				T(22) <= '1';					--PC = ALU_S
				T(9) <= '1';					--Enable PC
			when S15 =>
				T(16 downto 14) <= "000";	--D3 = PC
				T(13 downto 12) <= "01";	--A3 = I(9-11)
				T(21 downto 20) <= "11";	--ALU_A = R7
				T(19 downto 17) <= "100";	--ALU_B = SE(9-16)
				T(22) <= '1';					--PC = ALU_S
				T(9) <= '1';					--Enable PC
				T(2) <= '1';					--Enable Register Write
			when S16 =>
				T(22) <= '0';					--PC = D1
				T(13 downto 12) <= "01";	--A3 = I(9-11)
				T(16 downto 14) <= "000";	--D3 = PC
				T(2) <= '1';					--Enable Register Write
				T(9) <= '1';					--Enable PC
			when others =>
				--Do Nothing
		end case;
	end process;
	
	
	next_state:
	process(op_code, condition, C, OV, Z, invalid_next, eq, B, reset, Q, finish, bootload)
	begin
		nQ <= Q;
		case Q is
			when B0 => nQ <= B1;
			when B1 =>
				if (finish = '1') then nQ <= S0;
				end if;
			when S0 => nQ <= S1;
			when S1 =>
				case op_code is
					when "0011" | "1011" => nQ <= S6;	--LHI and LLI
					when "1000" =>	nQ <= S15;
					when "1001" => nQ <= S16;
					when others =>	nQ <= S2;
				end case;
			when S2 =>
				case op_code is
					when "0000" | "0010"=>
						case condition is
							when "00" => nQ <= S3;
							when "10" =>
								if (C = '1') then	nQ <= S3;
								else	nQ <= S5;
							end if;
						when "01" =>
								if (Z = '1') then	nQ <= S3;
								else nQ <= S5;
								end if;
							when "11" =>
								if (OV = '1') then	nQ <= S3;
								else nQ <= S5;
								end if;
							when others =>	nQ <= S5;
						end case;
					when "0001" => nQ <= S7;
					when "0100" =>	nQ <= S7;
					when "0101" =>	nQ <= S7;
					when "0110" => nQ <= S10;
					when "0111" => nQ <= S12;
					when "1100" =>
						if (eq = '1') then nQ <= S14;
						else	nQ <= S5;
						end if;
					when others =>	nQ <= S5;
				end case;
			when S3 =>	nQ <= S4;
			when S4 => 	
				if(B = '0') then nQ <= S5;
				else nQ <= S1;
				end if;
			when S5 =>	nQ <= S1;
			when S6 =>	
				if(B = '0') then nQ <= S5;
				else nQ <= S1;
				end if;
			when S7 =>
				if (op_code(0) = '0') then	nQ <= S8;
				elsif (op_code(2) = '1') then	nQ <= S9;
				else nQ <= S4;
				end if;
			when S8 => nQ <= S5;
			when S9 =>	nQ <= S1;
			when S10 => nQ <= S11;
			when S11 =>
				if (invalid_next = '1') then nQ <= S5;
				else nQ <= S10;
				end if;
			when S12 =>	nQ <= S13;
			when S13 =>
				if (invalid_next = '1') then
					if(B = '0') then nQ <= S5;
					else nQ <= S1;
					end if;
				else nQ <= S12;
				end if;
			when S14 =>	
				nQ <= S5;
			when S15 => 
				if(B = '0') then nQ <= S5;
				else nQ <= S1;
				end if;
			when S16 =>
				if(B = '0') then nQ <= S5;
				else nQ <= S1;
				end if;
			when others =>	nQ <= S5;
		end case;
		if ((reset = '1') and (bootload = '1')) then
			nQ <= B0;
		elsif (reset = '1') then
			nQ <= S0;
		end if;
	end process;
		
end architecture;
