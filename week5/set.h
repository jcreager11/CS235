#pragma once
/*************************************************************************
* Header:
*   Deque Class and definitions
* Summary:
*
* Authors:
*
******************************************************************************/

#ifndef SET_H
#define SET_H

#include <iostream>
#include <cassert>
using namespace std;

// forward declaration for ContainerIterator
template <class T>
class SetIterator;

/************************************************
* SET
* A class that holds unique stuffs
***********************************************/
template <class T>
class Set
{
public:
	// default constructor : empty and kinda useless
	Set() : numItems(0), cap(0), data(NULL) {}

	// copy constructor : copy it
	Set(const Set & rhs) throw (const char *);

	// non-default constructor : pre-allocate
	Set(int capacity) throw (const char *);

	// destructor : free everything
	~Set() { if (cap) delete[] data; }

	// is the container currently empty
	bool empty() const { return numItems == 0; }

	// remove all the items from the container
	void clear() { numItems = 0; }

	// how many items are currently in the container?
	int size() const { return numItems; }

	// how large is the current array?
	int capacity() const { return cap; }

	// add an item into the set
	void insert(const T item) throw(const char *);

	// remove an element from the Set
	void erase(SetIterator <T> it) throw(const char *);

	// try to find an item with in the set
	SetIterator <T> find(T item) throw(const char *);

	// return an iterator to the beginning of the list
	SetIterator <T> begin() { return SetIterator<T>(data); }

	// return an iterator to the end of the list
	SetIterator <T> end() { return SetIterator<T>(data + numItems); }

	//SUB FUNCTIONS: create and load new array size
	void allocate() throw (const char *);

	//OPERATORS
	// assignment operator
	Set<T>& operator=(const Set<T> &rhs) throw (const char *);
	// square bracket operator
	T& operator [](int index) throw (const char *);
	const T& operator [](int index) const throw (const char *);
	// intersection operator
	Set <T> operator &&(Set <T> rhs) throw (const char *);
	// union operator
	Set <T> operator ||(Set <T> rhs) throw (const char *);


private:
	T * data;          // dynamically allocated array of T
	int numItems;      // how many items are currently in the Container?
	int cap;      // how many items can I put on the Container before full?
};

/**************************************************
* CONTAINER ITERATOR
* An iterator through Container
*************************************************/
template <class T>
class SetIterator
{
public:
	// default constructor
	SetIterator() : p(NULL) {}

	// initialize to direct p to some item
	SetIterator(T * p) : p(p) {}

	// copy constructor
	SetIterator(const SetIterator & rhs) { *this = rhs; }

	// assignment operator
	SetIterator & operator = (const SetIterator & rhs)
	{
		this->p = rhs.p;
		return *this;
	}

	// not equals operator
	bool operator != (const SetIterator & rhs) const
	{
		return rhs.p != this->p;
	}

	// dereference operator
	T & operator * ()
	{
		return *p;
	}

	// prefix increment
	SetIterator <T> & operator ++ ()
	{
		p++;
		return *this;
	}

	// postfix increment
	SetIterator <T> operator++(int postfix)
	{
		SetIterator tmp(*this);
		p++;
		return tmp;
	}

private:
	T * p;
};

/*******************************************
* CONTAINER :: COPY CONSTRUCTOR
*******************************************/
template <class T>
Set <T> ::Set(const Set <T> & rhs) throw (const char *)
{
  assert(rhs.cap >= 0);

	// do nothing if there is nothing to do
	if (rhs.cap == 0)
	{
		cap = numItems = 0;
		data = NULL;
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
	assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
	cap = rhs.cap;
	numItems = rhs.numItems;

	// copy the items over one at a time using the assignment operator
	for (int i = 0; i < numItems; i++)
		data[i] = rhs.data[i];
}

/**********************************************
* CONTAINER : NON-DEFAULT CONSTRUCTOR
* Preallocate the container to "capacity"
**********************************************/
template <class T>
Set <T> ::Set(int capacity) throw (const char *)
{
	assert(capacity >= 0);

	// do nothing if there is nothing to do
	if (capacity == 0)
	{
		this->cap = this->numItems = 0;
		this->data = NULL;
		return;
	}

	// copy over the stuff
	this->cap = capacity;
	this->numItems = 0;
	this->data = NULL;

	allocate();
}

template<class T>
void Set<T>::allocate() throw (const char *)
{ 
  if (numItems < cap)
    return;
    
  if (cap == 0)
  {
		cap = 1;
    data = new T[cap];
  }
	else
  {
		cap *= 2;
 
	  T* temp = new T[cap];
 
	  for (int i = 0; i < numItems; i++)
	  {
		  temp[i] = data[i];
	  }

	  delete[] data;
	  data = temp;
  }
}

/***************************************************
* SET :: OPERATOR =
* Overridden Set class operators
**************************************************/
template<class T>
Set<T>& Set<T>::operator =(const Set<T> &rhs) throw (const char *)
{
  assert(rhs.cap >= 0);

	// do nothing if there is nothing to do
	if (rhs.cap == 0)
	{
		cap = numItems = 0;
		data = NULL;
    return *this;
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
	assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
	cap = rhs.cap;
	numItems = rhs.numItems;

	// copy the items over one at a time using the assignment operator
	for (int i = 0; i < numItems; i++)
		data[i] = rhs.data[i];
   
  return *this;
}

/***************************************************
* Set :: insert
* insert an item into the array
**************************************************/
template<class T>
void Set<T>::insert(const T item) throw(const char *)
{
  allocate();

  SetIterator <T> it = find(item);

  if (*it == item) //if a duplicate is not in the set
    return;
    
  if (numItems == 0)
  {
    data[0] = item;
    numItems++;
    return;
  }
  
  T last;
  bool up = false;

  for (int i = 0; i <= numItems; i++)
  { 
    if (up)
    {
      T temp = data[i];
      data[i] = last;
      last = temp;
    }
    else if (data[i] > item && !up)
    {
      last = data[i];
      data[i] = item;
      up = true; //push items up
    }
    else if (i == numItems && !up)
    {
      data[i] = item;
    }
	}
 
  numItems++;
}

/***************************************************
* Set :: erase
* remove an item from the array
**************************************************/
template<class T>
void Set<T>::erase(SetIterator <T> it) throw(const char *)
{
  T remObj = *it;
  bool replace = false;
  
  for (int i = 0; i < numItems; i++)
  {
    if (data[i] == remObj)
    {
      replace = true;
      numItems--;
    }
    
    if (replace)
      data[i] = data[i + 1];
  }
}

/***************************************************
* Set :: find
* try to find an item with in the set
**************************************************/
template<class T>
SetIterator <T> Set<T>::find(T item) throw(const char *)
{  
  for (SetIterator <T> it = begin(); it != end(); it++)
  {
    if (*it == item)
      return it;
  }
  
	return SetIterator <T> (end());
}

/***************************************************
* Set :: Operators
* overriden operators for the Set class
****************************************************/
template<class T>
T& Set<T>::operator [](int index) throw (const char *)
{
	if (index >= 0 || index < numItems)
		return data[index];
	else
		throw "ERROR: Invalid index";
}

template<class T>
const T& Set<T>::operator [](int index) const throw (const char *)
{
	if (index >= 0 || index < numItems)
		return data[index];
	else
		throw "ERROR: Invalid index";
}

template<class T>
Set<T> Set<T>::operator&&(Set<T> rhs) throw(const char *)
{
  Set<T> set3;

  for (int i = 0; i < numItems; i++)
  {
    for (int j = 0; j < rhs.numItems; j++)
    {
      T objA = data[i];
      T objB = rhs.data[j];
      
      if (objA == objB)
      {
        set3.insert(objA);
      }
    }
  }
  
  return set3;
}

template<class T>
Set<T> Set<T>::operator||(Set<T> rhs) throw(const char *)
{
  Set<T> set3;

  for (int i = 0; i < numItems; i++)
  {
    set3.insert(data[i]);
  }
  
  for (int i = 0; i < rhs.numItems; i++)
  {
    set3.insert(rhs.data[i]);
  }

  return set3;
}
#endif