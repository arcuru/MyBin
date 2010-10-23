#include "Euler.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int64 Euler_229()
{
    //printf("USES 1GB MEMORY\nARE YOU SURE YOU WANT TO?\nEDIT FILE TO CONTINUE\n");
    //const int memsize
    uns64 N =10000000; //2000000000;
    unsigned char* list = (unsigned char*) calloc((N + 1) >> 1,
                          sizeof(unsigned char));
    if (!list) {
        printf("Memory Fail\n");
        return 0;
    }
    uns64 x, y;
    int tmp;
    int shift;
    uns64 tmpx;
    for (x = 1; x * x <= N; x++) {
        y = 1;
        tmpx = x * x;
        while (1) {
            uns64 tmpy = y * y;
	    y++;

	    /* x^2 + y^2 */
            if (tmpx + tmpy > N)
                break;
            tmp = tmpx + tmpy;
            shift = 0;
            if (tmp & 1)
                shift = 4;
            list[tmp >> 1] |= 1 << shift;

	    /* x^2 + 2 * y^2 */
            if (tmpx + (tmpy << 1) > N)
                continue;
            tmp = tmpx + (tmpy << 1);
            shift = 0;
            if (tmp & 1)
                shift = 4;
            list[tmp >> 1] |= 2 << shift;

	    /* x^2 + 3 * y^2 */
            if (tmpx + (tmpy * 3) > N)
                continue;
            tmp = tmpx + (tmpy * 3);
            shift = 0;
            if (tmp & 1)
                shift = 4;
            list[tmp >> 1] |= 4 << shift;

	    /* x^2 + 7 * y^2 */
            if (tmpx + (tmpy * 7) > N)
                continue;
            tmp = tmpx + (tmpy * 7);
            shift = 0;
            if (tmp & 1)
                shift = 4;
            list[tmp >> 1] |= 8 << shift;

        }
    }
    int count = 0;
    for (x = 1; x <= N; x++) {
        int tmp = x >> 1;
        int shift = 0;
        if (x & 1)
            shift = 4;
        if ((list[tmp] & (15 << shift)) == 15 << shift)
            count++;
    }
    free(list);
    return (int64) count;
}
