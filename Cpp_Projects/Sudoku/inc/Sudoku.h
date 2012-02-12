#ifndef SUDOKU_H
#define SUDOKU_H

#include <cstdint>

#define SUDOKU_INDEX(r,c)	((r)*(9)+(c))

class Sudoku
{
	public:
		Sudoku();                               /* Default Constructor */
		~Sudoku();                              /* Destructor */
		int* Solve( int* );                     /* Generic Solver */
		int Check( int* );                      /* Check Solution */

	
	protected:

	private:
};

#endif /* SUDOKU_H */
