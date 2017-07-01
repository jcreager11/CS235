/***********************************************************************
* Header:
*    NODE
* Summary:
*    This will provide the function of a singly linked list to our program.
* Author
*    <your names here>
************************************************************************/

#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <string>
using namespace std;

/***********************************************
* Node
* The representation of a linked list
**********************************************/
template <class T>
class Node
{
public:
	T data;
	Node <T> * pNext;

	// constructors
	Node() { pNext = NULL;};
	Node(T data) 
	{
		this->data = data;
		this->pNext = NULL;
	};
};


/***********************************************
* NON-Member Function
* COPY: provides the user with the function
*       of returning a copy of a given linked
*       list
**********************************************/
template<class T>
Node<T>* copy(Node<T> * n)
{
	Node<T> * c = new Node<T>();
	Node<T> * l = c;
  l->data = n->data;
  
	while (n = n->pNext)
  {
    l->pNext = new Node<T>();
    l = l->pNext;
    l->data = n->data;    
	}
 
	return c;
}

/***********************************************
* NON-Member Function
* INSERT: provides the user with the function
*       of inserting a new Node into the linked
*       list
**********************************************/
template<class T>
void insert(T data, Node<T> * & p)
{
  if (p == NULL)
	  p = new Node<T>(data);
  else if (p->pNext == NULL)
    p->pNext = new Node<T>(data);
  else
  {
    for (Node<T> * next = p->pNext; next; next = next->pNext)
    {
      T temp = next->data;
      next->data = data;
      data = temp;
      T def; //default for T
      
      if (data != def && next->pNext == NULL)
        next->pNext = new Node<T>();
    }  
  }
}

template<class T>
void insert(T data, Node<T> * & p, bool atHead)
{
	if (atHead)
  {
    if (p == NULL)
      p = new Node<T>(data);
    else
    {
      for (Node<T> * next = p; next; next = next->pNext)
      {
        T temp = next->data;
        next->data = data;
        data = temp;
        T def; //default for T
      
        if (data != def && next->pNext == NULL)
          next->pNext = new Node<T>();
      }
    }
  }
}

/***********************************************
* NON-Member Function
* FIND: provides the user with the function
*       of returning a copy of a given linked
*       list
**********************************************/
template<class T>
Node<T> * find(Node<T> * pHead, T dataToFind)
{
	for (Node<T> * p = pHead; p; p = p->pNext)
	{
		if (p->data == dataToFind)
			return p;
	}
 
	return NULL;
}

/***********************************************
* NON-Member Function
* OPERATOR <<: provides the user with the function
*       of printing the data of a given linked
*       list
**********************************************/
template<class T>
std::ostream & operator << (std::ostream & out, Node<T> * rhs)
{
	for (Node<T> * p = rhs; p; p = p->pNext)
	{
		out << p->data;
	}
 
  return out;
}

template<>
std::ostream & operator << <char>(std::ostream & out, Node<char> * rhs)
{
	for (Node<char> * p = rhs; p; p = p->pNext)
	{
		out << p->data;
   
    if (p->pNext != NULL)
      out << ", ";
	}
 
  return out;
}

template<>
std::ostream & operator << <string>(std::ostream & out, Node<string> * rhs)
{
	for (Node<string> * p = rhs; p; p = p->pNext)
	{
		out << p->data;
   
    if (p->pNext != NULL)
      out << ", ";
	}
 
  return out;
}

/***********************************************
* NON-Member Function
* FREEDATA: provides the user with the function
*       of deleting a given linked list
**********************************************/
template<class T>
void freeData(Node<T> * & pHead)
{
  pHead = NULL;
  delete pHead;
}

#endif // NODE_H

