#include "bst.h"
#include "pair.h"

using namespace std;

//forward declaration for the map iterator
template <class T1, class T2>
class MapIterator;

template <class T1, class T2>
class Map
{
public:
  //constructors/destructors:
  Map() : numItems(0) {}
  Map(const Map<T1, T2> & copy) : numItems(copy.numItems) {tree = copy.tree;}
  ~Map() {this->clear();} //simply call the clear function
  
  //operators:
  void operator = (Map<T1, T2> right) {tree = right.tree; numItems = right.numItems;}
  T2& operator [] (T1);
  
  //methods:
  bool empty() {return tree.empty();}
  int size() {return numItems;}
  void clear() {numItems = 0; tree.clear();}
  MapIterator<T1, T2> find(T1 p1) {return MapIterator<T1, T2>(tree.find(Pair<T1, T2>()));}
  
  //begin and end:
  MapIterator<T1, T2> begin() {return MapIterator<T1, T2>(tree.begin());}
  MapIterator<T1, T2> end() {return MapIterator<T1, T2>(tree.end());}
  
  //rbegin and rend:
  MapIterator<T1, T2> rbegin() {return MapIterator<T1, T2>(tree.rbegin());}
  MapIterator<T1, T2> rend() {return MapIterator<T1, T2>(tree.rend());}
  
private:
  int numItems;
  BST<Pair<T1, T2> > tree;
};

template <class T1, class T2>
class MapIterator
{
public:
  //constructors:
  MapIterator() {}
  MapIterator(const MapIterator<T1, T2> & copy) {bstIt = copy.bstIt;}
  MapIterator(const BSTIterator<Pair<T1, T2> > copyIt) {bstIt = copyIt;}
  
  //operators:
  void operator = (const MapIterator<T1, T2> right) {bstIt = right.bstIt;}
  bool operator == (const MapIterator<T1, T2> right) {return bstIt == right.bstIt;}
  bool operator != (const MapIterator<T1, T2> right) {return bstIt != right.bstIt;}
  const Pair<T1, T2> operator * () {return *bstIt;}
  
  //prefix
  MapIterator<T1, T2>& operator ++ () {++bstIt; return *this;}
  MapIterator<T1, T2>& operator -- () {--bstIt; return *this;}
  
  //postfix
  MapIterator<T1, T2>& operator ++ (int) {bstIt++; return *this;}
  MapIterator<T1, T2>& operator -- (int) {bstIt--; return *this;}
  
//private:
  BSTIterator<Pair<T1, T2> > bstIt;
};

/*
insert operator:
*/
template <class T1, class T2>
T2& Map<T1, T2> :: operator [] (T1 index)
{
  for (MapIterator<T1, T2> mapIt = begin(); mapIt != end(); ++mapIt)
  {
    Pair<T1, T2> pair = *mapIt;

    if (pair.first == index)
    {
      //return pair.second; //doesn't work -- is a local variable
      return mapIt.bstIt.stack.top()->data.second;
    }
  }
  
  Pair<T1, T2> value = Pair<T1, T2>(index, T2());
  tree.insert(value);
  numItems++;
  
  //it is necessary to find the value because of troubles of creating a local variable
  BSTIterator<Pair<T1, T2> > myValue = tree.find(value);
  return myValue.stack.top()->data.second;
}