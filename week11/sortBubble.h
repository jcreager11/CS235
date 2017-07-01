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
	int compareUntil = num - 1;
	while (compareUntil != 0)
	{
		T lastValue = 1;
		for (int i = 1; i < compareUntil; i++)
		{
			if (array[i] > array[i + 1])
			{
				T temp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = temp;
				lastValue = i;
			}
			compareUntil = lastValue - 1;
		}
		compareUntil--;
	}
}


#endif // SORT_BUBBLE_H
