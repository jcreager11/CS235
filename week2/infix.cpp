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
   char token,
     topToken;
     
   string postfix;
   Stack<char> gStack;
   const string BLANK = " ";
   const string NOTHING = "";

   for (int i = 0; i < infix.size(); i++)
   {
     token = infix[i];
     
     if (token == ' ')
     {
        
     }
     else if (token == '(')
     {
       gStack.push(token);
     }
     else if (token == ')')
     {
       for (;;)
       {
         topToken = gStack.top();
         gStack.pop();
         if (topToken == '(') break;
         postfix.append(BLANK + topToken);
       }
     }
     else if (token == '+' || token == '-' || token == '*' || token == '/' || token == '%' || token == '^')
     {
       for (;;)
       {
         if (gStack.empty() || gStack.top() == '(' || (token == '*' || token == '/' || token == '%') && (gStack.top() == '+' || gStack.top() == '-'))
         {
           gStack.push(token);
           break;
         }
         else if (gStack.empty() || token == '^')
         {
           gStack.push(token);
           break;
         }
         else
         {
           topToken = gStack.top();
           gStack.pop();
           postfix.append(BLANK + topToken);
         }
       }
     }
     else
     {
       postfix.append(BLANK + token);
       
       for (;;)
       {
         if (!isalnum(infix[i+1]) && infix[i+1] != '.')
           break;
           
         i++;
         token = infix[i];
       
         postfix.append(1, token);
       }
     }
   }
   
   for (;;)
   {
     if (gStack.empty())
       break;
       
     topToken = gStack.top();
     gStack.pop();
     
     if (topToken != '(')
     {
       postfix.append(BLANK + topToken);
     }
     else
     {
       cout << "ERROR ALERT";
       break;
     }
   }

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
