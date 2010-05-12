#include "CC_Euler.h"
#include <stdlib.h>
#include <stdio.h>

int64 Euler_59() {
	int i = 0;
	char filepath[100];
	snprintf(filepath,sizeof(filepath),"%s59.txt",CC_EULER_DATA_PATH);
	FILE* code = fopen(filepath, "r");
	if (code == NULL)
		return 0;
	int c = 0;
	char* FileArray = (char*) calloc(1201,sizeof(char));
	char* A = (char*) calloc(1201,sizeof(char));
	while (fscanf(code, "%d", &c)) {
		FileArray[i] = c;
		i++;
		c = fgetc(code);
		if (c == EOF)
			break;
	}
	int decode[3];
	int64 total=0;
	bool print = false;
	for (decode[0] = 'a'; decode[0] <= 'z'; decode[0]++) {
		for (decode[1] = 'a'; decode[1] <= 'z'; decode[1]++) {
			for (decode[2] = 'a'; decode[2] <= 'z'; decode[2]++) {
				print = true;
				//printf("%c%c%c\n",decode[0],decode[1],decode[2]);
				for (i = 0; i < 1201; i++) {
					A[i] = (char) (FileArray[i] ^ decode[i % 3]);
					if (A[i]>'z' || A[i]<' ') {
						print=false;
						break;
					}
					if (A[i-3]=='G' && A[i-2]=='o' && A[i-1]=='d') {
						print = true;
					}
				}
				if (print) {
					total=0;
					for (i = 0; i < 1202; i++) {
						//printf("%c", A[i]);
						total+=(int)A[i];
					}
				}
			}
		}
	}
	free(A);
	fclose(code);
	return (int64)total;
}
