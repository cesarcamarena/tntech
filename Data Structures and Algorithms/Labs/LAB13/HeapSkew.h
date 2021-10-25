/*
	Cesar Camarena
	Jeremiah Payne
	Lab 13
*/
#if !defined HEAPSKEW_H
#define HEAPSKEW_H

#include "BinaryTree.h"
#include "wx/wx.h"

template < class T >
class HeapSkew : public Drawable
{

   private:
      BinaryTree<T>* bt;
      int sze;
      BinaryTree<T>* merge(BinaryTree<T>* left, BinaryTree<T>* right);

      int (*compare_items) (T* item_1, T* item_2);

   public:
      HeapSkew(int (*comp_items) (T* item_1, T* item_2));
      ~HeapSkew();

      bool heapIsEmpty();
      void heapInsert(T* item);
      T* heapRemove();

      void draw(wxDC& dc, int width, int height);
      void mouseClicked(int x, int y);

};

// this is a MAXHEAP (largest items to top alphabetical order)
template < class T >
HeapSkew<T>::HeapSkew(int (*comp_items) (T* item_1, T* item_2)) : Drawable()
{ 
   bt = new BinaryTree<T>();
   sze = 0;

   compare_items = comp_items;
}

template < class T >
HeapSkew<T>::~HeapSkew() 
{ 
   delete bt;
}  

template < class T >
bool HeapSkew<T>::heapIsEmpty()
{
   return sze == 0;
}

template < class T >
BinaryTree<T>* HeapSkew<T>::merge(BinaryTree<T>* left, BinaryTree<T>* right)
{
  //DO THIS
  
	if(left->isEmpty())
	{
		delete left;
		return right;
	}
	else if (right->isEmpty())
	{
		delete right;
		return left;
	}
	else
	{
		T* leftItem = left->getRootItem();
		T* rightItem = right->getRootItem();
		
		int compare = (*compare_items) (leftItem, rightItem);
		
		if (compare < 0)
		{
			return merge(right, left);
		}
		else
		{
			BinaryTree<T>* LL = left->detachLeftSubtree();
			BinaryTree<T>* LR = left->detachRightSubtree();
			
			left->attachRightSubtree(LL);
			delete LL;
			
			if (LR->isEmpty())
			{
				left->attachLeftSubtree(right);
				delete right;
				delete LR;
				
				return left;
			}
			else
			{
				BinaryTree<T>* mergedTree = merge(LR, right);
				left->attachLeftSubtree(mergedTree);
				delete mergedTree;
				return left;
			}
		}
	}
	
	

}

template < class T >
void HeapSkew<T>::heapInsert(T* item)
{
   //DO THIS (calls merge, should be short)
   BinaryTree<T>* itemInserted = new BinaryTree<T>(item);
   
   bt = merge(bt, itemInserted);
   
   sze++;
}

template < class T >
T* HeapSkew<T>::heapRemove()
{
   //DO THIS (calls merge, should be short)
   
   T* item = bt->getRootItem();
   
   BinaryTree<T>* leftSubtree = bt->detachLeftSubtree();
   BinaryTree<T>* rightSubtree = bt->detachRightSubtree();
   
   delete bt;
   
   bt = merge(leftSubtree, rightSubtree);
   
   sze--;
   
   return item;

}

template < class T >
void HeapSkew<T>::draw(wxDC& dc, int width, int height)
{
   bt->draw(dc, width, height);
}

template < class T >
void HeapSkew<T>::mouseClicked(int x, int y) {bt->mouseClicked(x, y);}

#endif
