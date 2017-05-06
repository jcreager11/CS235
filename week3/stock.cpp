/***********************************************************************
 * Implementation:
 *    STOCK
 * Summary:
 *    This will contain the implementation for stocksBuySell() as well
 *    as any other function or class implementation you need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>    // for ISTREAM, OSTREAM, CIN, and COUT
#include <sstream>
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stock.h"     // for STOCK_TRANSACTION
#include "queue.h"     // for QUEUE
using namespace std;

struct Share
{
	Dollars dollars;
	int sharesAmt;
};

struct SellStock
{
	Dollars dollars;
	Dollars profit;
	int sharesAmt;
};

Queue<Share> queue;
Queue<SellStock> soldQueue;

void buy(istringstream &iss)
{
	//finish extracting amt and dollar values
	Share share;
	iss >> share.sharesAmt;
	iss >> share.dollars;
	//for each share purchased load dollar value into queue
	queue.push(share);
}

void sell(istringstream &iss)
{
	//finish extracting amt and dollar values
	SellStock sellStock;
  sellStock.sharesAmt = 0;
	//iss >> sellStock.sharesAmt;
  int sharesToSell;
  iss >> sharesToSell;
  
	iss >> sellStock.dollars;
  
  for (int i = 0; i < sharesToSell; i)
  {
    if (queue.front().sharesAmt > 0)
    {
      //cout << "count: " << sellStock.sharesAmt;
      sellStock.sharesAmt++;
      queue.front().sharesAmt--;
      sellStock.profit += sellStock.dollars - queue.front().dollars;
      
      i++;
    }
    else
    {
      soldQueue.push(sellStock);
      sellStock.sharesAmt = 0;
      sellStock.profit = 0;
      
      queue.pop();
    }
  }
  
  if (queue.front().sharesAmt == 0)
    queue.pop();

	soldQueue.push(sellStock);
}

void display()
{
  if (queue.size() > 0)
    cout << "Currently held:\n";
  
  Queue<Share> tempBuyQueue = queue; //create temporary so we can pop off objects
  
  for (int i = 0; i < tempBuyQueue.size(); i)
  {
    Share share = tempBuyQueue.top();
    cout << "\tBought " << share.sharesAmt << " shares at " << share.dollars << endl;
    tempBuyQueue.pop();
  }
  
  Queue<SellStock> tempSellQueue = soldQueue; //same as tempBuyQueue
  Dollars proceeds;
  
  if (tempSellQueue.size() > 0)
    cout << "Sell History:\n";
  
  for (int i = 0; i < tempSellQueue.size(); i)
  {
    SellStock share = tempSellQueue.top();
    
    cout << "\tSold " << share.sharesAmt << " shares at " << share.dollars
         << " for a profit of " << share.profit << endl;
         
    proceeds += share.profit;
    tempSellQueue.pop();
  }
  
  cout << "Proceeds: " << proceeds << endl;
}

/************************************************
 * STOCKS BUY SELL
 * The interactive function allowing the user to
 * buy and sell stocks
 ***********************************************/
void stocksBuySell()
{
   // instructions
   cout << "This program will allow you to buy and sell stocks. "
        << "The actions are:\n";
   cout << "  buy 200 $1.57   - Buy 200 shares at $1.57\n";
   cout << "  sell 150 $2.15  - Sell 150 shares at $2.15\n";
   cout << "  display         - Display your current stock portfolio\n";
   cout << "  quit            - Display a final report and quit the program\n";

   // your code here...
   
  string input;
  
  while (input[0] != 'q')
  {
    cout << "> ";
    
    if (cin.peek() == '\n')
      cin.ignore();
      
    getline(cin, input);
    istringstream iss(input);
     
    string action;
    iss >> action;

    switch (action[0])
    {
      case 'b' :
        buy(iss);
        break;
      case 's' :
        sell(iss);
        break;
      case 'd' :
        display();
        break;
      case 'q' :
        break;
      default :
        cout << "Invalid action!";
    }
  }
}





