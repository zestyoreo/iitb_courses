#include <iostream>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include "Dictionary.h"
#include <stdlib.h>
#include<time.h>
using namespace std;

char *generate_random_string(){
	
	char *random_string;
	random_string = new char[32];
	int l = rand()%31 + 1;
	for(int i = 0;i<l;i++)
	{
		int j = rand()%2;
		if(j==0)
			{*(random_string+i) = char(rand()%26+97);}
		else
			{*(random_string+i) = char(rand()%26+65);}
	}
	return random_string;
}
int main()
{
	
	int n;
	srand(time(0));
	cout<<"Enter the no of strings to be generated and inputed: ";
	cin>>n;
	Dictionary dict;
	while((n--)!=0)
	{
		Entry e;
		e.key = new char[32];
		e.key = generate_random_string();
		*(e.key+strlen(e.key)) = '\0';
		cout<<"String: "<<e.key<<endl;
		e.frequency = 1;
		dict.put(e);
	}
}