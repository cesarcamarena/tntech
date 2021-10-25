/*
	Name: Cesar Camarena
	Purpose: Program 1
*/
#if !defined (SORTEDLISTARRAY_H)
#define SORTEDLISTARRAY_H

#include "Text.h"
using CSC2110::String;

#include "ListArrayIterator.h"
using CSC2110::ListArrayIterator;

#include <iostream>
using namespace std;

namespace CSC2110
{
template < class T >
class SortedListArray
{
   private:
      int max_size;
	  T** items;
      int sz;

      void arrayResize(int new_max_size);
      
	  int (*compare_items)(T* item_1, T* item_2);
      int (*compare_keys)(String* search_key, T* item);
	  
	  int computeAddIndex(T* item);
	  int computeRemoveIndex(String* search_key);
	  
   public:
	/*pre:  Nothing.
	  post: Creates the array, initializes the max size of the array and size of array.*/
      SortedListArray (int (*comp_items)(T* item_1, T* item_2), int (*comp_keys)(String* search_key, T* item));
      
	/*pre:  Nothing.
	  post: Deconstructs the array*/
	  ~SortedListArray();

	/*pre:  Nothing.
	  post: Returns true or false whether the array is empty or not*/
      bool isEmpty();
	  
	/*pre:  Nothing.
	  post: Returns the size of the array*/
      int size();

    /*pre:  search_key is passed into the function
      post: The item at the specified search_key is returned*/
      T* get(String* search_key);

    /*pre:  The item is passed into the function
      post: The item is added to the list at its computed index
			which will sort the item correctly in the array, however
			if the array is full then it will resize the array and
			then add the item to the array.*/
      void add(T* item);

     /*pre:  search_key is passed into the function
       post: The item is removed by its search key, however
			 if the item was not found then it will return nothing.
			 Then it will decrement the size of the list by one.*/
      void remove(String* search_key);

      ListArrayIterator<T>* iterator();
};

template < class T >
SortedListArray<T>::SortedListArray (int (*comp_items)(T* item_1, T* item_2), int (*comp_keys)(String* key, T* item))
{
  max_size = 2;
  items = new T*[max_size];
  sz = 0;

  //Copy the memory address of the function into a private instance variable
  compare_items = comp_items; 
  compare_keys = comp_keys;	
}

template < class T >
SortedListArray<T>::~SortedListArray()
{
   delete[] items;  //The items themselves are not deleted
}

template < class T >
int SortedListArray<T>::computeAddIndex(T* item)
{
	int f = 0;	//First
	int l = sz - 1;	//Last
	int m = f + ((l - f) / 2);	//Middle
	
	while (f <= l)	//Binary search for add
	{
		int compare = (*compare_items)(item, items[m]);
		
		if (compare == 0)	//If found, return its location
		{
			return m + 1;
		}
		
		else if (compare < 0)	//If the item is in the first half of the array, set last to middle
		{
			l = m - 1;
		}
		
		else	//If item is in the last half of the array, set first to the middle
		{
			f = m + 1;
		}
		
		m = f + ((l - f) / 2);
	}
	
	return m + 1;	//If not found, return the index of middle + 1
}


template < class T >
int SortedListArray<T>::computeRemoveIndex(String* search_key)
{
	int f = 0;	//First
	int l = sz - 1;	//Last
	int m = f + ((l - f) / 2);	//Middle
	
	
	while (f <= l)	//binary search for remove
	{
		int compare = (*compare_keys)(search_key, items[m]);
		
		if (compare == 0)	//If found, returns the location
		{
			return m + 1;
		}
		
		else if (compare < 0)	//If the item is in the first half of the array, set last to middle
		{
			l = m - 1;
		}
		
		else	//If item is in the last half of the array, set first to the middle
		{
			f = m + 1;
		}
		
		m = f + ((l - f) / 2);
	}
	
	return -1;	//If not found, return -1
}

template < class T >
bool SortedListArray<T>::isEmpty()
{
   return (sz == 0);	//Returns a bool whether the array is empty or not
}

template < class T >
int SortedListArray<T>::size()
{
   return sz;	//Returns the size of the array
}

template < class T >
T* SortedListArray<T>::get(String* search_key)
{
   T* item = NULL;
   
   if (search_key == NULL)	//If they're not searching for anything, return nothing
   {
	   return NULL;
   }
   
	int index = computeRemoveIndex(search_key);
	
	if (index != -1)	//If the computeRemoveIndex found the item, gets the item
	{
		item = items[index - 1];
	}

   return item;
}

template < class T >
void SortedListArray<T>::add(T* item)
{
   int index = computeAddIndex(item);
	
   //If you're not passing anything to the array, return nothing
   if (item == NULL)
   {
	   return;
   }

   //If the array needs more room
   if (sz == max_size) 
   {
      arrayResize(2*max_size);
   }  
 
   //Rearranges the array
   for (int i = sz; i >= index; i--)
   { 
      items[i] = items[i - 1];
   }

   items[index - 1] = item;
   sz++;	//Increases the size of the array
}

template < class T >
void SortedListArray<T>::remove(String* search_key)
{
   int index = computeRemoveIndex(search_key);
   
   //If you're not passing anything to the array, return nothing
   if (search_key == NULL)
   {
      return;
   }

   //If the list is empty, return nothing since there is nothing to remove
   if (isEmpty())
   {
      return;
   }
   
   //If the item was not found from the computeRemoveIndex function by the search key. Return nothing.
   if (index == -1)
   {
	   cout << "This artist was not found.\n\n";  //This is used to test
												  //when you are removing
												  //an artist that isn't in
												  //the list.
	   return;
   }
   
   //Rearranges the array
   for (int i = index; i < sz; i++)
   {
      items[i - 1] = items[i];
   }

   items[sz - 1] = NULL;
   sz--;	//Decrements the size of the array

}

template < class T >
ListArrayIterator<T>* SortedListArray<T>::iterator()
{
   ListArrayIterator<T>* iter = new ListArrayIterator<T>(items, sz);
   return iter;	//Returns the created iterator
}

template < class T >
void SortedListArray<T>::arrayResize(int new_max_size)
{
   max_size = new_max_size;
   T** temp = new T*[max_size];

   for (int i = 0; i < sz; i++)	//Copies the data from the array to the newly created one
   {
      temp[i] = items[i];
   }

   delete[] items;
   items = temp;
}
}

#endif
