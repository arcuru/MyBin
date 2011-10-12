#include <Euler.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
 * binsearch()
 * 	Searches a sorted list of length n for argument x
 */
static int64_t binsearch(int64_t x, int64_t list[], int n)
{
	int low, high, mid;
	low=0;
	high=n-1;
	while (low <= high) {
		mid = (low+high)/2;
		if (x < list[mid])
			high = mid-1;
		else if (x > list[mid])
			low = mid+1;
		else
			return mid;
	}
	return -1;
}

static void swap(char* a, char* b)
{
	if (*a==*b) return;
	(*a)^=(*b);
	(*b)^=(*a);
	(*a)^=(*b);
}

static const int max = 100000;//2642245;//Covers all cubes under 2^64
static int64_t *cubelist;
static int count=0;
static int64_t storedlist[10];


static void reverse(char s[])
{
	int i,j;
	char c;
	for (i=0,j=strlen(s)-1;i<j;i++,j--) {
		c=s[i];
		s[i]=s[j];
		s[j]=c;
	}
}

static void i64toa(int64_t n, char s[])
{
	int i=0;
	do {
		s[i++]=n%10+'0';
	} while ((n/=10) > 0);
	s[i]='\0';
	reverse(s);
}

static int a64toi(char s[])
{
	int i,n=0;
	for (i=0; s[i]>='0' && s[i]<='9'; ++i)
		n=10*n+(s[i]-'0');
	return n;
}

static void perm(char list[], int k, int length)
{
	if (k==length)
	{
		int64_t num = a64toi(list);
		if (binsearch(num,cubelist,max)!=-1) {
			int i=0;
			int skip=0;
			while (i < count)
				if (storedlist[i++]==num) {
					skip=1;
					break;
				}
			if (skip!=1) {
				storedlist[count]=num;
				count++;
			}
		}
	}
	else
	{
		int i;
		for (i=k;i<=length;i++) {
			swap(&list[k],&list[i]);
			perm(list,k+1,length);
			swap(&list[k],&list[i]);
		}
	}
}

int64_t Euler_62()
{
	return 0;
	cubelist = (int64_t *) malloc(sizeof(int64_t)*(max+1));
	int64_t i;
	char numstring[25];
	for (i=0;i<=max;i++)
		cubelist[i]=i*i*i;
	for (i=1000;i<=max;i++) {
		count=0;
		i64toa(i*i*i,numstring);
		printf("%jd\n",i);
		perm(numstring,0,strlen(numstring)-1);
		if (count==5)
			return i*i*i;
	}
	return 0;
}
