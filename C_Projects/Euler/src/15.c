#include "Euler.h"
#include <stdlib.h>

int64 Euler_15()
{
    int grid = 20;
    int64* array1 = (int64*) calloc(grid + 1, sizeof (int64));
    array1[0] = 1;
    int count = 1;
    int index = 0;
    int check = 0;
    int64* array2 = (int64*) calloc(grid + 1, sizeof (int64));
    while (count <= grid) {
        count++;
        check = 0;
        while (check < count) {
            if (check == 0) {
                array2[0] = array1[0];
            } else if (check != count - 1) {
                array2[check] = array1[check - 1] + array1[check];
            } else if (check == count - 1) {
                array2[check] = array1[check - 1];
            }
            check++;
        }
        index = 0;
        while (index <= count) {
            array1[index] = array2[index];
            index++;
        }
        array1[count] = 0;
    }
    count--;
    while (count > 0) {
        int check = 0;
        while (check <= count) {
            if (check < count) {
                array2[check] = array1[check] + array1[check + 1];
            } else if (check == count) {
                array2[check] = 0;
            }
            check++;
        }
        index = 0;
        while (index <= count) {
            array1[index] = array2[index];
            index++;
        }
        count--;
    }
    int64 ans = array1[0];
    //free(array1);
    //free(array2);
    return (int64) ans;
}
