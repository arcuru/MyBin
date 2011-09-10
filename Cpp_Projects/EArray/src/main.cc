#include "EArray.h"

#ifndef NULL
#define NULL 0
#endif

//#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif

EArray::EArray(int* initial,int len)
{
	initArray(initial, len);
}

EArray::~EArray()
{
	delete[] array;
}

void EArray::initArray(int* initial, int len)
{
	array = initial;
	length = len;
}

int* EArray::getArray()
{
	return array;
}

int* EArray::bubbleSort()
{
    int k, tmp;
    int i = 1;
    while (i < length) {
        k = i;
        while ((k > 0) && (array[k] < array[k - 1])) {
            tmp = array[k];
            array[k] = array[k - 1];
            array[k - 1] = tmp;
            k--;
        }
        i++;
    }
    return array;
}

bool EArray::bSearch(int searchVal)
{
	int low = 0;
	int high = length;
	int mid;
	while (low <= high) {
		mid = (low + high) / 2;
		if (array[mid] < searchVal)
			low = mid + 1;
		else if (array[mid] > searchVal)
			high = mid;
		else
			return true;
	}
	return false;
}

