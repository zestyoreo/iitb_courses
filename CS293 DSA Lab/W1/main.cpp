/*
	main.cpp
	Data Structures and Algorithms Lab - CS293
	Author: P Balasubramanian
	Rollno: 200050103
*/	

#include "DynamicDequeue.h"
// link to the DynamicDequeue.h I have used : https://drive.google.com/file/d/1pDQpX1xGP58fPAkD1fK4talVO2QXfjj9/view?usp=sharing
#include <iostream>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>

using namespace std::chrono;
using namespace std;

#define NUM_ITER 100000

int main(){
	DynamicDequeue x;
	ofstream fout;
	//comment one of the two following statements to get time value readings
	//fout.open("linear_time.txt");  //used to store linear_time values when linear growth technique os used
	fout.open("linear_time.txt");  //used to store expo_time values when exponential growth technique os used
	srand(time(0));
	auto start = high_resolution_clock::now();
	for(long int i=0;i<NUM_ITER;i++)
	{
		int choose = rand()%2;
		if(choose==1)
			x.insertFront(rand()%1000);
		else
			x.insertRear(rand()%1000);

		if(i%1000==0)
		{
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			double tim = double(duration.count());
			fout<<i<<","<<tim<<endl;
		}		
	}
	fout.close();
}