//************************************************************************
// ASU CSE310 Assignment #6 Spring 2024
// Author: Anuj Prabhu
// ASU ID: 1225065855
// Description: Red black tree implementation. See RedBlackTree.h
//              for the Red Black Tree definition
//************************************************************************

// include the relevant header file
#include "RedBlackTree.h"
#include <iomanip>
#include <stdlib.h>
#include <string>

// using statements go here
using namespace std;

//*******************************************************************
// constructor
RedBlackTree::RedBlackTree()
{
      //----
      root = nullptr;
}

//*******************************************************************
// destructor
int RedBlackTree::destructTree(Node *node) /*helper function that achieves TWO functionalities.
1. deletes every node of RBT one by one
2. returns total number of deleted nodes*/
{
      if (node == nullptr)
      {
            return 0;
      }
      else
      {
            int leftDeleted = destructTree(node->leftChild);   // total deleted nodes in left subtree
            int rightDeleted = destructTree(node->rightChild); // total deleted nodes in right subtree
            delete node;
            return 1 + leftDeleted + rightDeleted; //+1 to account for current node
      }
}

// destructor
RedBlackTree::~RedBlackTree()
{
      //----
      int deletedNodes = 0;
      deletedNodes = destructTree(root); // call helper function
      cout << "The number of nodes deleted: " << deletedNodes << endl;
}

//**************************************************************
// Accessor for the root of the red-black tree

// write your own code according to red-black tree definition
//----
Node *RedBlackTree::getRoot()
{
      return root;
}

//*******************************************************************
// delete the sub-tree rooted at 'node' and return number of nodes deleted
// This should be defined as a recursive function

// write your own code according to red-black tree definition
//---
int RedBlackTree::deleteNode(Node *node)
{
      int deletedNodes = 0;
      deletedNodes = destructTree(node); // call helper function
      return deletedNodes;
}

//****************************************************************
// This is the general BST insertion operation.
// It does not care about the color of the newly added node.

// write your own code according to red-black tree definition
//----
void RedBlackTree::insertNode(Node *node)
{
      string vin = to_string(node->vin);
      string model = node->model;
      string make = node->make;
      string node_key = vin + "," + model + "," + make;

      Node *current = root; // x
      Node *nodeParent = nullptr;

      while (current != nullptr) // iterate through tree to find correct leaf node to insert below
      {
            nodeParent = current;

            if (compareNodes(current, node_key) < 0)
            {
                  current = current->leftChild;
            }
            else
            {
                  current = current->rightChild;
            }
      }
      node->parent = nodeParent; // set node's parent to nodeParent
      if (nodeParent == nullptr) // case: if tree is empty
      {
            root = node;
      }
      else if (compareNodes(nodeParent, node_key) < 0)
      {
            nodeParent->leftChild = node;
      }
      else
      {
            nodeParent->rightChild = node;
      }
}

//*******************************************************************
// At beginning, each newly added node will always be RED,
// this may violate the red-black tree property #4. fixUp()
// function will restore the property.

// write your own code according to red-black tree definition
//----
void RedBlackTree::fixUp(Node *node)
{
      while (node->parent != nullptr && node->parent->color == "RED") /*loop until parent's color is red and node is not root
      since cant continue fixing up at root; just have to change root color to black*/
      {
            // cout << "no issues accessing node.parent.color" << endl;
            if (node->parent == node->parent->parent->leftChild)
            {
                  // cout << "no issues accessing node.parent.parent.leftChild; entering first if block" << endl;
                  Node *uncleNode = node->parent->parent->rightChild;
                  if (uncleNode != nullptr && uncleNode->color == "RED") // if uncle is not a dummy leaf node and is red
                  {
                        node->parent->color = "BLACK";
                        uncleNode->color = "BLACK";
                        node->parent->parent->color = "RED";
                        node = node->parent->parent;
                  }
                  else // if uncle is black (dummy leaf node or black)
                  {
                        if (node == node->parent->rightChild)
                        {
                              node = node->parent;
                              // cout << "code before inner left rotate happening fine" << endl;
                              leftRotate(node);
                              // cout << "code after inner left rotate happening fine" << endl;
                        }
                        node->parent->color = "BLACK";
                        node->parent->parent->color = "RED";
                        // cout << "code before outer right rotate happening fine" << endl;
                        rightRotate(node->parent->parent);
                        // cout << "code after outer left rotate happening fine" << endl;
                  }
            }
            else // symmetric
            {
                  // cout << "no issues accessing node.parent.parent.leftChild; entering first else block" << endl;
                  Node *uncleNode = node->parent->parent->leftChild;
                  // cout << y << endl;
                  // cout << "uncle being accessed and set to y fine" << endl;
                  if (uncleNode != nullptr && uncleNode->color == "RED")
                  {
                        // cout << "checking if uncle's color is RED fine" << endl;
                        node->parent->color = "BLACK";
                        // cout << "node.parent.color = BLACK fine" << endl;
                        uncleNode->color = "BLACK";
                        // cout << "y.color = BLACK fine" << endl;
                        node->parent->parent->color = "RED";
                        // cout << "node.parent.parent.color = RED" << endl;
                        node = node->parent->parent;
                        // cout << "node = node.parent.parent fine" << endl;

                        // cout << "exiting 2nd if fine" << endl;
                  }
                  else
                  {
                        if (node == node->parent->leftChild)
                        {
                              node = node->parent;
                              // cout << "code before inner right rotate happening fine" << endl;
                              rightRotate(node);
                              // cout << "code after inner right rotate happening fine" << endl;
                        }
                        node->parent->color = "BLACK";
                        node->parent->parent->color = "RED";
                        // cout << "code before outer left rotate happening fine" << endl;
                        leftRotate(node->parent->parent);
                        // cout << "code after outer left rotate happening fine" << endl;
                  }
                  // cout << "exiting 2nd else fine" << endl;
            }
            // cout << "exiting first while condition fine" << endl;
            // cout << node->parent << endl;
      }
      root->color = "BLACK";
      // cout << "setting root.color = BLACK fine" << endl;
}

//*****************************************************
// This function print the pre-order traversal of the
// subtree rooted at 'node'.It's a recursive function

// write your own code according to red-black tree definition
//----
void RedBlackTree::preOrderTraversal(Node *node)
{
      if (node != nullptr)
      {
            print(node); // order: root, L, R
            preOrderTraversal(node->leftChild);
            preOrderTraversal(node->rightChild);
      }
}

//**************************************************
// This function print the in-order traversal of the
// subtree rooted at 'node'.It's a recursive function

// write your own code according to red-black tree definition
//----
void RedBlackTree::inorderTraversal(Node *node)
{
      if (node != nullptr)
      {
            inorderTraversal(node->leftChild);
            print(node); // order: L, root, R
            inorderTraversal(node->rightChild);
      }
}

//**************************************************
// This function print the post-order traversal of the
// subtree rooted at 'node'.It's a recursive function

// write your own code according to red-black tree definition
//----
void RedBlackTree::postOrderTraversal(Node *node)
{
      if (node != nullptr)
      {
            postOrderTraversal(node->leftChild);
            postOrderTraversal(node->rightChild);
            print(node); // order: L, R, root
      }
}

//**************************************************************
// This function returns a pointer points to the minimum node from
// the current sub-tree rooted at 'node'. It should be designed as
// a recursive function

// write your own code according to red-black tree definition
//----
Node *RedBlackTree::findMinimumNode(Node *node)
{
      if (node->leftChild == nullptr)
      {
            return node;
      }
      else
      {
            return findMinimumNode(node->leftChild); // keep going as left as possible
      }
}

//**************************************************************
// This function returns a pointer points to the maximum node from
// the current sub-tree rooted at 'node'. It should be designed as
// a recursive function

// write your own code according to red-black tree definition
//----
Node *RedBlackTree::findMaximumNode(Node *node)
{
      if (node->rightChild == nullptr)
      {
            return node;
      }
      else
      {
            return findMaximumNode(node->rightChild); // keep going as right as possible
      }
}

//**************************************************************
// This function search the tree for a given key of a Car
// Note: key is the combination of vin, model and make of the Car
// It returns a pointer points to the node if founded; otherwise it returns NULL

// write your own code according to red-black tree definition
//----
Node *RedBlackTree::treeSearch(int vin, string model, string make)
{
      string key = to_string(vin) + "," + model + "," + make;

      Node *current = root;
      while (current != nullptr && (vin != current->vin || model != current->model || make != current->make))
      {
            if (compareNodes(current, key) < 0) // search left or right subtree based on key
            {
                  current = current->leftChild;
            }
            else
            {
                  current = current->rightChild;
            }
      }
      return current;
}

//****************************************************
// This function left-rotate the BST rooted at 'node'

// write your own code according to red-black tree definition
//----
void RedBlackTree::leftRotate(Node *node)
{
      Node *nodeRightChild = node->rightChild;
      node->rightChild = nodeRightChild->leftChild;
      if (nodeRightChild->leftChild != nullptr)
      {
            nodeRightChild->leftChild->parent = node;
      }
      nodeRightChild->parent = node->parent;
      if (node->parent == nullptr)
      {
            root = nodeRightChild;
      }
      else if (node == node->parent->leftChild)
      {
            node->parent->leftChild = nodeRightChild;
      }
      else
      {
            node->parent->rightChild = nodeRightChild;
      }
      // if (y != nullptr)
      //{
      nodeRightChild->leftChild = node;
      //}
      node->parent = nodeRightChild;
}

//***************************************************
// This function right-rotate the BST rooted at 'node'

// write your own code according to red-black tree definition
//----
void RedBlackTree::rightRotate(Node *node) // symmetric to left rotate
{
      Node *nodeLeftChild = node->leftChild;
      node->leftChild = nodeLeftChild->rightChild;
      if (nodeLeftChild->rightChild != nullptr)
      {
            nodeLeftChild->rightChild->parent = node;
      }
      nodeLeftChild->parent = node->parent;
      if (node->parent == nullptr)
      {
            root = nodeLeftChild;
      }
      else if (node == node->parent->rightChild)
      {
            node->parent->rightChild = nodeLeftChild;
      }
      else
      {
            node->parent->leftChild = nodeLeftChild;
      }
      // if (y != nullptr)
      //{
      nodeLeftChild->rightChild = node;
      //}
      node->parent = nodeLeftChild;
}

//**************************************************************
// This function finds the predecessor of the given 'node'
// it prints the relevant predecessor info. on screen and also
// return a pointer that points to the predecessor

// write your own code according to red-black tree definition
//----
Node *RedBlackTree::findPredecessorNode(Node *node)
{
      if (node->leftChild != nullptr)
      {
            return findMaximumNode(node->leftChild); // find max of node's left child
      }
      else
      {
            Node *nodeParent = node->parent;
            while (nodeParent != nullptr && node == nodeParent->leftChild) // then iterate back up to find predecessor
            {
                  node = nodeParent;
                  nodeParent = nodeParent->parent;
            }
            return nodeParent;
      }
}

//**************************************************************
// This function finds the successor of the given 'node'
// it prints the relevant successor info. on screen and also return
// a pointer that points to the successor node

// write your own code according to red-black tree definition
//----
Node *RedBlackTree::findSuccessorNode(Node *node) // symmetric to findPredecessorNode
{
      if (node->rightChild != nullptr)
      {
            return findMinimumNode(node->rightChild);
      }
      else
      {
            Node *nodeParent = node->parent;
            while (nodeParent != nullptr && node == nodeParent->rightChild)
            {
                  node = nodeParent;
                  nodeParent = nodeParent->parent;
            }
            return nodeParent;
      }
}

//****************************************************************
// This function find the minimum node of the entire red-black tree
// It print out the minimum node info. on screen if tree is not empty
// or print Tree is empty. No Minimum. message on screen.

// write your own code according to red-black tree definition
//----
void RedBlackTree::treeMinimum() // call findMinimumNode on root
{
      if (root == nullptr)
      {
            cout << "tree is empty" << endl;
      }
      else
      {
            cout << "The MINIMUM is:" << endl;
            print(findMinimumNode(root));
      }
}

//**************************************************************
// This function find the maximum node of the entire red-black tree
// It print out the maximum node info. on screen if tree is not empty
// or print Tree is empty. No Maximum. message on screen.

// write your own code according to red-black tree definition
//----
void RedBlackTree::treeMaximum() // call findMaximumNode on root
{
      if (root == nullptr)
      {
            cout << "tree is empty" << endl;
      }
      else
      {
            cout << "The MAXIMUM is:" << endl;
            print(findMaximumNode(root));
      }
}

//****************************************************************************
// This function print out the pre-order traversal of the entire red-black tree

// write your own code according to red-black tree definition
//----
void RedBlackTree::treePreorder() // call preOrderTraversal on root;
{
      if (root == nullptr)
      {
            cout << "tree is empty" << endl;
      }
      else
      {
            preOrderTraversal(root);
      }
}

//***************************************************************************
// This function print out the in-order traversal of the entire red-black tree

// write your own code according to red-black tree definition
//----
void RedBlackTree::treeInorder() // call inorderTraversal on root;
{
      if (root == nullptr)
      {
            cout << "tree is empty" << endl;
      }
      else
      {
            inorderTraversal(root);
      }
}

//*****************************************************************************
// This function print out the post-order traversal of the entire red-black tree

// write your own code according to red-black tree definition
//----
void RedBlackTree::treePostorder() // call postOrderTraversal on root;
{
      if (root == nullptr)
      {
            cout << "tree is empty" << endl;
      }
      else
      {
            postOrderTraversal(root);
      }
}

//******************************************************************
// Given a Car key, this function first check whether the
// Car is inside the tree or not, if it is inside, it will print
// its predecessor info. on screen, if not, it print an error message

// write your own code according to red-black tree definition
//----
void RedBlackTree::treePredecessor(int vin, string model, string make)
{
      Node *searchResult = treeSearch(vin, model, make);
      if (searchResult == nullptr)
      {
            cout << left;
            cout << setw(8) << vin
                 << setw(12) << model
                 << setw(12) << make << " is NOT FOUND." << endl;
            cout << "Its Predecessor does NOT EXIST" << endl;
      }
      else
      {
            cout << left;
            cout << setw(8) << vin
                 << setw(12) << model
                 << setw(12) << make << " is FOUND." << endl;
            Node *result = findPredecessorNode(searchResult); // find predecessor of given node
            if (result == nullptr)
            {
                  cout << "Its Predecessor does NOT EXIST" << endl;
            }
            else
            {
                  cout << "Its Predecessor is:" << endl;
                  print(result);
            }
      }
}

//******************************************************************
// Given a Car key, this function first check whether the
// Car is inside the tree or not, if it is inside, it will print
// its successor info. on screen, if not, it print an error message

// write your own code according to red-black tree definition
//----
void RedBlackTree::treeSuccessor(int vin, string model, string make)
{
      Node *searchResult = treeSearch(vin, model, make);
      if (searchResult == nullptr)
      {
            cout << left;
            cout << setw(8) << vin
                 << setw(12) << model
                 << setw(12) << make << " is NOT FOUND." << endl;
            cout << "Its Successor does NOT EXIST" << endl;
      }
      else
      {
            cout << left;
            cout << setw(8) << vin
                 << setw(12) << model
                 << setw(12) << make << " is FOUND." << endl;
            Node *result = findSuccessorNode(searchResult); // find successor of given node
            if (result == nullptr)
            {
                  cout << "Its Successor does NOT EXIST" << endl;
            }
            else
            {
                  cout << "Its Successor is:" << endl;
                  print(result);
            }
      }
}

//**************************************************************
// This function create a node from the given info., then insert
// the node inside the red-black tree. Note: at beginning, the newly
// added node should always be 'RED'

// write your own code according to red-black tree definition
//----
void RedBlackTree::treeInsert(int vin, string model, string make, double price)
{
      Node *newNode = new Node(vin, model, make, price);
      if (root == nullptr) // if tree is empty, color node black and insert regularly as root
      {
            newNode->color = "BLACK";
            insertNode(newNode); // bst insert
            // cout << "insertNode is happening fine" << endl;
            newNode->leftChild = nullptr; /*newNode will be leaf node after regular bst insert so
            left and right child will be null points*/
            newNode->rightChild = nullptr;
      }
      else // if tree is not empty, color node red and insert regularly with bst insert. fix up to fix any violations.
      {
            newNode->color = "RED";
            insertNode(newNode);
            // cout << "insertNode is happening fine" << endl;
            newNode->leftChild = nullptr; /*newNode will be leaf node after regular bst insert so
            left and right child will be null points*/
            newNode->rightChild = nullptr;
            fixUp(newNode);
            // cout << "fixUp is happening fine" << endl;
      }
}

//******************************************************************
// Given a 'node', this function prints all the node information on screen
void RedBlackTree::print(Node *node)
{
      cout << left;
      cout << setw(8) << node->vin
           << setw(12) << node->model
           << setw(12) << node->make
           << setw(10) << fixed << setprecision(2) << node->price;
      cout << right << setw(7) << node->color << endl;
}

//**************************************************************
// Given a Node 'node1', this function compares it with another
// node's key.
// key is a string combination of vin + model + make
// It returns a negative number if in alphabetical order, key2 is
// in front of 'node1'; otherwise it returns a positive number

// write your own code according to red-black tree definition
//----
int RedBlackTree::compareNodes(Node *node, string key)
{
      string vin = to_string(node->vin);
      string model = node->model;
      string make = node->make;

      string node_key = vin + "," + model + "," + make;
      return key.compare(node_key); // compare given key with node's key and return desired number based on comparison
}