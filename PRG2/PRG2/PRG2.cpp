#include <stdio.h>
#include "Matrix.h"
#include "Vector.h"
#include <iostream>
#include <fstream>
#include <mpi.h>
#include <cmath>
#include <windows.h>

using namespace std;

/*---------Main module----------
Parallel and Distributed Computing
Coursework. PRG2
Kovbasa Sviatoslav
IO-53
21.04.2018
A = sort(d * B + C * (MO * MX))
*/

//Size of arrays
static int n = 16;

//Result output string
static string result = "";

int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0) {
		cout << "Turn off unused cores and press enter to continue" << endl;
		getchar();
	}
	int* testLengths = new int[3]{ 900, 1800, 2400 };
	for (int lenIndex = 0; lenIndex < 3; lenIndex++) {
		double time = 0;
		MPI_Barrier(MPI_COMM_WORLD);
		time -= MPI_Wtime();
		n = testLengths[lenIndex];
		//Number of threads
		int p;
		MPI_Comm_size(MPI_COMM_WORLD, &p);
		//Dimension of a cube
		int k = (int)ceil(log2(p));
		//Size of the parts of arrays in threads
		int h = n / p;
		//Input data
		int *A, *B, *C, *D, *E;
		int *MO, *MX, *MZ;
		A = new int[n];
		B = new int[n];
		C = new int[n];
		D = new int[h];
		E = new int[h];
		MX = new int[n * n];
		MO = new int[n * n];
		MZ = new int[n * n];
		int d;
		std::cout << "T" + std::to_string(rank) + " started" << endl;
		//1. If rank==0 input B, C, MX
		if (rank == 0) {
			Vector::fillSequence(B, n);
			Vector::fill(C, 1, n);
			Matrix::fill(MX, 1, n);
		}
		//2. If rank==p-1 input d, MO
		if (rank == p - 1) {
			d = 1;
			Matrix::fill(MO, 1, n);
		}

		for (int i = 1; i <= k; i++) {
			int halfProcesses = (int)floor(pow(2, i - 1));
			int halfSize = n / (int)floor(pow(2, i));

			for (int tid = 0; tid < halfProcesses; tid++) {
				//3. Send B, C, MX
				if (rank == tid) {
					MPI_Send(&B[halfSize], halfSize, MPI_INT, tid + halfProcesses, 0, MPI_COMM_WORLD);
					MPI_Send(C, n, MPI_INT, tid + halfProcesses, 1, MPI_COMM_WORLD);
					MPI_Send(MX, n * n, MPI_INT, tid + halfProcesses, 2, MPI_COMM_WORLD);
				}
				//4. Recieve B, C, MX
				if (rank == tid + halfProcesses) {
					MPI_Recv(B, halfSize, MPI_INT, tid, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
					MPI_Recv(C, n, MPI_INT, tid, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
					MPI_Recv(MX, n * n, MPI_INT, tid, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				}
				//5. Send MO, c
				if (rank == p - tid - 1) {
					MPI_Send(&MO[halfSize * n], halfSize * n, MPI_INT, p - tid - halfProcesses - 1, 3, MPI_COMM_WORLD);
					MPI_Send(&d, 1, MPI_INT, p - tid - halfProcesses - 1, 4, MPI_COMM_WORLD);
				}
				//6. Recieve MO, c
				if (rank == p - tid - halfProcesses - 1) {
					MPI_Recv(MO, halfSize * n, MPI_INT, p - tid - 1, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
					MPI_Recv(&d, 1, MPI_INT, p - tid - 1, 4, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				}
			}
		}

		//7. Calculations 1
		Matrix::multiply(MO, MX, MZ, 0, h, n);
		Vector::multiply(C, MZ, D, 0, h, n);
		Vector::multiply(B, d, E, 0, h);
		Vector::add(E, D, A, 0, h);
		Vector::sort(A, 0, h);

		int size = h;
		for (int i = k; i >= 1; i--) {
			int halfProcesses = (int)floor(pow(2, i - 1));
			for (int tid = p - 1; tid >= p - halfProcesses; tid--) {

				//8. Send A
				if (rank == tid - halfProcesses)
					MPI_Send(A, size, MPI_INT, tid, 0, MPI_COMM_WORLD);

				//9. Recieve A 
				if (rank == tid) {
					MPI_Recv(&A[size], size, MPI_INT, tid - halfProcesses, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
					//10. Merge A
					Vector::merge(A, 0, size - 1, size * 2 - 1);
				}
			}
			size = size * 2;
		}

		//11. If rank==p-1 output A
		if (rank == p - 1)
			if(n <= 16)
				std::cout << Vector::toString(A, n) << endl;

		std::cout << "T" + std::to_string(rank) + " finished" << endl;
		MPI_Barrier(MPI_COMM_WORLD);
		time += MPI_Wtime();

		if(rank == 0)
			result += "N: " + std::to_string(n) + "\nP: " + std::to_string(p) + "\nTime: " + std::to_string(time * 1000) + " ms\n\n";
	}
	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	std::string path = "resultMPI" + std::to_string(size) + ".txt";
	MPI_Finalize();
	ofstream outputFile;
	outputFile.open(path);
	outputFile << result;
	outputFile.close();
	return 0;
}




