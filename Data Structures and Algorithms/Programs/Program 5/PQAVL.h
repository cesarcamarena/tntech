/*
	Name: Cesar Camarena
	Purpose: Program 5
*/
#if !defined (PQAVL_H)
#define PQAVL_H

#include "AVLTree.h"

template < class T >
class PQAVL
{
	private:
		AVLTree<T>* avl;
		bool min_or_max;
		
		int (*compare_item) (T* item_1, T* item_2);
		int (*compare_key) (String* key, T* item);
		
	public:
      /*pre:  Takesk int a bool whether the top is the max or min, and the 2 function pointers
	    post: Constructs a PQAVL*/
		PQAVL(bool min_or_max, int (*compare_item) (T* item_1, T* item_2), int (*compare_key) (String* key, T* item)); //constructor
		
	  /*pre:  Nothing.
	    post: Deconstructs the PQAVL*/
		~PQAVL(); //destructor
		
	  /*pre:  Nothing.
	    post: Returns true or false whether the PQAVL is empty or not*/
		bool pqIsEmpty();
		
	  /*pre:  Takes in the item you are inserting.
	    post: Inserts the item in its correct spot*/
		void pqInsert(T* item);
		
	  /*pre:  Nohthing.
	    post: Removes either the smallest or largest item in the priority queue and returns it*/
		T* pqRemove(); //removes and returns the smallest or largest item in the priority queue
};

template < class T >
PQAVL<T>::PQAVL(bool min_or_max, int (*compare_item) (T* item_1, T* item_2), int (*compare_key) (String* key, T* item))
{
	avl = new AVLTree<T>(min_or_max, true, true, compare_item, compare_key);
}

template < class T >
PQAVL<T>::~PQAVL()
{
	delete avl;
}

template < class T >
bool PQAVL<T>::pqIsEmpty()
{
	return avl->isEmpty();
}

template < class T >
void PQAVL<T>::pqInsert(T* item)
{
	avl->insert(item);
}

template < class T >
T* PQAVL<T>::pqRemove()
{
	return avl->remove();
}
#endif