/**************************************************************************************************
* LIST.H: Contains the definitions and classes of our list
*
* Authors:
*
*
*
*
*
*************************************************************************************************/

#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <cassert>

using namespace std;

/**********************************************
* NODE Class
**********************************************/
template <class T>
class node
{
public:
	T data;
	node <T> *pNext;
	node <T> *pPrev;
};

/***************************************************
* List Container Iterator
***************************************************/
template <class T>
class ListIterator
{
public:
	//default Constructor
	ListIterator() : p(NULL) {}

	//initialize to direct p to some item
	ListIterator(node <T> *p) : p(p) {}

	//Copy constructor
	ListIterator(const ListIterator &rhs) { *this = rhs; }

	//Assignment operator
	ListIterator & operator = (const ListIterator & rhs)
	{
		this->p = rhs.p;
		return *this;
	}

	//is equal operator
	bool operator == (const ListIterator & rhs) const
	{
		return rhs.p == this->p;
	}

	//Find Items
	ListIterator <T> find(T finditems) throw (const char *);

	//not equals operator
	bool operator != (const ListIterator & rhs) const
	{
		return rhs.p != this->p;
	}

	//dereference operator
	T & operator * ()
	{
		return p->data;
	}

	//prefix increment
	ListIterator <T> & operator ++ ()
	{
		p = p->pNext;
		return *this;
	}

	//Postfix increment
	ListIterator <T> operator ++ (int postfix)
	{
		ListIterator tmp(*this);
		p = p->pNext;
		return tmp;
	}

	// prefix increment
	ListIterator <T> & operator -- ()
	{
		p = p->pPrev;
		return *this;
	}

	// postfix increment
	ListIterator <T> operator--(int postfix)
	{
		ListIterator tmp(*this);
		p = p->pPrev;
		return tmp;
	}

	node <T> *p;
};

/********************************************
* List Class
*********************************************/
template <class T>
class List
{
public:
	node <T> *head;
	node <T> *tail;
	int Size;

	//default constructor 
	List() : head(NULL), tail(NULL), Size(0) {}

	//copy constructor 
	List(const List <T> & rhs) throw (const char*);

	//returns the Size
	int size() { return Size; }

	// Checks if the list is empty
	bool empty()
	{
		if (Size == 0)
			return true;
		else
			return false;
	}

	//Clear
	void clear();

	//pushes items at the end of the linked list
	void push_back(T item) throw (const char*);

	//pushes item at the beginning of the linked list
	void push_front(T item) throw (const char *);

	List <T> & operator = (List <T> & rhs) throw (const char*);

	//returns current item at from of the list
	T & front()
	{
		if (head != NULL)
			return head->data;
		else
			throw "ERROR: Unable to access data from an empty list";
	}

	//Returns current item at the end of list
	T & back()
	{
		if (tail != NULL)
			return tail->data;
		else
			throw "ERROR: unable to access data from an empty list";
	}

	ListIterator <T> insert(ListIterator <T> it, T item) throw (const char *);
	ListIterator <T> remove(ListIterator <T> it) throw (const char *);

	ListIterator <T> rbegin();
	ListIterator <T> begin();
	ListIterator <T> end();
	ListIterator <T> rend();

};


/***************************************
* Pushes back
***************************************/
template <class T>
List <T> ::List(const List <T> & copy) throw (const char *)
{
	head = NULL;
	tail = NULL;
	Size = 0;

	node <T> *pHead = copy.head;
	while (pHead != NULL)
	{
		push_back(pHead->data);
		pHead = pHead->pNext;
	}
}

/****************************************
* Pushes back
****************************************/
template <class T>
void List <T> ::push_back(T item) throw (const char*)
{
		node <T> *newnode = new node<T>;
		newnode->data = item;
   
		if (empty())
		{
			head = newnode;
			head->pPrev = NULL;
			head->pNext = NULL;
			tail = newnode;
			Size++;
		}
		else
		{
			tail->pNext = newnode;
			newnode->pPrev = tail;
			newnode->pNext = NULL;
			tail = newnode;
			Size++;
		}
}

/********************************************
* pushes front
********************************************/
template <class T>
void List <T> ::push_front(T item) throw (const char*)
{
	try
	{
		node <T> *newnode = new node<T>;
		newnode->data = item;
   
		if (empty())
		{
			head = newnode;
			head->pPrev = NULL;
			head->pNext = NULL;
			tail = newnode;
			Size++;
		}
		else
		{
			head->pPrev = newnode;
			newnode->pNext = head;
			head = newnode;
			Size++;
		}
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: unable to allocate a new node for a list";
	}
}

/***********************************
* Assingment Operator
***********************************/
template <class T>
List<T> & List <T> :: operator = (List<T> &rhs) throw (const char*)
{
	//this->clear();
	//node <T> *temp = rhs.head;
 /*
	while (temp != NULL)
	{
		node <T> *p = temp;
    
    //if (temp->dat
		//this->push_back(temp->data);
		temp = temp->pNext;
	}
 */
 	head = NULL;
	tail = NULL;
	Size = 0;

	node <T> *pHead = rhs.head;
	while (pHead != NULL)
	{
		push_back(pHead->data);
		pHead = pHead->pNext;
	}
 
	return *this;
}

/*************************************
* Inserts in the middle of the list
*************************************/
template <class T>
ListIterator <T> List <T> ::insert(ListIterator <T>  it, T item) throw (const char*)
{
	try
	{
		node <T>* temp = new node<T>;
		temp->data = item;
		if (empty()) // if(head == 0);
		{
			head = temp;
			tail = temp;
		}
		else if (it == end())  // inseert at end of list
		{
			push_back(item);
		}
		else if (it == begin())
		{
			push_front(item);

		}
		else  //
		{
			temp->pNext = it.p;
			temp->pPrev = it.p->pPrev;
			temp->pPrev->pNext = temp;
			temp->pNext->pPrev = temp;

		}

		return ListIterator<T>(temp);
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: unable to allocate a new node for a list";
	}

}

/***********************************
* Clears
***********************************/
template <class T>
void List <T> ::clear()
{
	node <T> *temp = head->pNext;
	while (temp)
	{
		delete head;
		head = temp;
		temp = head->pNext;
	}
	delete head;
	head = NULL;
	tail = NULL;
	Size = 0;
}

/**************************************
* Removes an itme form the lsit
***************************************/
template <class T>
ListIterator <T> List <T> ::remove(ListIterator <T> it) throw (const char*)
{
	if (it == end())
	{
		throw "ERROR: unable to remove from an invalid location in a list ";
	}
	else if (it == begin())
	{
		node<T> *temp = head->pNext;
		delete head;
		head = temp;
		head->pPrev = NULL;
	}
	else if (it == rbegin())
	{
		node<T> *temp = tail->pPrev;
		delete tail;
		tail = temp;
		tail->pNext = NULL;
	}
	else
	{
		it.p->pPrev->pNext = it.p->pNext;
		it.p->pNext->pPrev = it.p->pPrev;
		delete it.p;
	}

}

/*************************************
* begin
*************************************/
template <class T>
ListIterator <T> List <T> ::begin()
{
	ListIterator <T> newIterator(head);
	return newIterator;
}

/*************************
* rbegin
***************************/
template <class T>
ListIterator <T> List <T> ::rbegin()
{
	ListIterator <T> newIterator(tail);
	return newIterator;

}

/*******************************
* end
*********************************/
template <class T>
ListIterator <T> List <T> ::end()
{
	ListIterator <T> newIterator;
	return newIterator;
}

/********************************
* rend
********************************/
template <class T>
ListIterator <T> List <T> ::rend()
{
	ListIterator <T> newIterator;
	return newIterator;
}

#endif
