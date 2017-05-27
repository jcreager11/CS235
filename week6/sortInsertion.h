/***********************************************************************
 * Header:
 *    INSERTION SORT
 * Summary:
 *    This will contain just the prototype for insertionSortTest(). You may
 *    want to put other class definitions here as well.
 * Author
 *    <your names here>
 ************************************************************************/

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include <iostream>
#include "node.h"

/***********************************************
* INSERTION SORT
* Sort the items in the array
**********************************************/
template <class T>
void sortInsertion(T array[], int num)
{
  Node<T>* n = new Node<T>(array[0]);
  Node<T>* l = n; //loop node
  
  cout << ""; //oddly enough only runs when cout is called.
  
  //copy items over
  for (int i = 1; i < num; i++)
  {
    for (Node<T>* l = n; l; l = l->pNext)
    {
      if (l->pNext == NULL)
      {
        if (array[i] < l->data)
          insert(array[i], n, true);
        else
          insert(array[i], l);
          
        break;
      }
      else if (array[i] > l->data && array[i] < l->pNext->data)
      {
        insert(array[i], l);
        break;
      }
    }
  }
  
  int i = 0;
  
  for (Node<T> * l = n; l; l = l->pNext)
  {
    array[i] = l->data;
    i++;
  }
}

#endif // INSERTION_SORT_H

