#include "EArray.h"
#include <cstring>
#include <cstddef>
/*! \file main.cc
 * */


//#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif

	template < class T >
EArray<T>::EArray()
{
	array = NULL;
	length = 0;
}

	template < class T >
EArray<T>::EArray(int len)
{
	array = new T[len];
	length = len;
}

	template < class T >
EArray<T>::EArray(const T* initial, int len)
{
	array = NULL;
	length = 0;
	initArray(initial, len);
}
 
	template < class T >
EArray<T>::EArray(const EArray &other)
{
	array = new T[other->len];
	length = other->len;
	memcpy(array, other->array, sizeof(T) * length);
}

	template < class T >
EArray<T>::~EArray()
{
	delete[] array;
}

	template < class T >
void EArray<T>::initArray(const T* initial, int len)
{
	if (NULL != array)
		delete[] array;
	array = new T[len];
	memcpy(array, initial, sizeof(T) * len);
	length = len;
}

	template < class T >
inline T* EArray<T>::get_array() const
{
	return array;
}

	template < class T >
inline T EArray<T>::get_index(int index) const
{
	return array[index];
}

	template < class T >
inline int EArray<T>::get_length() const
{
	return length;
}

	template < class T >
inline void EArray<T>::set_index(int index, T value)
{
	array[index] = value;
}

	template < class T >
T* EArray<T>::bubbleSort()
{
	T tmp;
	int k, i = 1;
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

	template < class T >
bool EArray<T>::search(T searchVal) const
{
	for (int i=0; i<length; i++) {
		if (searchVal == array[i])
			return true;
	}
	return false;
}

	template < class T >
bool EArray<T>::bSearch(T searchVal) const
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

