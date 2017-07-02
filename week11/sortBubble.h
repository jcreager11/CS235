/***********************************************************************
 * Module:
 *    Week 11, Sort Bubble
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the Bubble Sort
 ************************************************************************/

#ifndef SORT_BUBBLE_H
#define SORT_BUBBLE_H

/*****************************************************
 * SORT BUBBLE
 * Perform the bubble sort
 ****************************************************/
template <class T>
void sortBubble(T array[], int num)
{
  int numCompares = num - 1;
  
  while (numCompares != 0)
  {
    int last = 0;
    
    for (int i = 0; i != numCompares; i++)
    {
      if (array[i] > array[i + 1])
      {
        T temp = array[i];
        array[i] = array[i + 1];
        array[i + 1] = temp;
        
        last = i;
      }
    }
    
    numCompares = last;
  }
}


#endif // SORT_BUBBLE_H
