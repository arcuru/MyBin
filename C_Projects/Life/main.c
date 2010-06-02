#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define IND(x,y,w)    ((y)*(w)+(x))

void printLife(unsigned char *p, int w, int h);
void iterate(unsigned char **a, unsigned char **b, int w, int h);

int main()
{
    int w=64,h=64;
    unsigned char *a, *b; //a points to current, b point to next
    a=(unsigned char*)calloc(w*h,sizeof(unsigned char));
    b=(unsigned char*)calloc(w*h,sizeof(unsigned char));
    a[IND(3,3,w)]=1;
    a[IND(4,4,w)]=1;
    a[IND(5,4,w)]=1;
//    printLife(a,w,h);
    int i;
    for (i=0;i<10000;i++)
        iterate(&a,&b,w,h);
//    printLife(a,w,h);
    return 0;
}

int neighbors(unsigned char *a, int x, int y, int w, int h)
{
    int tmpx,tmpy,count=0;
    for (tmpx=x-1; tmpx<(x+2); tmpx++) {
        for (tmpy=y-1; tmpy<(y+2); tmpy++) {
            if ((tmpx==x && tmpy==y) || tmpx<0 || tmpy<0 || tmpx>=w || tmpy>=h)
                continue;
            if (a[IND(tmpx,tmpy,w)]==1)
                count++;
        }
    }
    return count;
}

void iterate(unsigned char **a, unsigned char **b, int w, int h)
{
    int i,d;
    for (i=0; i<h; i++) {
        for (d=0; d<w; d++) {
            switch (neighbors(*a,d,i,w,h)) {
            case 2:
                if ((*a)[IND(d,i,w)]==1) {
            case 3:
                    (*b)[IND(d,i,w)]=1;
                    break;
                }
            default:
                (*b)[IND(d,i,w)]=0;
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
    for (i=0; i<h; i++) {
        for (d=0; d<w; d++) {
            (p[IND(d,i,w)]==1) ? putchar('+') : putchar(' ');
        }
        putchar('\n');
    }
}
