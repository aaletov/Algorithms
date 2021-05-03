#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "functions.hpp"

bool testSort(void (*sortAlg)(int*, int), double* timeDiff, int len);
void bucketSortRand(int* array, int len);

void veryFastTest()
{
	int NUMS[] = { -28, -9, -11, -2, 6, 7, 8, 17, 22, 23 };
	int len = 10; // sizeof(NUMS) / sizeof(NUMS[0]);
	for (int i = 0; i < 10; i++)
	{
		//NUMS[i] = pow(-1, rand() % 2) * (rand() / 1000);
		std::cout << NUMS[i] << ' ';
	}
	std::cout << '\n';
	heapSort(NUMS, len);
	for (int i = 0; i < len; i++)
	{
		std::cout << NUMS[i] << ' ';
	}
	std::cout << '\n' << '\n';
}

int main()
{
	srand(time(0));
	const int CORR_TEST_COUNT = 100;
	const int CORR_TEST_EL_COUNT = 100;
	const int COMP_TEST_EL_COUNT1 = 25000;
	const int COMP_TEST_EL_COUNT2 = 10000;
	void (*sortAlgs[])(int*, int) = { &bubbleSort<int>, &bucketSortRand, &heapSort<int> };
	std::string algNames[] = { "Bubble sort", "Bucket sort", "Heap sort" };

	double* timeDiff = new double[3];

	bool result = true;

	for (int i = 0; i < 3; i++)
	{
		std::cout << "Algorithm correctntness test (" << CORR_TEST_COUNT
				  << " tests for " << CORR_TEST_EL_COUNT << " random values)" << '\n';
		std::cout << algNames[i] << ' ';
		result = true;
		for (int j = 0; j < CORR_TEST_COUNT; j++)
		{
			result = result && testSort(sortAlgs[i], timeDiff, CORR_TEST_EL_COUNT);
		}
		if (result)
		{
			std::cout << "works correctly" << '\n';
		}
		else
		{
			std::cout << "works incorrectly" << '\n';
		}
		std::cout << '\n';
	}

	for (int i = 0; i < 3; i++)
	{
		std::cout << "Algorithm complexity test" << '\n';
		result = testSort(sortAlgs[i], timeDiff, COMP_TEST_EL_COUNT2);
		if (result)
		{

			std::cout << "Best case time: " << timeDiff[0] << '\n'
				<< "Average case time:" << timeDiff[1] << '\n'
				<< "Worst case time:" << timeDiff[2] << '\n' << '\n';
		}
		else
		{
			std::cout << " works incorrectly" << '\n';
		}
	}
}

bool testSort(void (*sortAlg)(int*, int), double* timeDiff, int len)
{
	int* best = new int[len];
	int* average = new int[len];
	int* worst = new int[len];

	for (int i = 0; i < len; i++)
	{
		best[i] = i;
		average[i] = pow(-1, rand() % 2) * rand();
		worst[i] = len - i;
	}

	clock_t startTime = std::clock();
	(*sortAlg)(best, len);
	timeDiff[0] = (std::clock() - startTime) / (double)CLOCKS_PER_SEC;
	startTime = std::clock();
	(*sortAlg)(average, len);
	timeDiff[1] = (std::clock() - startTime) / (double)CLOCKS_PER_SEC;
	startTime = std::clock();
	(*sortAlg)(worst, len);
	timeDiff[2] = (std::clock() - startTime) / (double)CLOCKS_PER_SEC;


	for (int i = 0; i < len - 1; i++)
	{
		if (best[i] > best[i + 1] || worst[i] > worst[i] || average[i] > average[i + 1])
		{
			delete[] best;
			delete[] worst;
			delete[] average;
			return false;
		}
	}
	delete[] best;
	delete[] worst;
	delete[] average;
	return true;
}

void bucketSortRand(int* array, int len)
{
	bucketSort(array, len, -1 * RAND_MAX, RAND_MAX);
}
