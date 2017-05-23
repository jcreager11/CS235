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
	Node() { pNext = NULL; };
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
Node<T> copy(Node<T> * & toCopy)
{
	Node<T> * h;
	Node<T> * n;
		
	h = n = new Node<T>();
	
	//loop throught the list and copy contents
	//into another linkedlist
	for (Node<T> * p = &toCopy; p; p = p->pNext)
	{
		n->data = p->data;
		//look for the end of the linked list
		if (p->pNext)
			n->pNext = p->pNext;
		else
		{
			n->pNext = new Node<T>;
			n = n->pNext;
		}
	}
	return h;
}

/***********************************************
* NON-Member Function
* INSERT: provides the user with the function
*       of inserting a new Node into the linked
*       list
**********************************************/
template<class T>
Node<T> * insert(T data, Node<T> * & p)
{
	Node<T> * n = new Node<T>(data);
	n->pNext = p->pNext;
	p->pNext = n;
	return n;
}
template<class T>
Node<T> * insert(T data, Node<T> * & p, bool atHead)
{
	Node<T> * n;
	if (atHead)
	{
		n = new Node<T>(data);
		n->pNext = p;
		p = n;
	}
	else
		n = insert(data, p);
	return n;
}

/***********************************************
* NON-Member Function
* FIND: provides the user with the function
*       of returning a copy of a given linked
*       list
**********************************************/
template<class T>
Node<T> * find(Node<T> * & pHead, T dataToFind)
{
	for (Node<T> * p = pHead; pHead; p = p->pNext)
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
void operator<<(Node<T> * rhs)
{
	for (Node<T> * p = rhs; p; p = p->pNext)
	{
		cout << p->data;
	}
}

/***********************************************
* NON-Member Function
* FREEDATA: provides the user with the function
*       of deleting a given linked list
**********************************************/
template<class T>
void freeData(Node<T> * & pHead)
{
	for (Node<T> * p = pHead; p;)
	{
		pHead = NULL;
		Node<T> * t = p->pNext;
		delete p;
		p = t->pNext;
	}
}

#endif // NODE_H

