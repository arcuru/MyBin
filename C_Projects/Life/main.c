#include <stdio.h>
#include <stdlib.h>
//#include <stdint.h>
#define IND(x,y,w)    ((y)*(w)+(x))
#define LENGTH(w,h)   ((w)*(h) >> 3)
#define REMOVE_1(x)	((x)&((x)-1))

void printLife(unsigned char *p, int w, int h);
void iterate(unsigned char **a, unsigned char **b, int w, int h);
void setPlace(unsigned char *a, int index, unsigned char val);

int main()
{
    int w=64,h=64;
    unsigned char *a, *b; //a points to current, b point to next
    a=(unsigned char*)calloc(LENGTH(w,h), sizeof(unsigned char));
    b=(unsigned char*)calloc(LENGTH(w,h), sizeof(unsigned char));
	setPlace(a, IND(3,3,w), 1);
	setPlace(a, IND(4,4,w), 1);
	setPlace(a, IND(5,4,w), 1);
    int i;
    for (i=0;i<10000;i++)
	{
        iterate(&a,&b,w,h);
    }
    return 0;
}

void setPlace(unsigned char *a, int index, unsigned char val)
{
    a[index >> 3] |= val << (index & 0b111); 
}

int getPlace(unsigned char *a, int index)
{
	return (a[index >> 3] & (1 << (index & 0b111))) >> (index & 0b111);
}

int bitCount(int bit)
{
    int count;
    for (count = 0; bit; ++count)
        bit = REMOVE_1(bit);
    return count;
}

int neighborCountThree(unsigned char *a, int index)
{
	int count = 0;
	if (index >> 3 == (index+2) >> 3)
	{ // All 3 in same byte
		int byte = a[index >> 3];
		byte &= 0b111 << (index & 0b111);
		return bitCount(byte);
	}
	else
	{
		int i;
		for (i=0; i<2; i++)
			count += getPlace(a, index+i);
	}
	return count;
}

// May not work correctly at the edges
int neighbors(unsigned char *a, int x, int y, int w, int h)
{
	int count = 0;
	int index = IND(x,y,w);
	int lowind = index - (w + 1);
	int highind = index + (w - 1);
	if (lowind >= 0) count += neighborCountThree(a, lowind);
	count += neighborCountThree(a, index - 1);
	if (highind > w*h) count += neighborCountThree(a, highind);
	count -= getPlace(a, index);
	return count;
}

void iterate(unsigned char **a, unsigned char **b, int w, int h)
{
    int i,d;
	for (i=0; i<LENGTH(w,h); i++) {
		(*b)[i] = 0;
	}
    for (i=0; i<h; i++) {
        for (d=0; d<w; d++) {
            switch (neighbors(*a,d,i,w,h)) {
            case 2:
                if (getPlace(*a, IND(d,i,w))==1) {
            case 3:
					setPlace(*b, IND(d,i,w), 1);
                    break;
                }
            default: break;
            }
        }
    }
    unsigned char *p;
    p=*a;
    *a=*b;
    *b=p;
}

void printLife(unsigned char *p, int w, int h)
{
    int i,d;
    for (d=-2; d<w; d++) {
		putchar('-');
	}
    putchar('\n');
    for (i=0; i<h; i++) {
		putchar('|');
        for (d=0; d<w; d++) {
            (getPlace(p, IND(d,i,w))==1) ? putchar('+') : putchar(' ');
        }
		putchar('|');
        putchar('\n');
    }
    for (d=-2; d<w; d++) {
		putchar('-');
	}
    putchar('\n');
}

