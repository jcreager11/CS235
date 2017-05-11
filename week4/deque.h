/*************************************************************************
* Header:
*   Deque Class and definitions
* Summary:
*
* Authors:
*
******************************************************************************/

#ifndef Deque_H
#define Deque_H

#include <iostream>
#include <cassert>
using namespace std;

template <class T>
class Deque
{
  public:
  
    //Default Constructor
    Deque() : items(0), cap(0), myback(0), myfront(0), data(NULL) {}
    
    //copy constructor
    Deque (const Deque & rhs) throw (const char *);
    
    // non-default constructor
    Deque (int cap) throw (const char *);
    
    //destructor
    ~Deque()  {if (cap) delete [] data;}
    
    //assignment operator
    Deque & operator = (const Deque & rhs) throw (const char *);
    
    //Capacity?
    int capacity() {return cap;}
    
    //Empty: is it empty?
    bool empty() const {return items == 0;}
    
    //full: is it full?
    bool full() const
    {
      if (items == cap)
        return true;
      else
        return false;
    }
    
    //clear: removes items
    void clear() {items = 0, myfront = 0, myback = 0;}
    
    //size: how many items?
    int size() const {return items;}
    
    //allocate
    void allocate() throw (const char *);
    
    //push_back: adds to the back
    void push_back(T additem) throw (const char *);
    
    //push_front:  adds to the front
    void push_front(T additem) throw (const char *);
    
    //pop_front
    void pop_front() throw (const char *);
    
    //pop_back
    void pop_back() throw (const char *);
    
    //top
    T top() throw (const char *);
    
    //front
    T & front() throw (const char *)
    {
      if (empty())
      {
         throw "ERROR: unable to access data from an empty deque";
      }
      else
      {
        return data[myfront];
      }
    }
    
    //back
    T & back() throw (const char *)
    {
      if (empty())
      {
        throw "ERROR: unable to access data from an empty deque";
      }
      else
      {
        return data[myback];
      }
    }
    
  private:
    int myback;
    int myfront;
    int items;
    int cap;
    T * data;
        
};

/**********************************************************
* Deque: Copy Consructor
* 
*********************************************************/
template <class T>
Deque <T> :: Deque(const Deque <T> & rhs) throw (const char *)
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
* Deque: Non-Default constructor
*
*********************************************************************/
template <class T>
Deque <T> :: Deque(int cap) throw (const char *)
{
   assert(cap >= 0);
   
   // do nothing if there is nothing to do
   if (cap == 0)
   {
      this->cap = this-> items = 0;
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
 * Deque:  OPERATOR  
 * COPYS DATA FROM ONE VECTOR TO OTHER..
 *******************************************/
template <class T>
Deque<T> & Deque <T> :: operator =(const Deque <T> & rhs) throw (const char *)
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
   if(data != NULL)
      delete [] data;
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
* Deque: Allocate
* doubles the memory when needed
*************************************************/
template <class T>
void Deque <T> ::allocate()  throw (const char *)
{
   int tempcap = cap;
   if(cap == 0)
   {
      cap = 1;
   }
   else
   {
      cap *= 2;
   }
   T * temp = new T[cap];
   int j = myfront;
   for(int i = 0; i<items; i++, j= (j+1) % tempcap)
   {
      temp[i] = data[j];
   }
   
   delete [] data;
   data = temp;
   myfront = 0;
   myback = items;
}

/***************************************************
* Deque: push_back
* pushes the item back to a new location
**************************************************/
template <class T>
void Deque <T> :: push_back (T additem)  throw (const char *)
{
  
   if(items >= cap)
   {
      allocate();
   }

   data[myback] = additem;
   myback = (myback + 1) % cap;
   items++;
   return;
}



/***********************************************
* Deque: pop_back  
* pop removes first item from the stack
*************************************************/
template <class T>
void Deque <T> ::pop_back() throw (const char * )
{
   if(items > 0)
   {
      myback = (myback - 1 + cap) % cap;
      items--;
   } 
   else
   {
      throw "ERROR: unable to pop from the back of empty deque";
   }
}


/***********************************************
* Deque: pop_front  
* pop removes first item from the stack
*************************************************/
template <class T>
void Deque <T> :: pop_front() throw (const char * )
{
   if(items > 0)
   {
      myfront = (myfront+1) % cap;
      items--;
   } 
   else
   {
      throw "ERROR: unable to pop from the front of empty deque";
   }
}

/***********************************************
* Deque: push_front
* pushes the item back to a new location
**************************************************/
template <class T>
void Deque <T> :: push_front(T additem) throw (const char *)
{
      if(items >= cap)
   {
      allocate();
   }

   myfront = (myfront - 1 + cap) % cap;
   data[myfront] = additem;
   items++;
   return;

}

/*********************************************** 
* Deque: Top
* top return the top item in the deque
************************************************/
template <class T>
T  Deque <T> :: top() throw (const char *)
{
   if(empty())
   {
      throw  "ERROR: Unable to reference the element from an empty Stack";
   }
   else 
      return data[myfront];
}



#endif