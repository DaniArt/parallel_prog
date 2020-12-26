#include "pt4.h"
#include "mpi.h"
void findmin()
{
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	double* nums = new double[k=s*(s+3)/2];
	for (int i = 0; i < k; ++i)
		pt >> nums[i];

	double* result = new double[k];
	MPI_Reduce(nums, result, k, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		for (int i = 0; i < k; ++i)
			pt << result[i];
	}
}
