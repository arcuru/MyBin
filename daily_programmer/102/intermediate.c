#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

bool ncset( const char* s, size_t n )
{
	size_t i;
	uint32_t bitvec = 0;
	for (i=0; NULL != s[i]; i++) {
		assert((s[i] <= 'z' && s[i] >= 'a') || (s[i] <= 'Z' && s[i] >= 'A'));
		if (s[i] <= 'z' && s[i] >= 'a')
			bitvec |= 1 << s[i] - 'a';
		else
			bitvec |= 1 << s[i] - 'A';
	}
	// Count active bits
	size_t count = 0;
	for (;0 != bitvec; count++)
		bitvec &= bitvec - 1;
	return count <= n;
}

int main ( int argc, char *argv[] )
{
	printf("%d\n", ncset(argv[1], atoi(argv[2])));
	return EXIT_SUCCESS;
}

