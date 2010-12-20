#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <NumberTheory.h>

#define PRINT(x)    printf("%d\n",(x));
#define MAXLINE     100

int64_t Compute_Value(char **,char endvalue);
int64_t calcOp(int64_t a, int64_t b, char op);
int64_t getInt(char**);

int main(int argc, char *argv[])
{
    if (argc<2) {
        printf("Usage: %s Expression\n",argv[0]);
        return 1;
    }
    FILE *fp;
    if ((fp = fopen(argv[1],"r")) == NULL) {
        printf("Can't open file %s\n",argv[1]);
        return 2;
    }
    char *p;
    while (fgets(p,MAXLINE,fp)!=NULL) {
        printf("%s = ",p);
        printf("%ld\n",Compute_Value(&p,'\0'));
    }
    return 0;
}

int64_t Compute_Value(char **p,char endvalue)
{
    int64_t a=0,b=0;
    int filling_a=1,isBValid=0;
    char op='\0';
    while (**p != endvalue && **p != '\0') {
        if (isdigit(**p)) {
            if (filling_a==1) {
                a=getInt(p);
                filling_a=0;
            } else {
                b=getInt(p);
                isBValid=1;
            }
        } else if (**p=='(') {
            (*p)++;
            if (filling_a==1) {
                a=Compute_Value(p,')');
                filling_a=0;
            } else {
                b=Compute_Value(p,')');
                isBValid=1;
            }
        } else { //Found op
            if (isBValid) {
                a=calcOp(a,b,op);
                isBValid=0;
            }
            if (**p=='!')
                a=calcOp(a,b,**p);
            else {
                op=**p;
            }
        }
        (*p)++;
    }
    (*p)++;
    return isBValid ? calcOp(a,b,op) : a;
}

int64_t calcOp(int64_t a, int64_t b, char op)
{
    //One argument operators implemented on @a
    int64_t tmp;
    switch(op) {
    case '+':
        return a+b;
    case '*':
        return a*b;
    case '-':
        return a-b;
    case '/':
        return a/b;
    case '!':
        tmp=a-1;
        while (tmp>1) {
            a*=tmp;
            tmp--;
        }
        return a;
    case '^':
        return Power(a,b);
    case '\0':
    default:
        return a;
    }
}

int64_t getInt(char **n)
{
    int64_t num=0;
    while (isdigit(**n)) {
        num=10*num+**n-'0';
        (*n)++;
    }
    (*n)--;
    return num;
}
