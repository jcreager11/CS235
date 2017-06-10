#include <string>
#include "huffman.h"
using namespace std;

void huffman()
{

}

void huffman(string filename)
{
   // create list of a binary node of a pair for user input
   list <BinaryNode <Pair <string, float> > * > trees;
  //open the file
   ifstream fin(filename.c_str());
   Pair<string, float> tPair;

   if(fin.fail())
   {
      cout << "error HERE";
      cin.clear();
      cin.ignore(256, '\n');
   }
  // read in data
   while(fin >> tPair)
   {
      BinaryNode <Pair<string, float> >* newnode = new BinaryNode<Pair<string, float> >(tPair);
      trees.push_back(newnode);
   }
   fin.close();
 
// sort the list
while(trees.size() > 1)
  { 
   trees.sort(sortfunction);
   addtree(trees);
  }
   
   // define table
   list<Pair<string, string> > table;
   
   // encode Huffman code
   BinaryNode<Pair<string, float> >* tree = trees.front();
   encodingHuffman(tree, string(), table);
   
   table.sort();
   display(table);
   
   // make sure tree is deleted
   deleteBinaryTree(trees.front());
   return;  
}

////////////////////////////////////////////////
// SORT THE  BINARY NODE WITH BOOL STATMENT
////////////////////////////////////////////////
bool sortfunction(BinaryNode<Pair<string, float> >* left, BinaryNode<Pair<string, float> >* right)
{ 
   if(left->data.second < right->data.second)
   {
      return true;
   }
   else
   {
      return false;
   }
}

////////////////////////////////////////////////
// ADDS TWO NODES TOGETHER TO MAKE A CHILD OR A ROOT
////////////////////////////////////////////////
void addtree(list<BinaryNode<Pair<string, float> >* > &trees)
{
   BinaryNode<Pair<string, float> >* num1 = trees.front();
   trees.pop_front();
   BinaryNode<Pair<string, float> >* num2 = trees.front();
   trees.pop_front();


   float sum = num1->data.second + num2->data.second;
   BinaryNode<Pair<string, float> >* ptemp = new BinaryNode<Pair<string, float> >;
   trees.push_back(ptemp);
   
   // assign child to leaf
   ptemp->addLeft(num1);
   ptemp->addRight(num2);
   ptemp->data.second = sum;   
}

////////////////////////////////////////////////
// ENCODES HUFFMANDS CODE BY RECURSION
////////////////////////////////////////////////
void encodingHuffman(BinaryNode<Pair<string, float> > *tree, string code, list<Pair<string, string> > &table)
{
  if(tree->pLeft == NULL && tree->pRight == NULL)
  {
  Pair<string, string> tpair;
  tpair.first = tree->data.first;
  tpair.second = code;
  table.push_back(tpair);
  }
  else
  {
    encodingHuffman(tree->pLeft, code+"0", table);
    encodingHuffman(tree->pRight, code+"1", table);
  }
}

////////////////////////////////////////////////
// DISPLYS ENCODED MATERIAL ON THE SCREEN
////////////////////////////////////////////////
void display(list<Pair<string, string> > &table)
{
  for(list<Pair<string, string> > :: iterator it = table.begin(); it != table.end();  it++)
  {
    cout << (*it).first << " = " << (*it).second << endl;
  }
}