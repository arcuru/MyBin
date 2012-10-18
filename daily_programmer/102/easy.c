#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

int main ( int argc, char *argv[] )
{
	if (argc < 2) {
		printf("Usage: %s Roll-String\n", argv[0]);
		return 1;
	}
	int A=1, B=-1, C=0;
	int i;
	bool A_exists = false;
	for (i=0; argv[1][i] != NULL; i++) {
		if ('d' == argv[1][i] || 'D' == argv[1][i]) {
			if (0 != i)
				A_exists = true;
		}
		if ('+' == argv[1][i])
			C = 1;
		if ('-' == argv[1][i])
			C = -1;
	}
	char* tmp = strtok(argv[1], "dD");
	if (A_exists) {
		A = atoi(tmp);
		if (0 != C) {
			B = atoi(strtok(NULL, "+-"));
			C *= atoi(strtok(NULL, "+-"));
		}
		else
			B = atoi(strtok(NULL, "+-"));
	}
	else {
		if (0 == C)
			B = atoi(tmp);
		else {
			B = atoi(strtok(tmp, "+-"));
			C *= atoi(strtok(NULL, "+-"));
		}
	}
	//printf("A=%d\nB=%d\nC=%d\n", A, B, C);
	srand(time(NULL));
	printf("Score = %d\n",(A * (rand() / (RAND_MAX/B))) + C);

	return EXIT_SUCCESS;
}
