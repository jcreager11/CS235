/***********************************************************************
 * Implementation:
 *    FIBONACCI
 * Summary:
 *    This will contain the implementation for fibonacci() as well as any
 *    other function or class implementations you may need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>
#include "fibonacci.h"   // for fibonacci() prototype
#include "list.h"        // for LIST
using namespace std;


/************************************************
 * FIBONACCI
 * The interactive function allowing the user to
 * display Fibonacci numbers
 ***********************************************/

List<int> f(int num)
{
	List<int> nums = List<int>();
	for (int i = 0; i < num; i++)
	{
		//push a new number into the list that is equal to the previous 2 numbers
		if (nums.size() < 2)
			nums.push_back(1);
		else
		{
			int x = nums.tail->data;
			int y = nums.tail->pPrev->data;
			nums.push_back(x + y);
		}
	}
	return nums;
}

void displayF(int num)
{
	List<int> nums = f(num);

	for (ListIterator<int> it = nums.begin(); it != nums.end(); it++)
	{
		cout << "\t" << it.p->data << "\n";
	}
}

void fibonacci()
{
   // show the first serveral Fibonacci numbers
   int number;
   cout << "How many Fibonacci numbers would you like to see? ";
   cin  >> number;

   // your code to display the first <number> Fibonacci numbers
   displayF(number);

   // prompt for a single large Fibonacci
   cout << "Which Fibonacci number would you like to display? ";
   cin  >> number;

   // your code to display the <number>th Fibonacci number
   cout << "\t" << f(number).tail->data << "\n";
}


