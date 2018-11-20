#include <string>

//Vector module. Containing all necessary methods to perform operations with vectors
class Vector {
public:
	//Returns vector that is a sum of this and vector2 vectors for elements from i1 to i2
	static void add(int* vector, int* vector2, int* sum, int i1, int i2);

	//Returns a vector that is a product of this vector and matrix matrix
	static void multiply(int* vector, int* matrix, int* product, int i1, int i2, int n);

	//Returns a vector that is a product of this vector and number num
	static void multiply(int* vector, int num, int* res, int i1, int i2);

	//Returns string representation of vector
	static std::string toString(int* vector, int n);

	//Fills vector with number k
	static void fill(int* vector, int k, int n);

	//Fills vector with decreasing number k
	static void fillSequence(int* vector, int n);

	//Returns deep copy of this vector
	static int* getCopy(int* vector, int n);

	//Insertion sort
	static void sort(int* vector, int i1, int i2);

	//Merge sort
	static void merge(int* input, int low, int middle, int high);
};