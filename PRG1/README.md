6 semester Parallel and Distributed systems programming Coursework part 1

C# program that utilizes Semaphores, Mutexes, Events and Locks to calculate expression:
A = sort(d * B + C * (MO * MX)),
where A, B, C are vectors with the size N, d is integer, MO and MX are NxN matrices.

Program is launched with one command-line argument that defines number of cores, for which algorithm will be adapted.
Program runs time-measuring tests on 900, 1800 and 2400 sized vectors.

Tests show that this implementation is slower, than the MPI one. 
