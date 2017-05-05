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

Queue<Share> sell(istringstream &iss, Queue<Share> queue)
{
	//finish extracting amt and dollar values
	SellStock sellStock;
	iss >> sellStock.sharesAmt;
	iss >> sellStock.dollars;

	//
	while (sellStock.sharesAmt >= 0)
	{
		Share share = queue.front();
		//if the amtToSell is greater then this Shares amt then 
		//subtract sharesAmt from amtToSell
		if (sellStock.sharesAmt >= share.sharesAmt)
		{
			sellStock.sharesAmt -= share.sharesAmt;
			sellStock.profit += (sellStock.dollars - share.dollars) * share.sharesAmt;
			queue.pop();
		}
		//else 0 out this share and move to the next after calculation
		if (sellStock.sharesAmt < share.sharesAmt)
		{
			share.sharesAmt -= sellStock.sharesAmt;
			sellStock.profit += (sellStock.dollars - share.dollars) * sellStock.sharesAmt;
		}
	}
	soldQueue.push(sellStock);
	return queue;
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
   getline(cin, input);
   istringstream iss(input);
   string _case;
   iss >> _case;

	   switch (_case[0])
	   {
	   case 'b' : 
		   buy(iss);
		   break;
	   case 's' :
		   queue = sell(iss, queue);
		   break;
	   case 'd' :
		   break;
	   case 'q' :
		   break;

   }
}





