#ifndef SORTBINARY_H
#define SORTBINARY_H

using namespace std;

template <class T>
void sortBinary(T array[], int numItems)
{
  BST<T> tree;
  tree.redBlackSort = false;
  
  for (int i = 0; i < numItems; i++)
  {
    tree.insert(array[i]);
  }
  
  int i = 0;
  
  for (BSTIterator<T> it = tree.begin(); it != tree.end(); ++it)
  {
    array[i] = *it;
    i++;
  }
}

#endif //SORTBINARY