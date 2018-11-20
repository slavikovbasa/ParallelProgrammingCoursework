#include <string>

//Matrix class. Containing all necessary methods to perform operations with matrix
class Matrix {
public:
	//Returns matrix that is a product of this and matrix2 matrices for lines from i1 to i2
	static void multiply(int* matrix, int* matrix2, int* product, int i1, int i2, int n);

	//Returns string representation of a matrix
	static std::string toString(int* matrix, int n, int m);

	//Fills matrix with number k
	static void fill(int* matrix, int k, int n);

	//Returns deep copy of a matrix
	static int* getCopy(int* matrix, int n);
};