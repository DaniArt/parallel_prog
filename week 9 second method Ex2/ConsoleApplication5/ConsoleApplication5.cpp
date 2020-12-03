#include "stdafx.h"
#include <iostream>
#include <omp.h>
#include <thread>
#include <time.h>




void show(int **mat, int n, int m) {

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			std::cout << mat[i][j] << " ";
		}
		std::cout << '\n';
	}
	std::cout << "\n\n";
}


void show(int* arr, int size) {
	for (int i = 0; i < size; ++i) {
		std::cout << arr[i] << " ";
	}
	std::cout << "\n\n";
}




int main() {
	setlocale(LC_ALL, "Russian");

	int m, n;
	int** matrix;
	int* array_;
	int* result;


	std::cout << "enter n = ";
	std::cin >> n;

	std::cout << "enter m = ";
	std::cin >> m;
	std::cout << '\n';

	matrix = new int*[n];
	array_ = new int[m];
	result = new int[m];

	for (int i = 0; i < n; ++i) {
		matrix[i] = new int[m];
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			matrix[i][j] = rand() % 10;
		}
	}
	//show(matrix, n, m);


	for (int i = 0; i < m; ++i) {
		array_[i] = rand() % 10;
	}
	//show(array_, m);


	clock_t timeBegin = clock();

	for (int i = 0; i < n; ++i)
	{
		result[i] = 0;
		for (int j = 0; j < m; ++j)
		{
			result[i] += matrix[i][j] * array_[j];
		}
	}
	//show(result, n);

	std::cout << "Total ticks 1 = " << clock() - timeBegin << '\n';




	omp_set_num_threads(8);
	timeBegin = clock();

#pragma omp parallel shared(matrix, array_, result)
	{
#pragma omp for schedule (dynamic)
		for (int i = 0; i < n; ++i) {
			result[i] = 0;
			for (int j = 0; j < m; ++j)
			{
				result[i] += matrix[i][j] * array_[j];
			}
		}
	}

	std::cout << "Total ticks 2 = " << clock() - timeBegin << '\n';


	for (int i = 0; i < n; ++i) {
		delete[] matrix[i];
	}
	delete[] matrix;

	delete[] array_;
	delete[] result;

	system("pause");
	return 0;
}



/* output
enter n = 1000
enter m = 2000

Total ticks 1 = 12
Total ticks 2 = 8

*/