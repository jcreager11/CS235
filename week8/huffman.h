#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <list>
#include <vector>
#include "bnode.h"
#include "pair.h"
#include <fstream>
using namespace std;

//typedef BinaryNode<Pair<string, float> > HuffNode;


void huffman(string filename);
// sorts list 
bool sortfunction(BinaryNode<Pair<string, float> >* left, BinaryNode<Pair<string, float> >* right);
//adds two numbers together and makes it to a tree or tree child
void addtree(list<BinaryNode <Pair<string, float> > *> & trees);
// encodes binary tree
void encodingHuffman (BinaryNode<Pair<string, float> > *tree, string code, list<Pair<string, string> > &table);
// displays encoded Huffman code on the screen
void display(list<Pair<string, string> > &table);

#endif // HUFFMAN_h
