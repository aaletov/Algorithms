#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <list>
#include <cmath>
#include <algorithm>

template <typename T>
void bubbleSort(T* array, int len)
{
	int c;
	int k = 1;
	while (true)
	{
		c = 0;
		for (int i = 0; i < len - k; i++) // n - k
		{
			if (array[i] > array[i + 1]) // const
			{
				std::swap(array[i], array[i + 1]);
				c++;
			}
		}
		if (c == 0)
		{
			break;
		}
		k++;
	}
}

// for range [-RAND_MAX; RAND_MAX]
void bucketSort(int* array, int len, int lowerLimit, int upperLimit)
{
	if (lowerLimit >= upperLimit)
	{
		throw - 1;
	}

	const int BUCKETS_COUNT = 10;
	double range = upperLimit - lowerLimit;
	int step = range / BUCKETS_COUNT;

	int bucketLimits[BUCKETS_COUNT + 1];
	for (int i = 0; i < BUCKETS_COUNT; i++)
	{
		bucketLimits[i] = lowerLimit + step * i;
	}
	bucketLimits[BUCKETS_COUNT] = INT_MAX;

	int lastPushed = -1;
	std::list<int> buckets[BUCKETS_COUNT];

	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < BUCKETS_COUNT; j++)
		{
			if (array[i] >= bucketLimits[j] && array[i] < bucketLimits[j + 1])
			{
				buckets[j].push_back(array[i]);
			}
		}
	}
	int bucketSize;
	for (int i = 0; i < BUCKETS_COUNT; i++)
	{
		bucketSize = buckets[i].size();
		buckets[i].sort();
		for (int j = 0; j < bucketSize; j++)
		{
			array[lastPushed + 1 + j] = buckets[i].front();
			buckets[i].pop_front();
		}
		lastPushed += bucketSize;
	}
}

template <typename T>
void findNMax(T* array, int len, int maxCount, T* maxes)
{
	for (int i = 0; i < maxCount; i++)
	{
		maxes[i] = array[i];
	}
	std::sort(&maxes[0], &maxes[maxCount - 1] + 1);
	for (int i = 0; i < len; i++)
	{
		if (array[i] > maxes[0])
		{
			maxes[0] = array[i];
			std::sort(&maxes[0], &maxes[maxCount - 1] + 1);
		}
	}
}

template <typename T>
void heapify(T* array, int len, int index)
{
	int left = index * 2 + 1;
	int right = index * 2 + 2;
	int largestIndex;
	if (left < len && array[left] > array[index])
	{
		largestIndex = left;
	}
	else
	{
		largestIndex = index;
	}
	if (right < len && array[right] > array[largestIndex])
	{
		largestIndex = right;
	}
	if (largestIndex != index)
	{
		std::swap(array[index], array[largestIndex]);
		heapify(array, len, largestIndex);
	}
}

template <typename T>
void buildHeap(T* array, int len)
{
	for (int i = len / 2 - 1; i > -1; i--)
	{
		heapify(array, len, i);
	}
}

template <typename T>
void heapSort(T* array, int len)
{
	for (int i = 0; i < len; i++)
	{
		buildHeap(array, len - i);
		std::swap(array[0], array[len - 1 - i]);
	}
}

#endif