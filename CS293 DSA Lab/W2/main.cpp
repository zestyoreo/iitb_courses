#include <iostream>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include "Dictionary.h"
using namespace std;

int main()
{
	
	int n;
	
	cout<<"Enter the no of strings to input: ";
	cin>>n;
	Dictionary dict;
	while((n--)!=0)
	{
		Entry e;
		e.key = new char[32];
		cout<<"Enter string: ";
		cin>>e.key;
		*(e.key+strlen(e.key)) = '\0';
		e.frequency = 1;
		dict.put(e);
	}
}