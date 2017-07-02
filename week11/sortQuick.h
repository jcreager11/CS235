/***********************************************************************
 * Module:
 *    Week 11, Sort Quick
 *    Brother Jones, CS 235
 * Author:
 *    <author>
 * Summary:
 *    This program will implement the Quick Sort
 * Sources:
 *    http://me.dt.in.th/page/Quicksort/
 ************************************************************************/

#ifndef SORT_QUICK_H
#define SORT_QUICK_H

#include "stack.h"

template <class T>
int partition(T array[], int first, int last)
{
  int pivot = first;
  int firstOpened = first + 1;
  
  for (int i = first + 1; i <= last; i++)
  {
    if (array[i] < array[pivot])
    {
      T temp = array[firstOpened];
      array[firstOpened] = array[i];
      array[i] = temp;
      
      firstOpened++;
    }
  }
  
  if (firstOpened != 0)
  {
    int lastClosed = firstOpened - 1; //last closed
    T temp = array[lastClosed];
    array[lastClosed] = array[pivot];
    array[pivot] = temp;
    pivot = lastClosed; //change pivot since it switched with last closed
  }
  
  return pivot; //return pivot position
}

template <class T>
int quicksort(T array[], int first, int last)
{
  if (first != last)
  {
    int pivot = partition(array, first, last);
    
    if (pivot != first)
      quicksort(array, first, pivot - 1);
      
    if (pivot != last)
      quicksort(array, pivot + 1, last);
  }
}

/*****************************************************
 * SORT QUICK
 * Perform the quick sort
 ****************************************************/
template <class T>
void sortQuick(T array[], int num)
{
  if (num == 0 || num == 1)
    return; //do nothing
    
  quicksort(array, 0, num - 1);
}


#endif // SORT_QUICK_H
