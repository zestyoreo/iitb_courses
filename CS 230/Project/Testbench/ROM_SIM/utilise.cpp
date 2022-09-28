#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
using namespace std;

int main()
{
	string inp;
	cout<<"Input file name: ";
	cin>>inp;
	
	string temp = "";
	temp += "python3 assembler.py ";
	temp += inp;
	temp += " temp.hex";
	
	system(temp.c_str());
	remove("kalpesh.hex");

	ofstream ofile("temp2");
	ofile<<"temp.hex\n2\n65536";
	system("g++ ROM_sim_generate.cpp");
	ofile.close();
	
	system("./a.out<temp2");
	
	remove("a.out");
	remove("temp.hex");
	remove("temp2");	
}
