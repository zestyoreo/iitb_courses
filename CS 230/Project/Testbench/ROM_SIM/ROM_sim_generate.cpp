#include<iostream>
#include<fstream>
#include<string>
#include<math.h>
#include<stdio.h>
#include<cstdlib>
using namespace std;

int hex_to_int(string inp)
{
	int num = 0;
	string index = "0123456789ABCDEF";
	for(int i = inp.length()-1; i>=0; i--)
	{
		size_t temp = index.find(inp[i]);
		if(temp == string::npos)
			return -1;
		num = num + int(temp)*pow(16,inp.length()-i-1);
	}
	return num;
}

void exit(ofstream* temp)
{
	temp->close();
	remove("output.temp");
	return;	
}

int main()
{
	string hex_name = "";
	cout<<"Enter the input INTEL HEX file: ";
	cin>>hex_name;
	if(hex_name.find(".hex") == string::npos)
	{
		cout<<"Invalid HEX File.\nCould not find extenstion!";
		return -1;
	}
	
	ifstream hex_file(hex_name.c_str());
	if(!hex_file.is_open())
	{
		cout<<"Cannot find the specified HEX File: "<<hex_name;
		return -1;
	}
	
	int word_length = 2;
	cout<<"Enter the word length in bytes: ";
	cin>>word_length;
	int num_words = 65536;
	cout<<"Enter the number of words in the memory: ";
	cin>>num_words;
	int address_length = (ceil(log2(num_words)))/4;
	ofstream temp("output.temp");
	
	//DEBUG
	cout<<word_length<<" "<<num_words<<" "<<address_length<<endl;
	
	int prev_address = 0;
	int num_line = 1;
	while(!hex_file.eof())
	{
		string line = "";
		hex_file>>line;
		if(line[0] != ':')
			continue;
			
		int words = hex_to_int(line.substr(1,2))/word_length;
		int address = hex_to_int(line.substr(3,address_length));
		
		int record_type = hex_to_int(line.substr(3+address_length,2));
		if(record_type == 1)
			break; 
		
		if(address<prev_address)
		{
			cout<<"Improper formatting of HEX file detected!\nWrong order of addresses or overlapping data! - Line: "<<num_line<<"\n";
			exit(&temp);
			return -1;
		}
		
		if(record_type != 0)
		{
			cout<<"In Line: "<<num_line<<"\nRecord Type "<<hex_to_int(line.substr(3+address_length,2))<<" not accepted.";
			exit(&temp);
			return -1;
		}
		for(int i = 0; i<words; i++)
		{
			cout<<i<<" "<<word_length<<" "<<address_length<<" "<<line.length()<<endl;
			if(3+(i+1)*2*word_length+address_length- 1 >= line.length()) 
			{
				cout<<"Improper formatting of HEX file detected!\nNumber of words not matching! - Line: "<<num_line<<"\n";
				exit(&temp);
				return -1;
			}
			temp<<address<<"\n"<<hex_to_int(line.substr(5+i*2*word_length+address_length, 2*word_length))<<endl;
			address++;
		}
		prev_address = address;
		num_line++;
	}
	
	cout<<"Retrieved Data. Creating ROM VHDL file!\n";
	ofstream vhd("ROM_sim.vhd");
	temp.close();
	ifstream temp_in("output.temp");
	vhd<<"library ieee;\n"
"use ieee.std_logic_1164.all;\n"
"use ieee.numeric_std.all;\n"
"\n"
"entity ROM_SIM is\n"
"	generic(num_words: integer := "<<num_words<<";\n"
"		word_length: integer := "<<word_length*8<<");\n"
"	port(\n"
"		address: in std_logic_vector("<<address_length*4-1<<" downto 0);\n"
"		data_out: out std_logic_vector(word_length-1 downto 0);\n"
"		rd_ena ,clk : in std_logic);\n"
"end entity;\n"
"\n"
"architecture behave of ROM_SIM is\n"
"	type int_array is array (0 to num_words-1) of integer;\n"
"	signal memory: int_array := (others => 0);\n"
"begin\n"
"\n"
"	process(rd_ena, address)\n"
"	begin\n"
"		data_out <= (others => 'Z');\n"
"		if(rd_ena = '1') then\n"
"			data_out <= std_logic_vector(to_unsigned(memory(to_integer(unsigned(address))),word_length));\n"
"		end if;\n"
"	end process;\n\n";
	num_line = 0;
	while(!temp_in.eof())
	{
		string line = "";
		temp_in>>line;
		if(line != "")
			vhd<<"\tmemory("<<line<<") <= ";
		temp_in>>line;
		if(line != "")
			vhd<<line<<";";
		if(num_line%4 == 0)
			vhd<<endl;
		num_line++;
	}	
	
	vhd<<"\nend architecture;";
	temp_in.close();
	vhd.close();
	remove("output.temp");
	char pause[256];
	cout<<"Press any key to exit...";
	cin.get(pause,256);
	cout<<pause;
}
