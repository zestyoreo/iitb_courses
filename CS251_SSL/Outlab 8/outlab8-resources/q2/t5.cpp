#include "init.h"

int zero()
{
	return 0;
}

int main(int argc, char* argv[])
{
	if(argc < 2){
		cout << "Usage : " << argv[0] << " <rollno1>-<rollno2>\n";
		return 0;
	}
	init(argv[1], 5);
	string s;
	if(zero())
		s = load_var();
	return 0;
}
