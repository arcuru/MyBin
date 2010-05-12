#include "C_Euler.h"
#include <stdio.h>

static int help(int h)
{
    if (!h)
        return 0;
    if (!(h & 1)) {
        if (h < 8)
            return 2;
        else
            return 4;
    }
    if (h == 1 || h == 5)
        return 1;
    if (h == 9)
        return 2;
    return 3;
}

static int sc(char single)
{
    if (single == 'I')
        return 1;
    if (single == 'V')
        return 5;
    if (single == 'X')
        return 10;
    if (single == 'L')
        return 50;
    if (single == 'C')
        return 100;
    if (single == 'D')
        return 500;
    if (single == 'M')
        return 1000;
    return 0;
}

static int bigness(int n)
{
    int out = 0;
    int ch = 0;
    while (n) {
        int h = n % 10;
        n /= 10;
        if (ch == 3)
            return out + h;
        ch++;
        out += help(h);
    }
    return out;
}

static int getvalue(char* line)
{
    int i = 0;
    int total = 0;
    while (line[i + 1] >= 'A' && line[i + 1] <= 'Z') {
        if (sc(line[i + 1]) > sc(line[i])) {
            total -= sc(line[i]);
            i++;
            continue;
        }
        total += sc(line[i]);
        i++;
    }
    total += sc(line[i]);
    return total;
}

int64 Euler_89()
{
    char filepath[100];
    snprintf(filepath, sizeof(filepath), "%s89.txt", C_EULER_DATA_PATH);
    FILE* data = fopen(filepath, "r");
    if (data == NULL)
        return 0;
    int saved = 0;
    char line[64];
    while (fgets(line, sizeof(line), data) != NULL) {
        int value = getvalue(line);
        int size = bigness(value);
        int length = 0;
        while (line[length] >= 'A' && line[length] <= 'Z')
            length++;
        saved += length - size;
    }
    fclose(data);
    return (int64) saved;
}
