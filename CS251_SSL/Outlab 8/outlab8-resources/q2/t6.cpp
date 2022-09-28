#include "init.h"
#include <time.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	if(argc < 2){
		cout << "Usage : " << argv[0] << " <rollno1>-<rollno2>\n";
		return 0;
	}
	init(argv[1], 6);
	
	int sum = 0;
	for(int i=0; i<1000000; i++){
		sum += i;
	}
	

	srand(time(NULL));
	int r = rand()%1000000;
	for(int j=0; j<1000000; j++){
		if(j == r){
			string s = load_var();
		}
	}
	return 0;
}
