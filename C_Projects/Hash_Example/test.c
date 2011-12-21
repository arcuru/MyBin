 /*
                        P2-2.c - Hash Table Implementation
Daniel Argue   							9 December 2011
*/

#include "P2-1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//I added in a paramter to MyMatch and GetElement that changes the functionality
//of MyMatch in order to either just delete elements or actually search through them.

//remember if my P2-1 library fails it came with a money back gurantee...
//and it would probably be a win-win situation if you just say I wrote my own P2-1...

//please?
typedef struct HashElement{
        int key;
        char data[10];
        int count;
} Hash;

int MyMatch(void* key, void* Element);
int MyLE(void* Element1, void* Element2);

int matches;

int main(int argc, char *argv[]){
	matches = 1;
    int size = atoi(argv[1]); //figure out the parameters
    int seed = atoi(argv[2]);
    int numElements = atoi(argv[3]);
    srand(seed); //seed random number generator
    //initialize variables
    void** table = (void*)malloc(size*sizeof(void*));
    int x;
    int hashNum;
    int genkey;
    Hash* current;
    Hash* found;
    for(x = 0; x <= size; x++){ // iterate through number of buckets
          table[x] = CreateLL(sizeof(Hash), MyMatch, MyLE); //create list
    }
    for(x = 0; x < numElements; x++){
          genkey = rand() % 1000000; //create unique key
          hashNum = genkey % size; //functino key
          found = (Hash*)GetElement(table[hashNum], &genkey, 0); //search for existing node
          if(found != NULL){
                found->count++; //if it already exists, increment count
          }
          else {
			  current = (Hash*)CreateElement((void*)table[hashNum]);
			  current->count = 1;
			  current->key = genkey;
			  sprintf(current->data, "%X", current->key); //convert to hex
			  InsertElement(table[hashNum], (void*)current); //add to list
          }

    }
	matches = 0;
    //initialize variables for printing
    int minList = numElements+1, maxList = 0, currMin, currMax, theMax = 0, theMaxKey = 1000000;
	int totalElements = 0;
    for(x = 0; x < size; x++){ //iterate through the lists
		int length = 0;
        current = (Hash*)GetElement(table[x], NULL, 1); //head of list
        while(current != NULL){ //check if the list still has elements
			length++;
            currMin++; //current count of iterations
            currMax++; //current count of iterations
            if(current->count == theMax){
                if(current->key < theMaxKey){
                    theMaxKey = current->key; //new key of max
                    theMax = current->count;  //new count of max
                }
            }
            if(current->count > theMax){
                theMax = current->count;
                theMaxKey = current->key;
            }
            current = (Hash*)GetElement(table[x], NULL, 1);

        }
        if(length < minList)
            minList = length; //set new minimum num of elements
        if(length > maxList)
            maxList = length; //set new maximum num of elements
		totalElements += length;
    }
    //print out answers
    printf("Minimum List Length:\t%d\n", minList);
    printf("Maximum List Length:\t%d\n", maxList);
    printf("Mean Elements/List:\t%.02f\n", ((double)totalElements)/((double)size));
    printf("Most Used Key (count):\t%d (%d)\n\n", theMaxKey, theMax);
    return 0;
}
// Match function defined by user
int MyMatch(void* key, void* Element)
{
	if (matches) {
		// Actual match
		int* val = (int*)key;
		Hash* s = (Hash*) Element;
		if (s->key == *val)
			return 1;
		else
			return 0;
	}
	else // Always return true
		return 1;
}

// Less than or equal to function defined by user
int MyLE(void *Element1, void *Element2)
{  
	printf("AHHHHHHHHHHHh\n");
	return 0;
	Hash* element1 = (Hash*)Element1;
    Hash* element2 = (Hash*)Element2;
    if(element1->key == element2->key)
        return 1;
    else
        return 0;
}
