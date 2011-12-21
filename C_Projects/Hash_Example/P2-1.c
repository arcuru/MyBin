/*
				P2-1.c - Data Structure Library					
<Your name here>   							<Date>
*/

#include <stdio.h>     
#include <stdlib.h>
#include "P2-1.h"

typedef struct NodeHeader {
	struct NodeHeader *next;
	struct NodeHeader *prev;
} NodeHeader;

typedef struct {
	NodeHeader *head;
	NodeHeader *tail;
	int (*Match)(void*, void*);
	int (*LE)(void*, void*);
	int ElementSize;
} ListHead;

//Create and return a pointer to a doubly linked list with elements of 
//size ElementSize in bytes. Match is a pointer to a function that 
//returns true (1) if (*key == MyElement->key) and false (0) if 
//(*key != MyElement->key), and LE is a pointer to a function that 
//returns true (1) if (MyElement1->key <= MyElement2->key) and false 
//(0) otherwise.
void *CreateLL(int ElementSize,int (*Match)(void *key, void *MyElement), int (*LE)(void *MyElement1, void *MyElement2))
{
	// Allocate dynamic memory for list head
	ListHead* list = (ListHead*)malloc(sizeof(ListHead));

	// Set list head defaults
	list->head = list->tail = NULL;
	list->Match = Match;
	list->LE = LE;
	list->ElementSize = ElementSize;

	return (void*)list;
}

//Return a pointer to an element for LL *MyList.
void *CreateElement(void *MyList)
{
	ListHead* list = (ListHead*) MyList;

	// Allocate Enough dynamic memory for Node
	NodeHeader* node = (NodeHeader*) malloc(sizeof(NodeHeader) + list->ElementSize);

	// Ensure pointers are NULL
	node->next = node->prev = NULL;

	// Return pointer to memory space for element
	return (void*)(node + 1);
}

//Delete and recover memory from element *MyElement.  DeleteElement 
//does not check that *MyElement is not a part of any linked list.
void DeleteElement(void *MyElement)
{
	// Free the memory of the element and associated NodeHeader
	// Use pointer arithmetic to determine the start of that memory block
	free(MyElement - sizeof(NodeHeader));
	return;
}

//Insert *MyElement at the head of linked list *MyList.
void InsertElement(void *MyList, void *MyElement)
{
	// Typecast
	ListHead* list = (ListHead*) MyList;
	NodeHeader* node = (NodeHeader*) MyElement;
	node--;

	// Insert at the head
	NodeHeader* tmp = list->head;
	node->prev = NULL; // Set to NULL instead of making a circular list
	node->next = tmp;

	// Change the prev value of the previous head
	if (NULL != tmp)
		tmp->prev = node;

	// Modify pointers from the list
	list->head = node;
	if (NULL == list->tail)
		list->tail = node;
}

// Insert *MyElement in sorted order in linked list *MyList. 
//MyElement->key should be less than or equal to the key of the next 
//element in the list.
void InsertElementSorted(void *MyList, void *MyElement)
{
	// Typecast
	ListHead* list = (ListHead*) MyList;
	NodeHeader* element = (NodeHeader*) MyElement;
	element--;

	// Walk the list
	NodeHeader* node;
	for (node = list->head; NULL != node; node = node->next) {
		if (!list->LE((void*)(node + 1), MyElement)) {
			// Insert before the current node
			element->prev = node->prev;
			element->next = node;
			node->prev = element;
			if (NULL != element->prev)
				element->prev->next = element;
			else // Head of list
				list->head = element;
			return;
		}
	}
	// Insert at beginning of empty list or at tail
	if (NULL == list->head) {
		list->head = element;
		element->next = NULL;
		element->prev = NULL;
		list->tail = element;
	}
	else { // List->tail guaranteed to be non NULL
		list->tail->next = element;
		element->prev = list->tail;
		element->next = NULL;
		list->tail = element;
	}
}

//Return a pointer to the first element in list *Mylist whose key 
//matches key.  If (Remove == True) (1), the returned element should 
//be removed from the list.
void *GetElement(void *MyList, void *key, int Remove)
{
	// Typecast
	ListHead* list = (ListHead*) MyList;

	// Walk the list
	NodeHeader* node;
	for (node = list->head; NULL != node; node = node->next) {
		if (list->Match(key, (void*)(node + 1))) {
			void* element = (void*)(node+1);
			if (Remove) {
				// Remove node from list
				if (NULL != node->prev)
					node->prev->next = node->next;
				else // Head of list
					list->head = node->next;
				if (NULL != node->next)
					node->next->prev = node->prev;
				else // Tail of list
					list->tail = node->prev;
			}
			return element;
		}
	}
	return NULL;
}
