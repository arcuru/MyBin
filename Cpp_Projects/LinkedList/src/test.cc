#include "SingleLL.h"
#include <iostream>


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
	SingleLL h(FIFO);
	int list[5] = {1, 2, 3, 4, 5};
	h.Push((void*)list);
	int* y = (int*)h.Pop();
	for (int i=0; i < 4; i++)
		std::cout << y[i] << std::endl;
	return 0;
}
