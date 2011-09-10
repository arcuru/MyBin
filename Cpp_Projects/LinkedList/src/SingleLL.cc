#include "SingleLL.h"
#include <cstdlib>

#define DEBUG
#ifdef DEBUG
	#include <iostream>
	using namespace std;
#endif

#ifndef NULL
	#define NULL 0
#endif

typedef struct sll_t {
	void* data;
	sll_t* next;
} sll_t;

/*
 *--------------------------------------------------------------------------------------
 *       Class:  SingleLL
 *      Method:  SingleLL
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
SingleLL::SingleLL ( queue_type init ) : LinkedList(init)
{
	head = NULL;
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  SingleLL
 *      Method:  SingleLL
 * Description:  copy constructor
 *--------------------------------------------------------------------------------------
 */
SingleLL::SingleLL ( const SingleLL &other ) : LinkedList(other)
{
	head = NULL;
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  SingleLL
 *      Method:  ~SingleLL
 * Description:  destructor
 *--------------------------------------------------------------------------------------
 */
SingleLL::~SingleLL ()
{
	if ( NULL != head ) {
		sll_t* tmp = head;
		while ( NULL != tmp->next ) {
			tmp = tmp->next;
			free(head);
			head = tmp;
		}
		free(head);
	}
}

void SingleLL::PushFront ( void* info )
{
	length++;
	sll_t* tmp = head;
	head = (sll_t*) malloc(sizeof(sll_t));
	if ( NULL == head ) {
#ifdef DEBUG
		cout << "Failed to allocate dynamic memory" << endl;
#endif
		return ;
	}
	head->data = info;
	head->next = tmp;
	return ;
}

void SingleLL::PushBack ( void* info )
{
	length++;
	if ( NULL == head )
		return PushFront(info);
	sll_t* tmp = head;
	while ( NULL == tmp->next )
		tmp = tmp->next;
	tmp->next = (sll_t*) malloc(sizeof(sll_t));
	if ( NULL == tmp->next ) {
#ifdef DEBUG
		cout << "Failed to allocate dynamic memory" << endl;
#endif
		return ;
	}
	tmp->next->data = info;
	tmp->next->next = NULL;
	return ;
}

void* SingleLL::PopFront ( )
{
	if ( NULL == head )
		return NULL;
	length--;
	void* out = head->data;
	free(head);
	head = head->next;
	return out;
}

void* SingleLL::PopBack ( )
{
	if ( NULL == head )
		return NULL;
	length--;
	sll_t* tmp = head;	
	if ( NULL == tmp->next) {
		void* out = tmp->data;
		free(head);
		head = NULL;
		return out;
	}
	while ( NULL != tmp->next->next)
		tmp = tmp->next;
	void* out = tmp->next->data;
	free(tmp->next);
	tmp->next = NULL;
	return out;
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  SingleLL
 *      Method:  operator =
 * Description:  assignment operator
 *--------------------------------------------------------------------------------------
 */
SingleLL& SingleLL::operator = ( const SingleLL &other )
{
	if ( this != &other ) {
		this->head = other.head;
	}
	return *this;
}

