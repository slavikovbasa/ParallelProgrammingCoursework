6 semester Parallel and Distributed systems programming Coursework part 2

You need MPI to run this program. I tested it with MS-MPI 9.0.12497.11.

C++ program that utilizes MPI to calculate expression:
A = sort(d * B + C * (MO * MX)),
where A, B, C are vectors with the size N, d is integer, MO and MX are NxN matrices.

It is assumed that processors form Hypercube topology, what means that program works only if passed as command-line argument number of cores is equal to 2^i, where i is a natural number.

Program is launched via `mpirun` program with corresponding command-line arguments (e.g. `mpirun -np 4 PRG2.exe` launches it on 4 cores). 
Program runs time-measuring tests on 900, 1800 and 2400 sized vectors.

Tests show that this implementation more efficient, than the C# one.
