/***********************************************************************
 * Implementation:
 *    NOW SERVING
 * Summary:
 *    This will contain the implementation for nowServing() as well as any
 *    other function or class implementations you may need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>       // for STRING
#include <cassert>      // for ASSERT
#include "nowServing.h" // for nowServing() prototype
#include "deque.h"      // for DEQUE
using namespace std;

struct List
{
  string cs;
  string name;
  int min;
  bool type;
};

/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{
   // instructions
   cout << "Every prompt is one minute.  The following input is accepted:\n";
   cout << "\t<class> <name> <#minutes>    : a normal help request\n";
   cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
   cout << "\tnone                         : no new request this minute\n";
   cout << "\tfinished                     : end simulation\n";

   // your code here
  Deque <List> deque;
  List temp;
  int servingtime;
  
  
  
  int q = 0;
  string input;
  string cs;
  string name;
  int min;

   List servingList;
   temp.min = 0;
   temp.type = false;
   
   // while loop handles input and exeptions
  do
  {
      cout << "<" << q << "> ";
      //prompt the user
      cin >> cs;
      if(cs == "!!")
      {
        cin >> cs;
        cin >> name;
        cin >> min;
    
    
        //push it in front of deque
        servingList.cs = cs;
        servingList.name = name;
        servingList.min = min;
        servingList.type = true;
        deque.push_front(servingList);
    
    
       if(!deque.empty() && temp.min == 0)
       {
         temp = deque.front();
         deque.pop_front();
       }

       if(temp.type == true)
       {
          cout << "\tEmergency for " << temp.name <<" for class " <<
          temp.cs <<". Time left: "<<  temp.min << endl;
       }
       else
       {
          cout << "\tCurrently serving " << temp.name <<" for class " <<
           temp.cs <<". Time left: "<<  temp.min << endl;
       }
      q++;
      temp.min--;
    }
    
    else if(cs != "none" && cs != "finished")
    {
      cin >> name;
      cin >> min;
    
      // Push data in the back of the deck
      servingList.cs = cs;
      servingList.name = name;
      servingList.min = min;
      servingList.type = false;
      deque.push_back(servingList);
  
  
      if(!deque.empty() && temp.min == 0)
      {
        temp = deque.front();
        deque.pop_front();
      }

      if(temp.type == true)
      {
        cout << "\tEmergency for " << temp.name <<" for class " <<
           temp.cs <<". Time left: "<<  temp.min << endl;
      }
      else
      {
        cout << "\tCurrently serving " << temp.name <<" for class " <<
           temp.cs <<". Time left: "<<  temp.min << endl;
      }
      q++;
      temp.min--;
  }
  
  else if(cs== "none")
  {
    if(!deque.empty() && temp.min == 0)
    {
      temp = deque.front();
      deque.pop_front();
    }

    if(temp.min > 0)
    {

      // if emergency print emergency 
       if(temp.type == true)
       {
          cout << "\tEmergency for " << temp.name <<" for class " <<
           temp.cs <<". Time left: "<<  temp.min << endl;
       }
       // else print normal
       else
       {
          cout << "\tCurrently serving " << temp.name <<" for class " <<
           temp.cs <<". Time left: "<<  temp.min << endl;
       }

       temp.min--;
      }
    q++;
    }
  }
while(cs != "finished");
  
   // end
   cout << "End of simulation\n";
}
