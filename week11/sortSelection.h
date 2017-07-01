/***********************************************************************
 * Module:
 *    Week 11, Sort Select
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the Selection Sort
 ************************************************************************/

#ifndef SORT_SELECTION_H
#define SORT_SELECTION_H

/*****************************************************
 * SORT SELECTION
 * Perform the selection sort
 ****************************************************/
template <class T>
void sortSelection(T array[], int num)
{
	for (int i = 1; i < num -1; i++)
	{
		int leastIndex = i;
		T leastValue = array[leastIndex];
		for (int j = i + 1; j < n - 1; j++)
		{
			//find smallest value
			if (array[j] < leastValue)
			{
				leastIndex = j;
				leastValue = array[j];
			}
		}
		//swap smallest and fisrt values
		if (leastIndex != i)
		{
			T temp = array[i];
			array[i] = leastValue;
			array[leastIndex] = temp;
		}
	}
}


#endif // SORT_SELECTION_H
