/***********************************************************************
 * Module:
 *    Week 02, Stack
 *    Brother Jones, CS 235
 * Author:
 *    Joslyn Sidamonidze
 * Summary:
 *    This program will implement the testInfixToPostfix()
 *    and testInfixToAssembly() functions
 ************************************************************************/

#include <iostream>    // for ISTREAM and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stack.h"     // for STACK
using namespace std;

/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 *****************************************************/
string convertInfixToPostfix(const string & infix) 
{
	   
   //loop through the string 
   //assign numerical values to one stack
   //assign operators to another
   //
   char token;
   char toptoken;
   string tokenString;
   string postfix;
   const char BLANK = ' ';
   // (2 + 2) + 3 - 4
    for (int i = 0; i < infix.length(); i++)
	{
		cout << "starting loop i = " << i << endl;
		int num = 0;
		if(BLANK != infix[i])
		{
			if(infix[i] == '+' 
				|| infix[i] == '-'
				|| infix[i] == '*'
				|| infix[i] == '/')
			{
				cout << "adding token if\n";
				tokenString += infix[i];
			}
			else
			{
				cout << "adding num\n";
				int num = infix[i];
				postfix += num;
			}
		}
		else
		{
			cout << "adding blank\n";
			postfix += BLANK;
		}
	}
	//2 2 + 3 4 - +
	postfix += tokenString;

   return postfix;
}

/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";
   
   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);

      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << "\tpostfix: " << postfix << endl << endl;
      }
   }
   while (input != "quit");
}

/**********************************************
 * CONVERT POSTFIX TO ASSEMBLY
 * Convert postfix "5 2 +" to assembly:
 *     LOAD 5
 *     ADD 2
 *     STORE VALUE1
 **********************************************/
string convertPostfixToAssembly(const string & postfix)
{
   string assembly;

   

   return assembly;
}

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";

   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);
      
      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << convertPostfixToAssembly(postfix);
      }
   }
   while (input != "quit");
      
}
