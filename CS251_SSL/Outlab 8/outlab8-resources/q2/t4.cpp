#include "init.h"

int main(int argc, char* argv[])
{
	if(argc < 2){
		cout << "Usage : " << argv[0] << " <rollno1>-<rollno2>\n";
		return 0;
	}
	init(argv[1], 4);
	int go_on = 0;
	string s;
	if(go_on)
		s = load_var();
	return 0;
}
