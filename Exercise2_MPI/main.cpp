#include <stdio.h>
#include "mpi.h"
#include "Exercise2_dll.h"
#include <iostream>
using namespace std;

// Ôóíêöèÿ âûäåëåíèÿ ïàìÿòè ïîä âåêòîð
double* malloc_array(int n)
{
	double* a = new double[n];
	return a;
}

// Ôóíêöèÿ îñâîáîæäåíèÿ ïàìÿòè 
int free_array(double*a, int n)
{
	delete[] a;
	return 0;
}
int multmv(int n, double* A, double* x, double* y) 

{ 


	int rank, size; 

 

	MPI_Comm_rank(MPI_COMM_WORLD, &rank); 

	MPI_Comm_size(MPI_COMM_WORLD, &size); 


	int const m = n / size; 

	double* local_A = malloc_array(n * n); 

	double* local_y = malloc_array(n); 


	MPI_Scatter(A, n * m, MPI_DOUBLE, local_A, n * m, MPI_DOUBLE, 0, MPI_COMM_WORLD); 

	MPI_Bcast(x, n, MPI_DOUBLE, 0, MPI_COMM_WORLD); 


	for (int k = 0; k < 100; k++) 

	{ 

		for (int i = 0; i < n; i++) 

		{ 

			y[i] = 0; 

			for (int j = 0; j < n; j++) 

			{ 

				y[i] += A[i * n + j] * x[j]; 

			} 

		} 

		for (int i = 0; i < n; i++) 

		{ 

			x[i] = y[i]; 

		} 

	} 


	MPI_Gather(&y[0], m, MPI_DOUBLE, &local_y[0], m, MPI_DOUBLE, 0, MPI_COMM_WORLD); 

 

	free_array(local_A); 

	free_array(local_y); 

	return 0; 

}

int main(int argc, char **argv)
{
	// Èíèöèëèçàöèÿ MPI
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	// Îïðåäåëåíèå ðàçìåðà çàäà÷è è ïîäçàäà÷
	int n = 840;
	int n1 = n / size;
	//if (rank < n - n1 * size) n1++;

	// Âûäåëåíèå ïàìÿòè 
	double *A_glob = malloc_array(n*n);
	double *x = malloc_array(n);
	double *y = malloc_array(n);

	// Çàïîëíåíèå ìàòðèöû À è âåêòîðà õ
	if (rank == 0)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				A_glob[i*n + j] = (double)rand() / RAND_MAX / (n / 2);
			}
			x[i] = (double)rand() / RAND_MAX / (n / 2);
			y[i] = 0;
		}
	}

	MPI_Barrier(MPI_COMM_WORLD);

	multmv(n, A_glob, x, y);

	if (rank == 0) {
		cout << "The Program is RUN on " << size << " CPU" << endl;
		cout << " y[0] = " << y[0] << "!" << endl;
	}
	
	submit(multmv);

	free_array(A_glob, n*n);
	free_array(x, n);
	free_array(y, n);
	MPI_Finalize();
	return 0;
}

