#include "wordCount.h"
#include "map.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void wordCount()
{
  cout << "What is the filename to be counted? ";
  string fileName;
  cin >> fileName;
  
  ifstream in;
  in.open(fileName.c_str());
  
  string text;
  Map<string, int> map;
  
  while (in >> text)
  {
    map[text] = map[text] + 1;
  }
  
  string word;
  cout << "What word whose frequency is to be found. Type ! when done\n";
  
  while (word != "!")
  {
    cout << "> ";
    cin >> word;
    
    if (word != "!")
      cout << "\t" << word << " : " << map[word] << endl;
  }
}