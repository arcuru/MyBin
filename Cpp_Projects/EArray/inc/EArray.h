#ifndef EARRAY_H
#define EARRAY_H

template <class T>
class EArray
{
	public:
		EArray();						//!< Default Constructor
		EArray(int len);
		EArray(const T* initial, int len);
		EArray(const EArray &other);	//!< Copy constructor
		~EArray();
		void initArray(const T* initial, int len);

		/* 
		 *	Retrieve private values
		 */
		inline T* get_array() const;	//!< Return the whole array
		inline T get_index(int index) const;	//!< Retrieve a value in the array
		inline int get_length() const;	//!< Retrieve the length of the array

		/*
		 * Manipulating the stored array
		 */
		inline void set_index(int index, T value);	//!< Set a value in the array

		/*
		 * Sort Functions
		 */
		T* bubbleSort();				//!< Bubble Sort
		T* parallelBubbleSort();		//!< Parallel Bubble Sort
		T* mergeSort();					//!< Merge Sort
		T* insertionSort();				//!< Insertion Sort
		T* bInsertionSort();			//!< Binary Insertion Sort

		/*
		 * Search Functions for sorted arrays
		 */
		bool search(T searchVal) const;	//!< Basic search
		bool bSearch(T searchVal) const;	//!< Binary Search

		EArray& operator = ( const EArray &other );

	private:
		T* array;						//!< Main saved array
		int length;						//!< Length of the saved array
};

#include "../src/EArray.cc"

#endif /* EARRAY_H */
