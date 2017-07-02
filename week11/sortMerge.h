/***********************************************************************
 * Module:
 *    Week 11, Sort Merge
 *    Brother Helfrich, CS 235
 * Author:
 *    <author>
 * Summary:
 *    This program will implement the Merge Sort
 ************************************************************************/

#ifndef SORT_MERGE_H
#define SORT_MERGE_H

template <class T>
void merge(T array[], int first, int mid, int last)
{
  int num1 = mid - first + 1, //number of values for first aray
  num2 = last - mid; //number of values for second array
  
  T array1[num1], array2[num2]; //create two arrays
  
  for (int i = 0; i < num1; i++)
    array1[i] = array[first + i]; //copy values into first array
  
  for (int i = 0; i < num2; i++)
    array2[i] = array[mid + 1 + i]; //copy values into second array
    
  int ar1ind = 0, ar2ind = 0, mergeind = first; //array 1 index, array 2 index, merge index
  
  //compare values from both arrays and insert into merged array by comparing values
  while (ar1ind < num1 && ar2ind < num2)
  {
    if (array1[ar1ind] <= array2[ar2ind])
    {
      array[mergeind] = array1[ar1ind];
      ar1ind++;
    }
    else
    {
      array[mergeind] = array2[ar2ind];
      ar2ind++;
    }
    
    mergeind++;
  }

  //put leftovers into merged array
  while (ar1ind < num1)
  {
    array[mergeind] = array1[ar1ind];
    ar1ind++;
    mergeind++;
  }
  
  while (ar2ind < num2)
  {
    array[mergeind] = array2[ar2ind];
    ar2ind++;
    mergeind++;
  }
}

template <class T>
void split(T  array[], int first, int last)
{
  if (first < last)
  {
    int mid = (first + (last - 1)) / 2; //mid of first and last
    
    split(array, first, mid);
    split(array, mid + 1, last);
  
    merge(array, first, mid, last);
  }
}

/*****************************************************
 * SORT MERGE
 * Perform the merge sort
 ****************************************************/
template <class T>
void sortMerge(T array[], int num)
{
  split(array, 0, num - 1);
}


#endif // SORT_MERGE_H
