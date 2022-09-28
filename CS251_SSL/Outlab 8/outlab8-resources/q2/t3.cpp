#include "init.h"

int main(int argc, char* argv[])
{
	if(argc < 2){
		cout << "Usage : " << argv[0] << " <rollno1>-<rollno2>\n";
		return 0;
	}
	init(argv[1], 3);
	void* ans = new(struct ans);
	load_struct( (struct ans*)ans );
	return 0;
}
