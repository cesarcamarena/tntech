/*
	Name: Cesar Camarena
	Purpose: Program 5
*/
#if !defined (PQSort_H)
#define PQSort_H

#include "PQAVL.h"

template < class T >
class PQSort
{
	private:
	  /*pre:  Takes in the unsorted array of items, whether the top of the PQAVL will be the max or min, and the two function pointers
	    post: Sorts and returns the unsorted array*/
		static void _pqSort(T** items, int num_items, bool min_or_max, int (*compare_item) (T* one, T* two), int (*compare_key) (String* key, T* item)); //sorts the array using PQAVL
	
	public:
	  /*pre:  Takes in the unsorted array of items, whether the top of the PQAVL will be the max or min, and the two function pointers
	    post: Returns sorted array*/
		static T** pqSort(T** items, int num_items, bool min_or_max, int (*compare_item) (T* one, T* two), int (*compare_key) (String* key, T* item)); //public method to create and return a new, sorted array in case the original unsorted array must be kept
};

template < class T >
T** PQSort<T>::pqSort(T** items, int num_items, bool min_or_max, int (*compare_item) (T* one, T* two), int (*compare_key) (String* key, T* item))
{
	T** sort = new T*[num_items];
	
	for (int i = 0; i < num_items; i++)
	{
		sort[i] = items[i];
	}
	
	_pqSort(sort, num_items, min_or_max, compare_item, compare_key);
	
	return sort;
}

template < class T >
void PQSort<T>::_pqSort(T** items, int num_items, bool min_or_max, int (*compare_item) (T* one, T* two), int (*compare_key) (String* key, T* item))
{
	PQAVL<T>* pqTree = new PQAVL<T>(min_or_max, compare_item, compare_key);
	
	for(int i = 0; i < num_items; i++)
	{
		pqTree->pqInsert(items[i]);
	}
	
	for(int i = 0; i < num_items; i++)
	{
		items[i] = pqTree->pqRemove();
	}
}
#endif