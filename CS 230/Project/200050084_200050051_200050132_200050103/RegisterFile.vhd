library ieee;
use ieee.std_logic_1164.all ;

entity Oneb8demux is
port(
	mux_inp : in std_logic_vector(2 downto 0) ;
	mux_out : out integer
);
end entity ;

architecture DEMUX_ARCH of Oneb8demux is

begin
	process(mux_inp)
	begin
		if(mux_inp = "000") then
			mux_out <= 0 ;
		elsif(mux_inp = "001") then
			mux_out <= 1 ;
		elsif(mux_inp = "010") then
			mux_out <= 2 ;
		elsif(mux_inp = "011") then
			mux_out <= 3 ;
		elsif(mux_inp = "100") then
			mux_out <= 4 ;
		elsif(mux_inp = "101") then
			mux_out <= 5 ;
		elsif(mux_inp = "110") then
			mux_out <= 6 ;
		elsif(mux_inp = "111") then
			mux_out <= 7 ;
		end if;
	end process;
	
end DEMUX_ARCH ;
----------------------------------------------
library ieee;
use ieee.std_logic_1164.all ;

entity RegisterFile is
port(
	read_regA,read_regB,write_regC : in std_logic_vector(2 downto 0) ;
	write_data : in std_logic_vector(15 downto 0) ;
	regWriteControl : in std_logic_vector ;
	data_regA,data_regB : out std_logic_vector(15 downto 0)	
);
end entity;

architecture RF_ARCH of RegisterFile is

	type my_reg_type is array(0 to 7) of std_logic_vector(15 downto 0);
	signal registers : my_reg_type ;
	
	component Oneb8demux is
	port(
		mux_inp : in std_logic_vector(2 downto 0) ;
		mux_out : out integer 
	);
	end component ;
	
--	component 8b1mux is
--	port(
--		demux_inp : in integer ;
--		demux_out : out std_logic_vector(2 downto 0) ;
--	);
--	end component ;
	
	signal int1,int2,int3 : integer ;
	--signal tmp : std_logic_vector;
	
begin

	mux1 : Oneb8demux port map(read_regA,int1) ;
	mux2 : Oneb8demux port map(read_regB,int2) ;
	mux3 : Oneb8demux port map(write_regC,int3) ;
	--tmp <= regWriteControl ;
	data_regA <= registers(int1) ;
	data_regB <= registers(int2) ;
	
	process(int1,int2,int3,registers,regWriteControl)
	begin
		
		if regWriteControl = "1" then --error why ?
			registers(int3) <= write_data ;
		end if;
	end process ;
	
	
end RF_ARCH ;