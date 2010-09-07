/*
 *  hash-map-chaining.c - Daniel "bodom_lx" Graziotin <http://daniel.graziotin.net>
 *      An implementation in C of search and insertion operations for a hash table with linear probing
 *  compile with: gcc -lm hash-map-chaining.c
 */

#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

#define TRUE 1
#define FALSE !TRUE
#define SIZE_HASH_MAP 10
#define HASH_CONSTANT ((sqrt(5) - 1) / 2)

typedef struct node{
    int value;
    struct node *next;
}t_hashTableNode;

static t_hashTableNode* hashMapChained[SIZE_HASH_MAP];              // hash table
/* HASH FUNCTIONS */
int hash(int value);                                                /* hash function */
void chainedHashInsert(int value);                                  /* inserts a value in the hash table, using chaining */
int chainedHashSearch(int value);                                   /* searches for a value in the hash table */
/* AUXILIARY FUNCTIONS */
void populateHashMap(int numbersToBeGenerated);                     /* AUX: inserts random integer numbers in the hash table */
void printList(int i);                                              /* AUX: prints the linked list stored in hashMapChained[i] */
void printHashMap();                                                /* AUX: prints the whole hash hashMapChained */
void searchNumbers(int numbersToBeSearched);                        /* AUX: searches random numbers in the hash map */

/* HASH FUNCTIONS */
int hash(int value){
    return (SIZE_HASH_MAP * fmod((value * HASH_CONSTANT),1));
}

void chainedHashInsert(int value){
    int probe = hash(value);                                        // stores the hash value of the number to be inserted
    if(hashMapChained[probe] == NULL){                              // if the list in hashMapChained[probe] is empty
        hashMapChained[probe] = malloc(sizeof(t_hashTableNode));    // then creates a new list
        hashMapChained[probe]->value = value;
        hashMapChained[probe]->next = NULL;
    }else{                                                          // if the list in hashMapChained[probe] is not empty
        t_hashTableNode *hashTableNode = hashMapChained[probe];
        while(hashTableNode->next!=NULL){                           // scrolls down the list
            hashTableNode = hashTableNode->next;
        }
        hashTableNode->next = malloc(sizeof(t_hashTableNode));      // inserst the value as the last element of the list
        hashTableNode->next->value = value;
        hashTableNode->next->next = NULL;
    }
}

int chainedHashSearch(int value){
    t_hashTableNode *hashTableNode = hashMapChained[hash(value)];   // pointer to the list stored in hashMapChained[hash(value)]
    while(hashTableNode!=NULL){                                     // scrolls the list
        if(hashTableNode->value==value){
            return TRUE;                                            // if the value is found, returns TRUE
        }
        hashTableNode = hashTableNode->next;
    }
    return FALSE;                                                   // else returns FALSE
}

/* MAIN FUNCTION */
int main (int argc, char const *argv[]){
    srand(time(NULL));
    populateHashMap(25);
    printf("\nsituation after insertion of random integers:\n");
    printHashMap();
    printf("\nsearch of some random integers:\n");
    searchNumbers(10);
}


/* AUXILIARY FUNCTIONS */
void populateHashMap(int numbersToBeGenerated){                     // generates random numbers
    int k = 1;
    int randomNumber;
    for(k=1;k<=numbersToBeGenerated;k++){
        randomNumber = rand() % 100 + 1; 
        chainedHashInsert(randomNumber);                            // inserts them in the hash map
    }
}

void printList(int hashMapRow){
    t_hashTableNode *hashMapNode = hashMapChained[hashMapRow];      // pointer to the linked list stored in hashMapChained[hashMapRow]
    while(hashMapNode!=NULL){
        printf("%d ",hashMapNode->value);                           // prints out the value of the nodes
        hashMapNode = hashMapNode->next;
    }
}

void printHashMap(){                                            
    int i;
    for(i=0;i<SIZE_HASH_MAP;i++){                                   // for every row of the hash map
        printf("hashMapChained[%d]:\t",i);  
        printList(i);                                               // prints the list contained in it
        printf("\n");
    }
}

void searchNumbers(int numbersToBeSearched){
    int k;
    int randomNumber;
    for(k=1;k<=numbersToBeSearched;k++){                            // searches a random number (from 1 to 100) numbersToBeSearched times
        randomNumber = rand() % 100 + 1; 
        printf("Is the value %d present? %d\n",randomNumber,chainedHashSearch(randomNumber));
    }
}
