#include <iostream>
#include <vector>
#include <stack>
using namespace std;

typedef vector <double> point;
typedef vector <point> matrix;


/**
 @param A k x k Square matrix in row major form,
 @param B k x k Square matrix in B in row major form
 @return matrix multiplication A. B
*/
matrix matmul(matrix &A, matrix &B){
	int k = A.size();
	matrix product(k, point(k, 0));
	for (int i=1; i<=k; i++){
		for (int l=1; l<=k; l++){
			for(int j=1; j<=k; j++){
				product[i][j]+=A[i][l]*B[l][j];
			}
		}
	}
	return product;
}

/**
 @param A kxk Square matrix in row major form
 @param v kx1 vector, but in column major form
 @return transform A.v
 */
point transform(matrix &A, point &v){
	int k = v.size();
	point answer(k, 0);
	for (int i=0; i<k; i++){
		for (int l=0; l<k; l++){
			answer[i] += A[i][l]*v[l];
		}
	}
	return answer;
}

/**
 @param M k x k square companion matrix
 @param n integer iterate to compute
 @returns M to the nth power
 */
matrix power(matrix &M, unsigned int n){
	stack <int> operations;
	
	int k = M.size();
	//initialise the identity matrix
	matrix working(k, point(k, 1));
	for (int i=0; i<k; i++){
		working[i][i] = 1;
	}
	
	unsigned int quotient = n;
	
	//compute binary of n, from least to most significant
	
	while (quotient != 0){
		operations.push(quotient%2);
		quotient /= 2;
	}
	
	//read binary of n, from most to least significant
	while (!operations.empty()){
		working = matmul(working, working);
		
		int parity = operations.top();
		if (parity = 1){
			working = matmul(working, M);
		}
		
		operations.pop();
	}
	
	return working;
}


/**
 @brief takes n, k from command line, and then waits for a_0, .. a_{k-1}, u_0, ..., u_{k-1} in that order, from stdin
 */
int main(int argc, char* argv[]){
	if (argc != 3){
		cout<<"Usage: ./iterate n(>=0) k(>0)"<<endl;
		return 1;
	}
	int n = atoi(argv[1]);
	int k = atoi(argv[2]);
	
	matrix companion(k, point(k, 0));
	for (int i=0; i<k-1; i++){
		companion[i][i+1] = 1;
	}
	
	for (int i=0; i<k; i++){
		cin>>companion[k-1][i];
	}
	
	point initial(k);
	for (int i=0; i<k; i++){
		cin>>initial[i];
	}
	
	matrix transformer = power(companion, n);
	point n_steps = transform(transformer, initial);
	cout<<n_steps[0]<<endl;
}
