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
#include <iomanip>
using namespace std;

#ifndef BIGINT
#define BIGINT

const int DIGITS_PER_SECTION = 3;
class BigInt
{
public:
	BigInt() : list(List<int>()){ }
	BigInt(unsigned int value)
	{
		int carryOver = value;
		while (carryOver > 0)
		{
			list.push_front( carryOver % 1000 );
			carryOver /= 1000;
		}
	}
	BigInt(const BigInt & copy)
	{
		list.head = copy.list.head;
		list.tail = copy.list.tail;
		list.Size = copy.list.Size;
	}
	~BigInt() { list.clear(); }



	friend ostream & operator<<(ostream& out, BigInt num);
	BigInt operator+=(BigInt adder)
	{
		int
			carryOver = 0,
			first,
			second;

		ListIterator<int> 
			adderit = adder.list.end(), 
			listit = list.end();
		while ( adderit != adder.list.begin() || listit != list.begin() )
		{
			if (adderit != adder.list.begin())
			{
				first = *adderit;
				adderit--;
			}
			else
				first = 0;

			if (listit != list.begin())
			{
				second = *listit;
				listit--;
			}
			else
				second = 0;


			int result = first + second + carryOver;
			carryOver = result / 1000;
			listit.p->data = result % 1000;
		}
		return *this;
	}
	BigInt operator=(BigInt adder)
	{
		list = adder.list;
		return *this;
	}
	List<int> getList() { return list; }
private:
	List<int> list;
};

ostream & operator<<(ostream & out, BigInt num)
{
	int sectionCount = 0;
	const int SECTIONS_PER_LINE = 20;
	for (ListIterator<int> it = num.getList().begin();;)
	{
		out << setfill('0');
		if (sectionCount == 0)
			out << setfill(' ');

		if (it == num.getList().end())
			return out;

		out << setw(3) << *it;
		sectionCount++;

		it++;
		if (it != num.getList().end())
		{
			out << ",";
			if (sectionCount > 0 && sectionCount % SECTIONS_PER_LINE == 0)
				out << endl;
		}
	}
	return out;
}
#endif // !BIGINT

/************************************************
 * FIBONACCI
 * The interactive function allowing the user to
 * display Fibonacci numbers
 ***********************************************/

List<BigInt> f(int num)
{
	List<BigInt> nums = List<BigInt>();
	for (int i = 0; i < num; i++)
	{
		//push a new number into the list that is equal to the previous 2 numbers
		if (nums.size() < 2)
			nums.push_back(BigInt(1));
		else
		{
			BigInt result = nums.tail->data;
				result += nums.tail->pPrev->data;
			nums.push_back(result);
		}
	}
	return nums;
}

void displayF(int num)
{
	List<BigInt> nums = f(num);

	for (ListIterator<BigInt> it = nums.begin(); it != nums.end(); it++)
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
   cout << "\t" << f(number).tail << "\n";
}


