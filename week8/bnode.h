#ifndef BNODE_H
#define BNODE_H

#include <iostream>
#include <cassert>

#include <iostream>
using namespace std;

template <class T>
class BinaryNode
{
public:
  BinaryNode() : pLeft(NULL), pRight(NULL), pParent(NULL), numNodes(1) {}
  BinaryNode(T value) : data(value), numNodes(1), pLeft(NULL), pRight(NULL), pParent(NULL) {}
  
  void addLeft(T);
  void addLeft(BinaryNode<T>*);
  
  void addRight(T);
  void addRight(BinaryNode<T>*);
  
  int size() {return getRoot(this)->numNodes;} //returns the size (located at the root node)
  void addSize(int i) {getRoot(this)->numNodes += i;}
  
  BinaryNode<T> *pLeft;
  BinaryNode<T> *pRight;
  BinaryNode<T> *pParent;
  
  T data;
  
private:
  int numNodes; //holds the number of nodes in the tree
};

template <class T>
BinaryNode<T>* getRoot(BinaryNode<T>* node)
{
  BinaryNode<T>* iterator = node;
  
  while (iterator->pParent != NULL)
  {
    iterator = iterator->pParent;
  }
  
  return iterator;
}

template <class T>
int countNodes(BinaryNode<T>* node)
{
  int i = 1;
  
  if (node->pLeft != NULL)
    i += countNodes(node->pLeft);
    
  if (node->pRight != NULL)
    i += countNodes(node->pRight);
    
  return i;
}

template <class T>
void BinaryNode<T> :: addLeft(T value)
{
  if (this->pLeft == NULL)
  {
    this->pLeft = new BinaryNode<T>(value);
    this->pLeft->pParent = this;
    this->addSize(1);
  }
  else
    this->pLeft->data = value;
}

template <class T>
void BinaryNode<T> :: addLeft(BinaryNode<T> *left)
{
  if (left == NULL) //&& this->pLeft != NULL)
  {
    //deleteBinaryTree(this->pLeft);
    this->pLeft = NULL;
  }
  else if (this->pLeft == NULL)
  {
    this->pLeft = left;
    this->pLeft->pParent = this;
    this->addSize(countNodes(left));
  }
  else
  {
    BinaryNode<T> *tempLeft = this->pLeft->pLeft;
    BinaryNode<T> *tempRight = this->pLeft->pRight;
    
    this->pLeft = new BinaryNode<T>(left->data);
    this->pLeft->pLeft = tempLeft;
    this->pLeft->pRight = tempRight;
    
    //this->pLeft->data = left->data;
  }
}

template <class T>
void BinaryNode<T> :: addRight(T value)
{
  if (this->pRight == NULL)
  {
    this->pRight = new BinaryNode<T>(value);
    this->pRight->pParent = this;
    this->addSize(1);
  }
  else
    this->pRight->data = value;
}

template <class T>
void BinaryNode<T> :: addRight(BinaryNode<T> *right)
{
  if (right == NULL) //&& this->pRight != NULL)
  {
    //deleteBinaryTree(this->pRight);
    this->pRight = NULL;
  }
  else if (this->pRight == NULL)
  {
    this->pRight = right;
    this->pRight->pParent = this;
    this->addSize(countNodes(right));
  }
  else
  {
    BinaryNode<T> *tempLeft = this->pRight->pLeft;
    BinaryNode<T> *tempRight = this->pRight->pRight;
    
    this->pRight = new BinaryNode<T>(right->data);
    this->pRight->pLeft = tempLeft;
    this->pRight->pRight = tempRight;
    
    //this->pRight->data = right->data;
  }
}

template <class T>
void deleteBinaryTree(BinaryNode<T> *tree)
{
  if (tree == NULL)
    return;
    
  if (tree->pLeft != NULL)
    deleteBinaryTree(tree->pLeft);
    
  if (tree->pRight != NULL)
    deleteBinaryTree(tree->pRight);
    
  tree->addSize(-1);
  tree = NULL;
}

template <class T>
ostream & operator << (ostream & out, BinaryNode<T>* node)
{
  if (node->pLeft != NULL)
    out << node->pLeft;
    
  out << node->data << ' ';
    
  if (node->pRight != NULL)
    out << node->pRight;
  
  return out;
}

#endif //BNODE