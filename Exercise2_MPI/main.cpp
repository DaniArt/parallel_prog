#include <stdio.h>
#include "mpi.h"
#include "Exercise2_dll.h"
#include <iostream>
using namespace std;

// ������� ��������� ������ ��� ������
double* malloc_array(int n)
{
	double* a = new double[n];
	return a;
}

// ������� ������������ ������ 
int free_array(double*a, int n)
{
	delete[] a;
	return 0;
}
int multmv(int n, double* A_glob, double* x, double* y)
{
	/*for (int i = 0; i < N; i++)
    {   R[i] = 0;
        for (int j = 0; j < N; j++)
        R[i] += M[i][j] * V[j];           ��������� ��������� ������� M nxn �� ������ V � ����������� � ������� R
    } */

	// ��������� ������� �� ������
	for (int k = 0; k < 100; k++)
	{
		for (int i = 0; i < n; i++)
		{
			y[i] = 0;
			for (int j = 0; j < n; j++)
			{
				y[i] += A_glob[i*n + j] * x[j];
			}
		}
		for (int i = 0; i < n; i++)
		{
			x[i] = y[i];
		}
	}

	// ���� �������

	return 0;
}

int main(int argc, char **argv)
{
	// ������������ MPI
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	// ����������� ������� ������ � ��������
	int n = 840;
	int n1 = n / size;
	//if (rank < n - n1 * size) n1++;

	// ��������� ������ 
	double *A_glob = malloc_array(n*n);
	double *x = malloc_array(n);
	double *y = malloc_array(n);

	// ���������� ������� � � ������� �
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

	// ����� ������� �� ����������, ������� �������� �������� ������������ ���������� ��������� � ��� ���������
	submit(multmv);

	free_array(A_glob, n*n);
	free_array(x, n);
	free_array(y, n);
	MPI_Finalize();
	return 0;
}

