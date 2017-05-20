/***********************************************************************
* Program:
*    Assignment 01, Go Fish
*    Brother Helfrich, CS 235
* Author:
*    <your names here>
* Summary: 
*    This is all the functions necessary to play Go Fish!
*
*    Estimated:  0.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part.
************************************************************************/

#include <iostream>
#include "set.h"
#include "card.h"
#include "goFish.h"
#include <string>
#include <fstream>
using namespace std;

/**********************************************************************
 * GO FISH
 * The function which starts it all
 ***********************************************************************/
void goFish()
{
  cout << "We will play 5 rounds of Go Fish.  Guess the card in the hand\n";
  Set<Card> deck;
  int i = 0;
  Card h;
  
  ifstream in;
  in.open("/home/cs235/week05/hand.txt");
  
  while (in >> h)
  {
    deck.insert(h);
  }
  
  int matches = 0;
  
  while (i < 5)
  {
    i++;
    cout << "round " << i << ": ";
    
    Card guess;
    cin >> guess;

    Card cardMatch = *(deck.find(guess));
    
    if (guess == cardMatch && guess != "-INVALID-")
    {
      cout << "\tYou got a match!\n";
      deck.erase(deck.find(guess));
      matches++;
    }
    else
    {
      cout << "\tGo Fish!\n";
    }
  }
  
  cout << "You have " << matches << " matches!\n";
  cout << "The remaining cards: ";
  
  for (SetIterator<Card> it = deck.begin(); it != deck.end();it)
  {
    cout << *it;
    it++;
    
    if (it != deck.end())
      cout << ", ";
  }
  
  cout << endl;
  
   return ;
}
