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
    if (value >= 1000)
      BigInt(value / 1000);
      
    list.push_front(value % 1000);
    
		//while (carryOver > 0)
		//{
			//list.push_front( carryOver % 1000 );
			//carryOver /= 1000;
		//}
	}

/*
	BigInt(const BigInt & copy)
	{
		list.head = copy.list.head;
		list.tail = copy.list.tail;
		list.Size = copy.list.Size;
	}
	~BigInt() { list.clear(); }

	friend ostream & operator<<(ostream& out, BigInt num);
 
 */
 
	BigInt operator+=(BigInt adder)
	{
		int carryOver = 0, first, second;
		ListIterator<int> adderit = adder.list.rbegin(), listit = list.rbegin();
   
    int index = 0;
   
		while (adderit != adder.list.rend() || listit != list.rend())
		{
      index++;

      if (adderit != adder.list.rend())
      {
		    first = *adderit;
		    adderit--;
      }
			else
				first = 0;
      
			if (listit != list.rend())
      {
        second = *listit;
        
        int result = first + second + carryOver;
        
        if (result >= 1000)
        {
          carryOver = 1;
        }
        else
          carryOver = 0;
          
			  listit.p->data = result % 1000;     
        listit--;
      }
			else
      {
				int result = first + carryOver;
        
        if (result >= 1000)
        {
          carryOver = 1;
        }
        else
          carryOver = 0;
          
        adder.list.push_front(result % 1000);
      }
		}
   
    if (carryOver == 1)
    {
      list.push_front(1);
      carryOver = 0;
    }
   
		return *this;
	}
 
	BigInt operator=(BigInt adder)
	{
		list = adder.list;
		return *this;
	}

	List<int> getList() { return list; }

  friend ostream & operator<<(ostream & out, BigInt num)
  {
	  int sectionCount = 0;
	  const int SECTIONS_PER_LINE = 20;
    
	  for (ListIterator<int> it = num.getList().begin(); it != num.getList().end(); it++)
	  {
      if (sectionCount != 0)
        cout << ',';
      
      if (sectionCount != 0)
      {
        out << setfill('0');
        out << setw(3);
      }
      else
        out << setw(0);
        
      out << *it;
      sectionCount++;
      
      if (sectionCount > 0 && sectionCount % SECTIONS_PER_LINE == 0);
				  //out << endl;
    }
    return out;
  }
  
  private:
    List<int> list;
};
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
   {
			nums.push_back(BigInt(1));
   }
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
  int x = 0;
  
	for (ListIterator<BigInt> it = nums.begin(); it != nums.end(); it++)
	{
    x++;
    cout << "\t" << it.p->data << endl;
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
   cout << "\t" << *(f(number).rbegin()) << "\n";
}


