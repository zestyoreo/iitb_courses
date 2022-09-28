#include <iostream>
using namespace std;
void func(double *A)
{
	int N = 100;
	double *B = new double[N];
	A = B;
	delete[] B;
	*A = 1;
	cout<<*A<<endl;
	*(A+1) = 2;
	cout<<*(A+1)<<endl;
}
int main(){
	int N = 100;
	double *A ;
	A = new double[N];
	*A = 1;
	cout<<*A<<endl;
	*(A+1) = 2;
	cout<<*(A+1)<<endl;
	delete[] A;
	cout<<*A<<endl;
	func(A);
}