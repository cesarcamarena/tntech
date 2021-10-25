/*
	Name: Cesar Camarena
	Purpose: Program 4
*/
#if !defined (NULL)
#define NULL 0
#endif

#if !defined (AVLTREE_H)
#define AVLTREE_H

#include "Drawable.h"
#include "AVLTreeIterator.h"
#include "Line.h"

#include <iostream>
using namespace std;

template < class T >
class AVLTree : public Drawable
{
   
   private:
      AVLTreeNode<T>* root;

      bool avlFlag;
      int sz;

      int (*compare_items) (T* item_1, T* item_2);
      int (*compare_keys) (String* key, T* item);

	/*pre:  Takes in a tNode
	  post: Sets the tNode as the root*/
      void setRootNode(AVLTreeNode<T>* tNode);  //you can get by without using these methods, refer to root directly
      
	/*pre:  Nothing.
	  post: Returns the root node*/
	  AVLTreeNode<T>* getRootNode();
	  
	/*pre: Takes in the root of the tree
	  post: Returns the total height of the tree*/
      int getHeight(AVLTreeNode<T>* tNode);
	  
	/*pre:  Takes in the root of the tree
	  post: Returns whether the tree is balanced or not*/
      int isBalanced(AVLTreeNode<T>* tNode);
	  
	/*pre:  Takes in the root of the tree
	  post: Returns whether the tree is balanced or not*/
      bool checkBalanceFactors(AVLTreeNode<T>* tNode);

	/*pre:  Takes in the root of the tree
	  post: Deletes the root and it's left and right*/
      void destroyItem(AVLTreeNode<T>* tNode);
      
	/*pre:  Nothing.
	  post: Destroys the whole tree*/
	  void destroy();

	/*pre:  Takes in a tNode and its item
	  post: Inserts the tNode and its item in the tree*/
      AVLTreeNode<T>* insertItem(AVLTreeNode<T>* tNode, T* item);
      
	/*pre:  Takes in a tNode
	  post: Returns the item of its left most node*/
	  T* findLeftMost(AVLTreeNode<T>* tNode);

	/*pre:  Takes in the root of a tree
	  post: Rotates the tree to the left and returns the root*/
      AVLTreeNode<T>* rotateLeft(AVLTreeNode<T>* tNode);
	  
	/*pre:  Takes in the root of the tree
	  post: Rotates the tree to the right and returns the root*/
      AVLTreeNode<T>* rotateRight(AVLTreeNode<T>* tNode);

      //write and use methods to do each of the four rotations (SR, SL, DLR, DRL)
	  
	/*pre:  Takes in the root of the tree
	  post: Rotates the tree left and right and returns the root*/
      AVLTreeNode<T>* DLR(AVLTreeNode<T>* tNode);
      
	/*pre:  Takes in the root of the tree
	  post: Rotates the tree right and left and returns the root*/
	  AVLTreeNode<T>* DRL(AVLTreeNode<T>* tNode);

	/*pre:  Takes in the root of the tree
	  post: Fixes the balance factors and does the proper rotations*/
      AVLTreeNode<T>* avlFixAddLeft(AVLTreeNode<T>* tNode);
      
	/*pre:  Takes in the root of the tree
	  post: Fixes the balance factors and does the proper rotations*/
	  AVLTreeNode<T>* avlFixAddRight(AVLTreeNode<T>* tNode);
      
	/*pre:  Takes in the root of the tree and its left node
	  post: Changes the balance factors and returns the root*/
	  AVLTreeNode<T>* DLR(AVLTreeNode<T>* tNode, AVLTreeNode<T>* left);  //changes balance factors, calls the other DLR to do two rotations
      
	/*pre:  Takes in the root of the tree and its node
	  post: Changes the balance factors and returns the root*/
	  AVLTreeNode<T>* DRL(AVLTreeNode<T>* tNode, AVLTreeNode<T>* right);  //changes balance factors, calls the other DRL to do two rotations

      virtual void drawRec(AVLTreeNode<T>* tNode, wxDC&  dc, Line* line, int x_parent, int x_curr, int y_curr);

   public:
    /*pre:  Takes in the two function pointers
	  post: Constructs the AVLTree*/
      AVLTree(int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item));
	  
	/*pre:  Nothing.
	  post: Deconstructs the AVLTree*/
      ~AVLTree();

	/*pre:  Nothing.
	  post: Returns the size of the AVLTree*/
      int size();
      
	/*pre:  Takes in an item
	  post: Inserts the item into the AVLTree*/
	  void insert(T* item);
      
	 /*pre: Takes in search key
	  post: Returns the item from its search key*/
	  T* retrieve(String* sk);

	/*pre:  Nothing.
	  post: Returns true or false whether the tree isEmpty*/
      bool isEmpty();
      
	/*pre:  Nothing.
	  post: Makes the AVLTree empty*/
	  void makeEmpty();
      
	/*pre:  Nothing.
	  post: Returns the root's item*/
	  T* getRootItem();
      
	/*pre:  Nothing.
	  post: Creates an AVLTree iterator*/
	  AVLTreeIterator<T>* iterator();

	/*pre:  Nothing.
	  post: Returns the height of the tree*/
      int getHeight();
      
	/*pre:  Nothing.
	  post: Returns true or false whether the tree is balanced*/
	  bool isBalanced();
      
	/*pre:  Nothing.
	  post: Returns true or false whether the tree is balanced*/
	  bool checkBalanceFactors();

      void draw(wxDC&  dc, int width, int height);
      void mouseClicked(int x, int y);

};

template < class T >
AVLTree<T>::AVLTree(int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item))
{
	root = NULL;
	sz = 0;
	
	compare_items = comp_items;
	compare_keys = comp_keys;
}

template < class T >
AVLTree<T>::~AVLTree()
{
	destroy();
}

template < class T >
int AVLTree<T>::size()
{
	return sz;
}

template < class T >
T* AVLTree<T>::retrieve(String* sk)
{
	AVLTreeNode<T>* tNode = getRootNode();
	
	while (tNode != NULL)
	{
		T* item = tNode->getItem();
		int compare = (*compare_keys) (sk, item);
		
		if (compare == 0)
		{
			return item;
		}
		else if (compare < 0)
		{
			tNode = tNode->getLeft();
		}
		else
		{
			tNode = tNode->getRight();
		}
	}
	
	return NULL;
}

template < class T >
bool AVLTree<T>::isEmpty()
{
	return (sz == 0);
}

template < class T >
void AVLTree<T>::makeEmpty()
{
	destroy();
	root == NULL;
	sz = 0;
}

template < class T >
T* AVLTree<T>::getRootItem()
{
	return root->getItem();
}

template < class T >
AVLTreeIterator<T>* AVLTree<T>::iterator()
{
	return new AVLTreeIterator<T>(root);
}

template < class T >
void AVLTree<T>::setRootNode(AVLTreeNode<T>* tNode)
{
	root = tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::getRootNode()
{
	return root;
}

template < class T >
int AVLTree<T>::getHeight()
{
	return getHeight(root);
}

template < class T >
int AVLTree<T>::getHeight(AVLTreeNode<T>* tNode)
{
   if (tNode == NULL)
   {
	   return 0;
   }
   else
   {
	   int left = getHeight(tNode->getLeft());
	   int right = getHeight(tNode->getRight());
	   
	   if (left >= right)
	   {
		   return left + 1;
	   }
	   
	   else
	   {
		   return right + 1;
	   }
   }
}

template < class T >
bool AVLTree<T>::isBalanced()
{
	return isBalanced(root);
}

template < class T >
int AVLTree<T>::isBalanced(AVLTreeNode<T>* tNode)
{
   if (tNode == NULL)
   {
	   return true;
   }
   
   AVLTreeNode<T>* left = tNode->getLeft();
   
   AVLTreeNode<T>* right = tNode->getRight();
   
   bool leftBal = isBalanced(left);
   
   if (leftBal == false)
   {
	   return false;
   }
   
   bool rightBal = isBalanced(right);
   
   if (rightBal == false)
   {
	   return false;
   }
   
   int leftHeight = getHeight(left);
   int rightHeight = getHeight(right);
   
   if(abs(leftHeight - rightHeight) > 1)
   {
	   return false;
   }
   
   return true;
}

template < class T >
bool AVLTree<T>::checkBalanceFactors()
{
	return checkBalanceFactors(root);
}

template < class T >
bool AVLTree<T>::checkBalanceFactors(AVLTreeNode<T>* tNode)
{
	return isBalanced(tNode);
}

template < class T >
void AVLTree<T>::destroy()
{
	destroyItem(root);
}

template < class T >
void AVLTree<T>::destroyItem(AVLTreeNode<T>* tNode)
{
   if (tNode != NULL)
   {
      destroyItem(tNode->getLeft());
      destroyItem(tNode->getRight());
      delete tNode;
   }
}

template < class T >
void AVLTree<T>::insert(T* item)
{
	root = insertItem(root, item);
	avlFlag = false;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::insertItem(AVLTreeNode<T>* tNode, T* item)
{
   AVLTreeNode<T>* subtree;
   if (tNode == NULL)
   {
	  tNode = new AVLTreeNode<T>(item);
	  tNode->setBalanceFactor(BALANCED);
	  
	  avlFlag = true;
	  sz++;
	  return tNode;
   }

   T* node_items = tNode->getItem();
   int comp = (*compare_items) (item, node_items);

   if (comp == 0)
   {
      return tNode;
   }
   else if (comp < 0)
   {
      subtree = insertItem(tNode->getLeft(), item);
      tNode->setLeft(subtree);
	  if (avlFlag)
	  {
		  return avlFixAddLeft(tNode);
	  }
   }
   else
   {
      subtree = insertItem(tNode->getRight(), item);
      tNode->setRight(subtree);
	  if (avlFlag)
	  {
		  return avlFixAddRight(tNode);
	  }
   }
   
   return tNode;
}

template < class T >
T* AVLTree<T>::findLeftMost(AVLTreeNode<T>* tNode)
{
   while (tNode->getLeft() != NULL)
   {
      tNode = tNode->getLeft();
   }
   return tNode->getItem();
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::rotateLeft(AVLTreeNode<T>* tNode)
{
	AVLTreeNode<T>* right = tNode->getRight();
	AVLTreeNode<T>* rightLeft = right->getLeft();
	right->setLeft(tNode);
	tNode->setRight(rightLeft);
	return right;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::rotateRight(AVLTreeNode<T>* tNode)
{
	AVLTreeNode<T>* left = tNode->getLeft();
	AVLTreeNode<T>* leftRight = left->getRight();
	left->setRight(tNode);
	tNode->setLeft(leftRight);
	return left;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DLR(AVLTreeNode<T>* tNode)
{
	AVLTreeNode<T>* left = tNode->getLeft();
	AVLTreeNode<T>* leftRight = left->getRight();
	tNode->setLeft(rotateLeft(left));
	return rotateRight(tNode);
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DRL(AVLTreeNode<T>* tNode)
{
	AVLTreeNode<T>* right = tNode->getRight();
	AVLTreeNode<T>* rightLeft = right->getLeft();
	tNode->setRight(rotateRight(right));
	return rotateLeft(tNode);
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixAddLeft(AVLTreeNode<T>* tNode)
{
	tNode->insertLeft();
	AVL tNodeBalanceFactor = tNode->getBalanceFactor();
	
	if (tNodeBalanceFactor == BALANCED)
	{
		avlFlag = false;
	}
	else if (tNodeBalanceFactor == LEFT_UNBALANCED)
	{
		AVLTreeNode<T>* left = tNode->getLeft();
		AVL leftBalanceFactor = left->getBalanceFactor();
		
		left->setBalanceFactor(BALANCED);
		tNode->setBalanceFactor(BALANCED);
		
		if (leftBalanceFactor == RIGHT_HEAVY)
		{
			avlFlag = false;
			return DLR(tNode, left);
		}
		else
		{
			avlFlag = false;
			return rotateRight(tNode);
		}
	}
		
	return tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixAddRight(AVLTreeNode<T>* tNode)
{
	tNode->insertRight();
	AVL tNodeBalanceFactor = tNode->getBalanceFactor();
	
	if (tNodeBalanceFactor == BALANCED)
	{
		avlFlag = false;
	}
	else if (tNodeBalanceFactor == RIGHT_UNBALANCED)
	{
		AVLTreeNode<T>* right = tNode->getRight();
		AVL rightBalanceFactor = right->getBalanceFactor();
		
		tNode->setBalanceFactor(BALANCED);
		right->setBalanceFactor(BALANCED);
		
		if (rightBalanceFactor == LEFT_HEAVY)
		{
			avlFlag = false;
			return DRL(tNode, right);
		}
		else
		{
			avlFlag = false;
			return rotateLeft(tNode);
		}
	}
	
	return tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DLR(AVLTreeNode<T>* tNode, AVLTreeNode<T>* left)
{
	AVLTreeNode<T>* leftRight = left->getRight();
	AVL leftRightBalanceFactor = leftRight->getBalanceFactor();
	
	leftRight->setBalanceFactor(BALANCED);
	
	if (leftRightBalanceFactor == LEFT_HEAVY)
	{
		tNode->setBalanceFactor(RIGHT_HEAVY);
	}
	else if (leftRightBalanceFactor == RIGHT_HEAVY)
	{
		left->setBalanceFactor(LEFT_HEAVY);
	}
	return DLR(tNode);
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DRL(AVLTreeNode<T>* tNode, AVLTreeNode<T>* right)
{
	AVLTreeNode<T>* rightLeft = right->getLeft();
	AVL rightLeftBalanceFactor = rightLeft->getBalanceFactor();
	
	rightLeft->setBalanceFactor(BALANCED);
	
	if (rightLeftBalanceFactor == LEFT_HEAVY)
	{
		right->setBalanceFactor(RIGHT_HEAVY);
	}
	else if (rightLeftBalanceFactor == RIGHT_HEAVY)
	{
		tNode->setBalanceFactor(LEFT_HEAVY);
	}
	return DRL(tNode);
}


//the below methods have been completed for you

template < class T >
void AVLTree<T>::draw(wxDC&  dc, int width, int height)
{
	Line line(new Color(0, 0, 0), 5.0);
	drawRec(getRootNode(), dc, &line, width, width/2, 20);
}

template < class T >
void AVLTree<T>::drawRec(AVLTreeNode<T>* tNode, wxDC& dc, Line* line, int x_parent, int x_curr, int y_curr)
{

   //traversal to draw the entire binary tree
   if (tNode != NULL)
   {
      //computing the location of the current node's two children
      //the distance between a node's two children is the same as the horizontal distance between
      //the current node and the current node's parent
      //need to do this first as the drawing is from the bottom to the top
      int separation = abs(x_curr - x_parent);

      //need to make sure that the children are symmetrically placed with respect to the parent
      int x_left = x_curr - separation/2;  //the location of the left child
      int x_right = x_left + separation;   //the location of the right child

      //compute the vertical location of the current node's parent
      //and the current node's two children
      int y_parent = y_curr - 50;
      int y_children = y_curr + 50;

      //draw the line connecting the current node to its parent
      if (tNode != root)
      {
         line->draw(dc, x_curr, y_curr, x_parent, y_parent);
      }

      //draw the children
      drawRec(tNode->getLeft(), dc, line, x_curr, x_left, y_children);
      drawRec(tNode->getRight(), dc, line, x_curr, x_right, y_children);

      //draw tNode
      tNode->draw(dc, x_curr, y_curr);
   }
}

template < class T >
void AVLTree<T>::mouseClicked(int x, int y) {}

#endif
