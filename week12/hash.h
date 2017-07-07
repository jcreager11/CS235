#include <iostream>
#include <cassert>
#include "list.h"

using namespace std;

template <class T>
class Hash
{
public:
  //constructors:
  Hash(int buckets) : cap(buckets), numItems(0) {data = new List<T>[buckets];}
  Hash(const Hash & right) : cap(right.cap), numItems(right.numItems) {data = right.data;}
  
  //destructor:
  ~Hash() {}
  
  //operators:
  void operator = (const Hash & right);
  
  //methods:
  void resize(int);
  
  bool empty() const {return numItems == 0;}
  int size() const {return numItems;}
  int capacity() const {return cap;}
  
  void clear()
  {
    data = NULL;
    data = new List<T>[cap];
  }
  bool find(T);
  void insert(T);
  
  virtual int hash(const T&) const = 0; //=0 because of pure virtual function
  
protected:
  int numItems;
  int cap;
  List<T>* data; //make a list at each index for chaining
};

/*
Sets this hash equal to another.
*/
template <class T>
void Hash<T> :: operator = (const Hash<T> & right)
{
  clear();
  /*
  for (int i = 0; i < right.cap; i++)
  {
    List<T> list = right.data[i];
    
    for (ListIterator<T> it = list.begin(); it != list.end(); it++)
    {
      insert(*it);
    }
  }
  */
  
  numItems = right.numItems;
  cap = right.cap;
  
  for (int i = 0; i < cap; i++)
    data[i] = right.data[i];
}

/*
Finds a value within the hashtable.
*/
template <class T>
bool Hash<T> :: find(T value)
{
  int index = hash(value);
  List<T> list = data[index];
    
  for (ListIterator<T> it = list.begin(); it != list.end(); it++)
  {
    if (*it == value)
      return true;
  }
  
  return false;
}

/*
Inserts a value into the hashtable.
*/
template <class T>
void Hash<T> :: insert(T value)
{
  int index = hash(value);
  data[index].push_back(value);
  numItems++;
}