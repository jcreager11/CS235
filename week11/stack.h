/***********************************************************************
* Header:
*    STACK      
* Summary:
*    The stack Class
* Author
*    Joslyn Sidamonidze, 
************************************************************************/

#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <cassert>

/*********************************
* Stack Class
* A class that holds things
**********************************/
template <class T>
class Stack
{
  public:
    //Default Constructor
    Stack() : item(0), cap(0), data(NULL) {}
    
    //Copy Constructor 
    Stack(const Stack & rhs) throw (const char *);
    
    //Non-Default constructor
    Stack(int cap) throw (const char *);
    
    //Destructor
    ~Stack() {if(cap) delete [] data;}
    
    //Assignment Operator
    Stack & operator = (const Stack & rhs) throw (const char *);
    
    //Test if empty
    bool empty() const {return item == 0;}
    
    //returns the size
    int size() const {return item;}
    
    //return capacity or number of elements
    int capacity() {return cap;}
    
    //clears the content
    void clear() {item = 0;}
    
    // push: adds new element
    void push(T additem);
    
    //pop: Removes an item at the end of the stack
    void pop() throw (const char *);
    
    //top: returns the item at the end of the stack
    T top() throw (const char *);
    
    
    private:
      int item;
      int cap;
      T * data;

};

/*******************************************
* Copy Constructor 
* Copys the Stack
*******************************************/
template <class T>
Stack <T> :: Stack(const Stack <T> & rhs) throw (const char *)
{
  assert(rhs.cap >= 0);
  
  // do nothing if there is nothing to do
  if (rhs.cap == 0)
  {
    cap = item = 0;
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
  
  // copy over the capacity and size
  assert(rhs.item >= 0 && rhs.item <= rhs.cap);
  cap = rhs.cap;
  item = rhs.item;
  
  // copy the items
  for (int i = 0; i < item; i++)
  {
    data[i] = rhs.data[i];
  }
  
  // The rest is filled with default value for T
  for(int i = item; i < cap; i++)
  {
    data[i] = T();
  }
}

/*******************************************
* Non-Default Constructor
* Preallocates the container
*******************************************/
template <class T>
Stack <T> :: Stack(int cap) throw (const char *)
{
  assert(cap >= 0);
  
  // do nothing if there is nothing to do 
  if(cap == 0)
  {
    this -> cap = this -> item = 0;
    this -> data = NULL;
  }
  
  // attmept to allocate
  try
  {
    data = new T[cap];
  }
  catch (std::bad_alloc)
  {
    throw "ERROR: Unable to allocate buffer.";
  }
  
  //copy over cap
  this -> cap = cap;
  this -> item = 0;
  
  //initialize the container by calling the default constructor 
  for (int i = 0; i < cap; i++)
  {
    data[i] = T();
  }
}

/*******************************************************
* Operator
* Copys the data from one stack to another
*******************************************************/
template <class T>
Stack <T> & Stack <T> :: operator  = (const Stack <T> & rhs) throw (const char *)
{
  assert(rhs.cap >= 0);
  
  // do nothing if there is nothing to do
  if (rhs.cap == 0)
  {
    cap = item = 0;
    data = NULL;
    return *this;
  }
  
  if (data != NULL)
  {
    delete [] data;
  }
  
  //attempt to allocate
  try
  {
    data = new T[rhs.cap];
  }
  catch (std::bad_alloc)
  {
    throw "Error: Unable to allocate buffer.";
  }
  
  // copy over the capacity and size
  
  assert(rhs.item >= 0 && rhs.item <= rhs.cap);
  cap = rhs.cap;
  item = rhs.item;
  
  for (int i = 0; i < item; i++)
  {
    data[i] = rhs.data[i];
  }
  
  // Fill the rest with default value for T
  for (int i = item; i < cap; i++)
  {
    data[i] = T();
  }
  
  return *this;
}

/***************************************************************
* Push
* pushes the item back to a new location
**************************************************************/
template <class T>
void Stack <T> :: push (T additem)
{
  if(cap <= item)
  {
    // increases the memory
    if(cap == 0)
    {
      cap = 1;
    }
    else
    {
      cap = cap * 2;
    } 
     
    T * temp = new T[cap];
    
    for (int i = 0; i < item; i++)
    {
      temp[i] = data[i];
    }
    
    if(data != NULL)
    {
      delete [] data;
    }
    
    data = temp;
  }
  
  data[item++] = additem;
}

/*************************************************
* Pop
* removes the first item from the stack
*************************************************/
template <class T>
void Stack <T> :: pop() throw (const char *)
{
  if(!empty())
  {
    item--;
  }
  else 
  {
    throw "ERROR: Unable to pop from an empty Stack";
  }
}

/************************************************
* Top
* return sthe top item in the stack
*************************************************/
template <class T>
T Stack <T> :: top() throw (const char *)
{
  if (empty())
  {
    return NULL;
    throw "ERROR: Unable to reference the element from an empty Stack";
  }
  else
  {
    return data[item - 1];
  }
}


#endif // STACK_H