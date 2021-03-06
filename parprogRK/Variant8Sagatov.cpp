#include <iostream>
#include "pt4.h"
#include "mpi.h"

using namespace std;

void main()
{
	int f, r, s;
	MPI_Initialized(&f);
	MPI_Comm_size(MPI_COMM_WORLD, &s);
	MPI_Comm_rank(MPI_COMM_WORLD, &r);
	auto k = s*(s + 3) / 2;
	int *z = new int[r + 1];
	int *q = new int[k];
	int *w = new int[s];
	int *e = new int[s];
	for (int i = 0; i<s; i++)
	{
		w[i] = i + 2, e[i] = !i ? 0 : w[i - 1] + e[i - 1];
	}
	if (!r)
	{
		for (auto i = 0; i<k; i++)
		{
			cin >> q[i];
		}
	}
	MPI_Scatterv(q, w, e, MPI_INT, z, r + 2, MPI_INT, 0, MPI_COMM_WORLD);
	for (int i = 0; i<r + 1; i++)
	{
		cout << z[i];
	}

	double* nums = new double[s*(s + 3) / 2];
	for (int i = 0; i < s*(s + 3) / 2; ++i)
		pt >> nums[i];

	double* result = new double[s*(s + 3) / 2];

	MPI_Reduce(nums, result, k<r + 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);

	if (r == 0) {
		for (int i = 0; i<r + 1; i++)
			cout << z[i];
	}
}
