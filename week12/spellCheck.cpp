/***********************************************************************
 * Module:
 *    Week 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name here>
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype> //for usage of the tolower() function for strings
#include "spellCheck.h"
#include "hash.h"
using namespace std;

/*
Hashes a string.
*/
class SHash : public Hash <string>
{
public:
   SHash(int numBuckets)    throw (const char *) : Hash <string> (numBuckets) {}
   SHash(const SHash & rhs) throw (const char *) : Hash <string> (rhs)        {}

   /*
   This hash takes the sum of all the ascii numbers of the chars in a word
   and mods it by the capacity. This method seems great because it
   produces a high enough number to mod with and the result is fairly
   random within the range of 0 to the capacity. This reduces the number of
   collisions between values, which benefits the efficiency of the hashtable.
   */
   int hash(const string & value) const
   {
      int sum = 0;
      
      for (int i = 0; i < value.length(); i++)
        sum += int(value[i]); //add ascii value to sum

      int index = sum % capacity();
      assert(0 <= index && index < capacity());
      
      return index;
   }
};

/*****************************************
 * SPELL CHECK
 * Prompt the user for a file to spell-check
 ****************************************/
void spellCheck()
{
  //load up the dictionary
  ifstream in;
  in.open("/home/cs235/week12/dictionary.txt");
  
  SHash sh(1000);
  string word;
  
  while (in >> word)
  {
    sh.insert(word);
    //cout << "inserted: " << word << endl;
  }
  
  //now load up the file to be checked and compare
  cout << "What file do you want to check? ";
  string fileName;
  cin >> fileName;
  
  ifstream in2;
  in2.open(fileName.c_str());
  
  string wordToCheck;
  List<string> list;
  
  //check spelling of every word
  while (in2 >> wordToCheck)
  {
    //convert first letter to lowercase in order to check properly
    //with dictionary words.
    string tempCheck = wordToCheck;
    tempCheck[0] = tolower(tempCheck[0]);
    
    if (!sh.find(tempCheck))
      list.push_back(wordToCheck);
      
    //it is not needed to find the duplicates
    /*
    {
      bool duplicate = false;
      
      //check for duplicates already in the list
      for (ListIterator<string> it = list.begin(); it != list.end(); it++)
      {
        if (*it == wordToCheck)
          duplicate = true;
      }
      
      if (!duplicate)
        list.push_back(wordToCheck);
    }
    */
  }
  
  //print out mispelled words or nothing if no errors
  if (list.empty())
    cout << "File contains no spelling errors\n";
  else
  {
    cout << "Misspelled: ";
    
    ListIterator<string> it = list.begin();
    cout << *it;
    it++;
    
    for (; it != list.end(); it++)
    {
      cout << ", " << *it;
    }
    
    cout << endl;
  }
}
