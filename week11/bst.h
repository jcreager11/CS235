#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>

#include "bnode.h"
#include "stack.h"

using namespace std;

//forward declaration:
template <class T>
class BSTIterator;

template <class T>
class BST
{
public:
  //CONSTRUCTORS
  BST() : root(NULL), redBlackSort(true) {}
  BST(BST<T>* tree);
  ~BST();
  
  //OPERATORS
  void operator = (BST<T>);
  
  //METHODS
  bool empty();
  int size();
  void clear();
  void insert(T);
  void remove(BSTIterator<T>);
  BSTIterator<T> find(T);
  BinaryNode<T>* getRoot() {return root;}
  
  //RETURNS BEGINNINGS AND ENDS
  BSTIterator<T> begin();
  BSTIterator<T> end();
  BSTIterator<T> rbegin();
  BSTIterator<T> rend();
  
  //steps for red/black node tree:
  void step2(BinaryNode<T>*);
  void step3(BinaryNode<T>*);
  
  bool redBlackSort;
  
private:
  BinaryNode<T>* root;
};

template <class T>
class BSTIterator
{
public:
  //CONSTRUCTORS:
  BSTIterator() {stack = Stack<BinaryNode<T>* >();}
  BSTIterator(BinaryNode<T>*);
  BSTIterator(Stack<T> copy) {stack = copy;}
  BSTIterator(BSTIterator<T>*);
  
  //METHODS:
  void accumulate(BinaryNode<T>*);
  
  //OPERATORS
  BSTIterator<T>& operator = (const BSTIterator<T>&);
  bool operator == (BSTIterator<T>);
  bool operator != (BSTIterator<T>);
  const T operator * ();
  //prefix
  BSTIterator<T>& operator ++ ();
  BSTIterator<T>& operator -- ();
  //postfix
  BSTIterator<T>& operator ++ (int);
  BSTIterator<T>& operator -- (int);
  
//private:
  Stack<BinaryNode<T>* > stack;
};

/////
// BINARY SEARCH TREE CONSTRUCTORS
/////

/*
* Deletes all of the elements of the binary search tree.
*/
template <class T>
BST<T> :: ~BST<T>()
{
  deleteBinaryTree(root);
}

/////
// BINARY SEARCH TREE OPERATORS:
/////

template <class T>
void copyNodes(BinaryNode<T>* node, BinaryNode<T>* copy)
{  
  if (copy->pLeft != NULL)
  {
    node->addLeft(copy->pLeft->data);
    copyNodes(node->pLeft, copy->pLeft);
  }
    
  if (copy->pRight != NULL)
  {
    node->addRight(copy->pRight->data);
    copyNodes(node->pRight, copy->pRight);
  }
}

template <class T>
void BST<T> :: operator = (BST<T> right)
{
  if (right.root == NULL)
  {
    this->root = NULL;
    return;
  }
  
  this->root = new BinaryNode<T>(right.root->data);
  copyNodes(this->root, right.root);
}

/////
// BINARY SEARCH TREE METHODS
/////

/*
* Returns true if the binary search tree is empty or does not exist.
* Otherwise, returns false.
*/
template <class T>
bool BST<T> :: empty()
{
  if (root != NULL)
    return root->size() == 0;
    
  return true;
}

/*
* Returns the size of the binary search tree.
*/
template <class T>
int BST<T> :: size()
{
  if (root != NULL)
    return root->size();
    
  return 0;
}

/*
* Deletes all the elements in the binary search tree.
*/
template <class T>
void BST<T> :: clear()
{
  deleteBinaryTree(root);
  root = NULL;
}

/*
* Find where to insert a value.
*/
template <class T>
BinaryNode<T>* findSpot(BinaryNode<T>* node, T value)
{
  BinaryNode<T>* returnNode;
  
  if (value < node->data)
  {
    if (node->pLeft == NULL)
    {
      node->addLeft(value);
      return node->pLeft;
    }
    
    returnNode = findSpot(node->pLeft, value);
  }
  else if (value >= node->data)
  {
    if (node->pRight == NULL)
    {
      node->addRight(value);
      return node->pRight;
    }
    
    returnNode = findSpot(node->pRight, value);
  }
  
  return returnNode;
}

template <class T>
bool isLeftChild(BinaryNode<T>* node)
{
  if (node->pParent->pLeft == node)
    return true;
    
  return false;
}

template <class T>
void BST<T> :: step2 (BinaryNode<T>* insertNode)
{
  if (insertNode == root)
    insertNode->isRed = false;
  else
    step3(insertNode);
}

template <class T>
void leftLeft (BinaryNode<T>* parent)
{
  assert(parent->pParent != NULL);
  BinaryNode<T>* grandparent = parent->pParent;
  
  if (grandparent->pParent != NULL)
  {
    if (isLeftChild(grandparent))
    {
      grandparent->pParent->pLeft = parent;
      parent->pParent = grandparent->pParent;
    }
    else
    {
      grandparent->pParent->pRight = parent;
      parent->pParent = grandparent->pParent;
    }
  }
  else
    parent->pParent = NULL;
  
  grandparent->pLeft = parent->pRight;
  
  if (grandparent->pLeft != NULL)
    grandparent->pLeft->pParent = grandparent;
  
  parent->pRight = grandparent;
  parent->pRight->pParent = parent;
  
  //switch colors
  parent->isRed = false;
  grandparent->isRed = true;
}

template <class T>
void rightRight (BinaryNode<T>* parent)
{
  assert(parent->pParent != NULL);
  BinaryNode<T>* grandparent = parent->pParent;
  
  if (grandparent->pParent != NULL)
  {
    if (isLeftChild(grandparent))
    {
      grandparent->pParent->pLeft = parent;
      parent->pParent = grandparent->pParent;
    }
    else
    {
      grandparent->pParent->pRight = parent;
      parent->pParent = grandparent->pParent;
    }
  }
  else
    parent->pParent = NULL;
  
  grandparent->pRight = parent->pLeft;
  
  if (grandparent->pRight != NULL)
    grandparent->pRight->pParent = grandparent;
  
  parent->pLeft = grandparent;
  parent->pLeft->pParent = parent;
  
  //switch colors
  parent->isRed = false;
  grandparent->isRed = true;
}

template <class T>
void BST<T> :: step3 (BinaryNode<T>* insertNode)
{
  assert(insertNode != NULL);
  assert(insertNode->pParent != NULL);
  
  BinaryNode<T>* parent = insertNode->pParent;
  
  if (parent->isRed == false)
    return;
    
  BinaryNode<T>* grandparent = parent->pParent;
  BinaryNode<T>* aunt;
  
  if (isLeftChild(parent))
    aunt = grandparent->pRight;
  else
    aunt = grandparent->pLeft;
    
  if (aunt != NULL)
  {
    if (aunt->isRed)
    {
      parent->isRed = false;
      aunt->isRed = false;

      //grandparent
      grandparent->isRed = true;
      step2(grandparent);
      
      return;
    }
  }
  
  if (isLeftChild(parent) && isLeftChild(insertNode)) //LEFT-LEFT
  {
    leftLeft(parent);
  }
  else if (isLeftChild(parent) && !isLeftChild(insertNode)) //LEFT-RIGHT
  {
    grandparent->pLeft = insertNode;
    insertNode->pParent = grandparent;
    
    parent->pRight = insertNode->pLeft;
    
    if (parent->pRight != NULL)
      parent->pRight->pParent = parent;
    
    insertNode->pLeft = parent;
    parent->pParent = insertNode;
    
    leftLeft(insertNode);
  }
  else if (!isLeftChild(parent) && !isLeftChild(insertNode)) //RIGHT-RIGHT
  {
    rightRight(parent);
  }
  else if (!isLeftChild(parent) && isLeftChild(insertNode)) //RIGHT-LEFT
  {
    grandparent->pRight = insertNode;
    insertNode->pParent = grandparent;
    
    parent->pLeft = insertNode->pRight;
    
    if (parent->pLeft != NULL)
      parent->pLeft->pParent = parent;
    
    insertNode->pRight = parent;
    parent->pParent = insertNode;
    
    rightRight(insertNode);
  }
  //aunt is null or black
}

/*
* Inserts a node into the binary search tree.
*/
template <class T>
void BST<T> :: insert(T value)
{
  BinaryNode<T>* insertNode;
  
  if (root == NULL)
  {
    root = new BinaryNode<T>(value);
    insertNode = root;
  }
  else
    insertNode = findSpot(root, value);
    
  if (redBlackSort == true)
    step2(insertNode);
}

template <class T>
int numChildren(BinaryNode<T>* node)
{
  if (node->pLeft == NULL && node->pRight == NULL)
    return 0;
  else if (node->pLeft != NULL && node->pRight != NULL)
    return 2;
  else
    return 1;
}

/*
* Removes a value from the binary search tree.
*/
template <class T>
void BST<T> ::remove(BSTIterator<T> it)
{
  BinaryNode<T>* node = it.stack.top();
  BinaryNode<T>* parent = node->pParent;
  BinaryNode<T>* left = node->pLeft;
  BinaryNode<T>* right = node->pRight;

  if (numChildren(node) == 0)
  {
    if (isLeftChild(node))
      parent->pLeft = NULL;
    else
      parent->pRight = NULL;
      
    return;
  }
  
  //or else replace the parent with one of the children
  
  if (numChildren(node) == 1)
  {
    if (left != NULL && right == NULL)
    {
      if (isLeftChild(node))
        parent->pLeft = left;
      else
        parent->pRight = left;
    }
    else
    {
      if (isLeftChild(node))
        parent->pLeft = right;
      else
        parent->pRight = right;
    }
    
    return;
  }
  
  //Node has 2 children, find the successor to replace the node
  
  BinaryNode<T>* successor = node->pRight;
  
  while (successor->pLeft != NULL)
  {
    successor = successor->pLeft;
  }
  
  if (numChildren(successor) == 0)
  {
    if (isLeftChild(successor))
      successor->pParent->pLeft = NULL;
    else
      successor->pParent->pRight = NULL;
      
    return;
  }
  
  if (successor->pLeft != NULL && successor->pRight == NULL)
  {
    if (isLeftChild(successor))
      successor->pParent->pLeft = successor->pLeft;
    else
      successor->pParent->pRight = successor->pLeft;
  }
  else
  {
    if (isLeftChild(successor))
      successor->pParent->pLeft = successor->pRight;
    else
      successor->pParent->pRight = successor->pRight;
  }
  
  node->data = successor->data;
}

/*
* Finds a value in the binary search tree.
*/
template <class T>
BSTIterator<T> BST<T> :: find(T value)
{
  //CODE HERE
  BSTIterator <T> it;

  for (it = this->begin(); it != this->end(); ++it)
  {
    if (*it == value)
      return it;
  }

  return it;
}

/////
//BEGINNINGS AND ENDS
/////

template <class T>
BSTIterator<T> BST<T> :: begin()
{ 
  if (root == NULL)
    return BSTIterator<T>();
    
  BSTIterator<T> it;
  BinaryNode<T>* current = root;
    
  while (current->pLeft != NULL) //Find the leftmost value
  {
    it.stack.push(current);
    current = current->pLeft;
  }
  
  it.stack.push(current);
    
  return it;
}

template <class T>
BSTIterator<T> BST<T> :: end()
{
  return new BSTIterator<T>();
}

template <class T>
BSTIterator<T> BST<T> :: rbegin()
{
  //CHANGE THIS!!
  if (root == NULL)
    return BSTIterator<T>();
    
  BSTIterator<T> it;
  BinaryNode<T>* current = root;
  
  while (current->pRight != NULL) //Find the rightmost value
  {
    it.stack.push(current);
    current = current->pRight;
  }
  
  it.stack.push(current);
    
  return it;
}

template <class T>
BSTIterator<T> BST<T> :: rend()
{
  return new BSTIterator<T>();
}

/////
// BSTITERATOR CONSTRUCTORS
/////

template <class T>
void BSTIterator<T> :: accumulate(BinaryNode<T>* node)
{
  /* UNUSED
  if (node->pRight != NULL)
    accumulate(node->pRight);
    
  stack.push(node);
  cout << "pushed " << node->data;
  
  if (node->pLeft != NULL)
    accumulate(node->pLeft);
  */
}

/*
* Returns an iterator with a node as a parameter.
*/
template <class T>
BSTIterator<T> :: BSTIterator(BinaryNode<T>* node)
{
  stack = Stack<BinaryNode<T>* >();
  stack.push(node);
  
  /*
  if (node != NULL)
    accumulate(node);
  */
}

/*
* Copy constructor - copies a BSTIterator for the initial value.
*/
template <class T>
BSTIterator<T> :: BSTIterator(BSTIterator<T>* it)
{
  this->stack = Stack<BinaryNode<T>* >(it->stack);
}

/////
// BSTITERATOR OPERATORS
/////

/*
* Copies an iterator's values to another iterator's.
*/
template <class T>
BSTIterator<T>& BSTIterator<T> :: operator = (const BSTIterator<T>& right)
{
  this->stack = right.stack;
}

/*
* Compares two binary search trees to see if they're equal. Returns true if they are.
*/
template <class T>
bool BSTIterator<T> :: operator == (BSTIterator<T> right)
{
  BSTIterator<T> left = *this; //dereference this pointer
  
  while (left.stack.empty() == false || right.stack.empty() == false)
  {  
    if (left.stack.empty() == true || right.stack.empty() == true) //one stack is not empty and another is empty, return false
      return false;
    
    if (left.stack.top()->data != right.stack.top()->data)
      return false;
      
    left.stack.pop();
    right.stack.pop();
  }
  
  return true;
}

template <class T>
bool BSTIterator<T> :: operator != (BSTIterator<T> right)
{  
  if (*this == right) //simply see if they are equal to each other
  {
    return false;
  }
    
  return true;
}

template <class T>
const T BSTIterator<T> :: operator * ()
{
  if (stack.top() != NULL)
  {
    const T value = stack.top()->data;
    return value;
  }
  else
  {
    cout << "NULL TOP OF STACK VALUE";
    T x = T();
    return x;
  }
}

//prefix
template <class T>
BSTIterator<T>& BSTIterator<T> :: operator ++ ()
{
  if (stack.top() == NULL)
    return *this;
    
  if (stack.top()->pRight != NULL)
   {
      stack.push(stack.top()->pRight);

      // there might be more left-most children
      while (stack.top()->pLeft)
         stack.push(stack.top()->pLeft);
         
      return *this;
   }
   
   assert(stack.top()->pRight == NULL);
   BinaryNode <T> * pSave = stack.top();
   
   stack.pop();

   // if the parent is the NULL, we are done!
   if (stack.top() == NULL)
      return *this;
  
  // if we are the left-child, got to the parent.
   if (pSave == stack.top()->pLeft)
      return *this;

   // we are the right-child, go up as long as we are the right child!
   while (stack.top() != NULL && pSave == stack.top()->pRight)
   {
      pSave = stack.top();
      stack.pop();
   }
   
  return *this;
}

//prefix
template <class T>
BSTIterator<T>& BSTIterator<T> :: operator -- ()
{
   // do nothing if we have nothing
   if (stack.top() == NULL)
      return *this;

   // if there is a left node, take it
   if (stack.top()->pLeft != NULL)
   {
      stack.push(stack.top()->pLeft);

      // there might be more right-most children
      while (stack.top()->pRight)
         stack.push(stack.top()->pRight);
         
      return *this;
   }

   // there are no left children, the right are done
   assert(stack.top()->pLeft == NULL);
   BinaryNode <T> * pSave = stack.top();
   stack.pop();

   // if the parent is the NULL, we are done!
   if (NULL == stack.top())
      return *this;

   // if we are the right-child, got to the parent.
   if (pSave == stack.top()->pRight)
      return *this;

   // we are the left-child, go up as long as we are the left child!
   while (stack.top() != NULL && pSave == stack.top()->pLeft)
   {
      pSave = stack.top();
      stack.pop();
   }

   return *this;
}

//postfix
template <class T>
BSTIterator<T>& BSTIterator<T> :: operator -- (int)
{
  BSTIterator<T> it = *this;
  --it;
  return it;
}

template <class T>
BSTIterator<T>& BSTIterator<T> :: operator ++ (int)
{
  BSTIterator<T> it = *this;
  ++it;
  return it;
}

#endif
