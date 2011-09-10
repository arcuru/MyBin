#ifndef EARRAY_H
#define EARRAY_H

class EArray
{
	public:
		EArray(int* initial = 0, int len = 0);
		~EArray();
		void initArray(int* initial, int len);
		int* getArray();

		/*
		 * Manipulating the stored array
		 */

		/*
		 * Sort Functions
		 */
		int* bubbleSort();
		int* parallelBubbleSort();
		int* mergeSort();
		int* insertionSort();
		int* bInsertionSort();

		/*
		 * Search Functions for sorted arrays
		 */
		bool bSearch(int searchVal);

	private:
		int* array;
		int length;
};

#endif /* EARRAY_H */
