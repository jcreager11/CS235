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
	Set() : numItems(0), sCapacity(0), data(NULL) {}

	// copy constructor : copy it
	Set(const Set & rhs) throw (const char *);

	// non-default constructor : pre-allocate
	Set(int capacity) throw (const char *);

	// destructor : free everything
	~Set() { if (sCapacity) delete[] data; }

	// is the container currently empty
	bool empty() const { return numItems == 0; }

	// remove all the items from the container
	void clear() { numItems = 0; }

	// how many items are currently in the container?
	int size() const { return numItems; }

	// how large is the current array?
	int capacity() const { return sCapacity; }

	// add an item into the set
	void insert(const T item) const throw(const char *);

	// remove an element from the Set
	void erase(SetIterator <T> it) const throw(const char *);

	// try to find an item with in the set
	SetIterator <T> find(T item) const throw(const char *);

	// return an iterator to the beginning of the list
	SetIterator <T> begin() { return SetIterator<T>(data); }

	// return an iterator to the end of the list
	SetIterator <T> end() { return SetIterator<T>(data + numItems); }

	//SUB FUNCTIONS: create and load new array size
	void allocateAndInti() throw (const char *);
	void allocateAndInti(T * data) throw (const char *);
	void load(T * loadData);
	void load(T * loadInto, T * loadData);

	//OPERATORS
	// assignment operator
	Set<T>& operator=(const Set<T> &rhs) throw (const char *);
	// square bracket operator
	T& operator [](int index) throw (const char *);
	const T& operator [](int index) const throw (const char *);
	// intersection operator
	Set <T> operator &&(Set <T> rhs) const throw (const char *);
	// union operator
	Set <T> operator ||(Set <T> lhs, Set <T> rhs) const throw (const char *);


private:
	T * data;          // dynamically allocated array of T
	int numItems;      // how many items are currently in the Container?
	int sCapacity;      // how many items can I put on the Container before full?
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
	assert(rhs.sCapacity >= 0);

	// do nothing if there is nothing to do
	if (rhs.sCapacity == 0)
	{
		sCapacity = numItems = 0;
		data = NULL;
		return;
	}

	// copy over the capacity and size
	assert(rhs.numItems >= 0 && rhs.numItems <= rhs.sCapacity);
	sCapacity = rhs.sCapacity;
	numItems = rhs.numItems;
	data = NULL;

	allocateAndInti();

	load(rhs.data);
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
		this->sCapacity = this->numItems = 0;
		this->data = NULL;
		return;
	}

	// copy over the stuff
	this->sCapacity = capacity;
	this->numItems = 0;
	this->data = NULL;

	allocateAndInti();
}

/***********************************************************
* sub functions allocateAndInti and load
* handles intialization of data
************************************************************/
template<class T>
void Set<T>::allocateAndInti() throw (const char *)
{
	if (data != NULL)
	{
		delete[] data;
		data = NULL;
	}

	// attempt to allocate
	try
	{
		data = new T[sCapacity];
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate buffer";
	}

	// initialize the container by calling the default constructor
	for (int i = 0; i < sCapacity; i++)
		data[i] = T();
}
template<class T>
void Set<T>::allocateAndInti(T * data) throw (const char *)
{
	if (data != NULL)
	{
		delete[] data;
		data = NULL;
	}

	// attempt to allocate
	try
	{
		data = new T[sCapacity];
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate buffer";
	}

	// initialize the container by calling the default constructor
	for (int i = 0; i < sCapacity; i++)
		data[i] = T();
}
template<class T>
void Set<T>::load(T * loadData)
{
	// copy the items over one at a time using the assignment operator
	for (int i = 0; i < numItems; i++)
		data[i] = loadData[i];
}
template<class T>
void Set<T>::load(T * loadInto, T * loadData)
{
	// copy the items over one at a time using the assignment operator
	for (int i = 0; i < numItems; i++)
		loadInto[i] = loadData[i];
}

/***************************************************
* SET :: OPERATOR =
* Overridden Set class operators
**************************************************/
template<class T>
Set<T>& Set<T>::operator =(const Set<T> &rhs) throw (const char *)
{
	assert(rhs.sCapacity >= 0);

	// do nothing if there is nothing to do
	if (rhs.sCapacity == 0)
	{
		sCapacity = numItems = 0;
		data = NULL;
		return *this;
	}

	// copy over the capacity and size
	assert(rhs.numItems >= 0 && rhs.numItems <= rhs.sCapacity);
	if (sCapacity < rhs.capacity())
		sCapacity = rhs.sCapacity;
	numItems = rhs.numItems;

	allocateAndInti();

	load(rhs.data);
}

/***************************************************
* Set :: insert
* insert an item into the array
**************************************************/
template<class T>
void Set<T>::insert(const T item) const throw(const char *)
{
	try
	{
		// check for atiquit space to add an item
		bool changed = false;
		if (sCapacity <= 0)
		{
			sCapacity = 1;
			changed = true;
		}
		if (sCapacity <= numItems)
		{
			sCapacity = sCapacity * 2;
			changed = true;
		}
		if (changed)
		{
			Set<T> temp = Set<T>(*this);
			allocateAndInti();
			load(temp.data);
		}
		// is the item currently in the Set?
		// find correct location to insert
		SetIterator <T> it = find(item);
		if (!item == it)
		{
			// insert the item
			T next = item;
			for (SetIterator <T> i = it; it != end(); i++)
			{
				// shift the array by one
				T temp = i;
				i = next;
				next = temp;
			}
		}
	}
	catch (exception e)
	{
		throw "ERROR: Failed to insert element";
	}
}

/***************************************************
* Set :: erase
* remove an item from the array
**************************************************/
template<class T>
void Set<T>::erase(SetIterator <T> it) const throw(const char *)
{
	try
	{
		// search for the item
		T * foundIt = find(*it);
		// if found delete it
		if (foundIt == it)
		{
			// rearange the array
			T * previousItem = NULL;
			for (SetIterator <T> i = end(); i != it; i--)
			{
				T * temp = i;
				i = previousItem;
				previousItem = temp;
			}
		}
	}
	catch (exception e)
	{
		throw "ERROR: Failed to erase element";
	}
}

/***************************************************
* Set :: find
* try to find an item with in the set
**************************************************/
template<class T>
SetIterator <T> Set<T>::find(T item) const throw(const char *)
{
	int fBegin = 0;
	int fEnd = numItems;
	// start the search
	while (fBegin <= fEnd)
	{
		int fMid = (fBegin + fEnd) / 2;
		if (item = data[fMid])
			// if item is found return this element
			return SetIterator(data[fMid]);
		if (item < data[fMid])
			fEnd = fMid - 1;
		else
			fBegin = fMid + 1;
	}
	// if item was not found return last element
	return SetIterator <T> (data[numItems]);
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
inline Set<T> Set<T>::operator&&(Set<T> rhs) const throw(const char *)
{
	Set <T> intersection = new Set <T>();
	for (SetIterator <T> it = begin(); it != end(); it++)
	{
		if (it == rhsit.find(*it))
		{
			T temp = *it;
			intersection.insert(temp);
		}
	}
	return intersection;
}
template<class T>
inline Set<T> Set<T>::operator||(Set<T> lhs, Set<T> rhs) const throw(const char *)
{
	Set <T> unionSet = lhs;
	for (SetIterator <T> it = rhs.begin(); it != rhs.end(); it++)
	{
		unionSet.insert(*it);
	}
	return unionSet;
}
#endif