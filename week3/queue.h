#pragma once
/*********************************************************************
* Header:
*    queue.h
* Summary:
*     File contains queue class
* Author:
*
*
*
*
***********************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <cassert>
using namespace std;

/*************************************************************
* Queue Class
* Defines all the things we need
*************************************************************/
template <class T>
class Queue
{
public:
	//default constructor
	Queue() : items(0), cap(0), myback(0), myfront(0), data(NULL) {}

	// copy constructor : copy it
	Queue(const Queue & rhs) throw (const char *);

	// non-default constructor : pre-allocate
	Queue(int cap) throw (const char *);


	// destructor : free everything
	~Queue() { if (cap) delete[] data; }


	// assignment operator
	Queue & operator = (const Queue & rhs) throw (const char *);


	// Vcapasity
	int capacity() { return cap; }

	// is the container currently empty
	bool empty() const { return items == 0; }

	// is the container currently full
	bool full() const
	{
		if (items == cap)
			return true;
		else
			return false;
	}

	// remove all the items from the container
	void clear() { items = 0; }

	// how many items are currently in the container?
	int size() const { return items; }

	void allocate() throw (const char *);
	void push(T additem) throw (const char *);
	void pop() throw (const char *);
	T top() throw (const char *);
	T & front()  throw (const char *)
	{
		if (empty())
		{
			throw  "ERROR: attempting to access an item in an empty queue";
		}
		else
			return data[myfront];
	}
	T & back() throw (const char *)
	{
		if (empty())
		{
			throw  "ERROR: attempting to access an item in an empty queue";
		}
		else
			return data[myback];
	}

private:
	int myback;
	int myfront;
	int items;
	int cap;
	T * data;
};


/**********************************************************
* Queue: Copy Consructor
*
*********************************************************/
template <class T>
Queue <T> ::Queue(const Queue <T> & rhs) throw (const char *)
{
	assert(rhs.cap >= 0);

	// do nothing if there is nothing to do
	if (rhs.cap == 0)
	{
		cap = items = 0;
		data = NULL;
		myfront = 0;
		myback = 0;
		return;
	}

	// attempt to allocate
	try
	{
		data = new T[rhs.cap];
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate buffer";
	}

	// copy over the vcapacity and size
	assert(rhs.items >= 0 && rhs.items <= rhs.cap);
	cap = rhs.cap;
	items = rhs.items;
	myfront = rhs.myfront;
	myback = rhs.myback;

	// copy the items over one at a time using the assignment operator
	for (int i = 0; i < cap; i++)
		data[i] = rhs.data[i];

}

/**********************************************************************
* Queue: Non-Default constructor
*
*********************************************************************/
template <class T>
Queue <T> ::Queue(int cap) throw (const char *)
{
	assert(cap >= 0);

	// do nothing if there is nothing to do
	if (cap == 0)
	{
		this->cap = this->items = 0;
		this->data = NULL;
		this->myfront = 0;
		this->myback = 0;
		return;
	}

	// attempt to allocate
	try
	{
		data = new T[cap];
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate buffer";
	}


	// copy over the stuff
	this->cap = cap;
	this->items = 0;
	this->myfront = 0;
	this->myback = 0;

	// initialize the container by calling the default constructor
	for (int i = 0; i < cap; i++)
		data[i] = T();
}

/*******************************************
* Queue:  OPERATOR
* COPYS DATA FROM ONE VECTOR TO OTHER..
*******************************************/
template <class T>
Queue<T> & Queue <T> :: operator =(const Queue <T> & rhs) throw (const char *)
{
	assert(rhs.cap >= 0);

	// do nothing if there is nothing to do
	if (rhs.cap == 0)
	{
		cap = items = 0;
		data = NULL;
		myfront = 0;
		myback = 0;
		return *this;
	}
	if (data != NULL)
		delete[] data;
	// attempt to allocate
	try
	{
		data = new T[rhs.cap];
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate buffer";
	}

	// copy over the vcapacity and size
	assert(rhs.items >= 0 && rhs.items <= rhs.cap);
	cap = rhs.cap;
	items = rhs.items;
	myfront = rhs.myfront;
	myback = rhs.myback;

	// copy the items over one at a time using the assignment operator
	for (int i = 0; i < cap; i++)
		data[i] = rhs.data[i];

	return *this;
}

/****************************************************
* Queue: Allocate
* doubles the memory when needed
*************************************************/
template <class T>
void Queue <T> ::allocate()  throw (const char *)
{
	int tempcap = cap;
	if (cap == 0)
	{
		cap = 1;
	}
	else
	{
		cap *= 2;
	}
	T * temp = new T[cap];
	int j = myfront;
	for (int i = 0; i<items; i++, j = (j + 1) % tempcap)
	{
		temp[i] = data[j];
	}

	delete[] data;
	data = temp;
	myfront = 0;
	myback = items;
}

/***************************************************
* Queue: push
* pushes the item back to a new location
**************************************************/
template <class T>
void Queue <T> ::push(T additem)  throw (const char *)
{

	if (items >= cap)
	{
		allocate();
	}

	data[myback] = additem;
	myback = (myback + 1) % cap;
	items++;
	return;
}



/***********************************************
* Queue: pop
* pop removes first item from the stack
*************************************************/
template <class T>
void Queue <T> ::pop() throw (const char *)
{
	if (items > 0)
	{
		myfront = (myfront + 1) % cap;
		items--;
	}
	else
	{
		throw "ERROR: attempting to pop from an empty queue";
	}
}

/***********************************************
* Queue: Top
* top return the top item in the queue
************************************************/
template <class T>
T  Queue <T> ::top() throw (const char *)
{
	if (empty())
	{
		throw  "ERROR: Unable to reference the element from an empty Stack";
	}
	else
		return data[myfront];
}


#endif //QUEUE_H
