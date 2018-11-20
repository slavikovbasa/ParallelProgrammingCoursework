#include <string>
#include "Vector.h"

//Vector module. Containing all necessary methods to perform operations with vectors
	
//Returns vector that is a sum of this and vector2 vectors for elements from i1 to i2
void Vector::add(int* vector, int* vector2, int* sum, int i1, int i2) {
	for (int i = i1; i < i2; i++)
		sum[i] = vector[i] + vector2[i];
}

//Returns a vector that is a product of this vector and matrix matrix
void Vector::multiply(int* vector, int* matrix, int* product, int i1, int i2, int n) {
	for (int i = i1; i < i2; i++) {
		product[i] = 0;
		for (int j = 0; j < n; j++)
			product[i] += vector[j] * matrix[i*n + j];
	}
}

//Returns a vector that is a product of this vector and number num
void Vector::multiply(int* vector, int num, int* res, int i1, int i2) {
	for (int i = i1; i < i2; i++)
		res[i] = vector[i] * num;
}

//Returns string representation of vector
std::string Vector::toString(int* vector, int n) {
	std::string str = "";
	for (int i = 0; i < n; i++) {
		str += std::to_string(vector[i]) + " ";
	}
	return str;
}

//Fills vector with number k
void Vector::fill(int* vector, int k, int n) {
	for (int i = 0; i < n; i++)
		vector[i] = k;
}

//Fills vector with decreasing number n
void Vector::fillSequence(int* vector, int n) {
	for (int i = 0; i < n; i++)
		vector[i] = n - i;
}

//Returns deep copy of this vector
int* Vector::getCopy(int* vector, int n) {
	int* cpVector = new int[n];
	for (int i = 0; i < n; i++)
		cpVector[i] = vector[i];
	return cpVector;
}

//Insertion sort
void Vector::sort(int* vector, int i1, int i2) {
	for (int i = i1; i < i2 - 1; i++) {
		int j = i + 1;

		while (j > i1) {
			if (vector[j - 1] > vector[j]) {
				int temp = vector[j - 1];
				vector[j - 1] = vector[j];
				vector[j] = temp;

			}
			j--;
		}
	}
}

//Merge sort
void Vector::merge(int* input, int low, int middle, int high) {
	int left = low;
	int right = middle + 1;
	int tmpLen = (high - low) + 1;
	int* tmp = new int[tmpLen];
	int tmpIndex = 0;

	while ((left <= middle) && (right <= high)) {
		if (input[left] < input[right]) {
			tmp[tmpIndex] = input[left];
			left = left + 1;
		} else {
			tmp[tmpIndex] = input[right];
			right = right + 1;
		}
		tmpIndex = tmpIndex + 1;
	}


	while (left <= middle) {
		tmp[tmpIndex] = input[left];
		left = left + 1;
		tmpIndex = tmpIndex + 1;
	}

	while (right <= high) {
		tmp[tmpIndex] = input[right];
		right = right + 1;
		tmpIndex = tmpIndex + 1;
	}

	for (int i = 0; i < tmpLen; i++) {
		input[low + i] = tmp[i];
	}

}


