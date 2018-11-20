#include <string>
#include "Matrix.h"

//Matrix module. Containing all necessary methods to perform operations with matrix

//Returns matrix that is a product of this and matrix2 matrices for lines from i1 to i2
void Matrix::multiply(int* matrix, int* matrix2, int* product, int i1, int i2, int n) {
	for (int i = i1; i < i2; i++)
		for (int j = 0; j < n; j++) {
			product[i*n + j] = 0;
			for (int k = 0; k < n; k++)
				product[i*n + j] += matrix[i*n + k] * matrix2[k*n + j];
		}
}

//Returns string representation of a matrix
std::string Matrix::toString(int* matrix, int n, int m) {
	std::string str = "";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			str += std::to_string(matrix[i*n + j]) + " ";
		}
		str += "\n";
	}
	return str;
}

//Fills matrix with number k
void Matrix::fill(int* matrix, int k, int n) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrix[i*n + j] = k;
}

//Returns deep copy of a matrix
int* Matrix::getCopy(int* matrix, int n) {
	int* cpMatrix = new int[n];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cpMatrix[i*n + j] = matrix[i*n + j];

	return cpMatrix;
}
