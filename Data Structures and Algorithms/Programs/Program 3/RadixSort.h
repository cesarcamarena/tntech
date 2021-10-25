/*
	Name: Cesar Camarena
	Purpose: Program 3
*/
#if !defined (RADIXSORT_H)
#define RADIXSORT_H

#include "QueueLinked.h"
using CSC2110::QueueLinked;

template < class T >
class RadixSort
{
   private:
   
    /*pre: Takes in an unsorted bin, the current character that the algorithm is sorting by,
	       the max number of characters, and a function pointer to sort the data in the bin.
	  post: Creates a sorted bin that has its data in ascending order.*/
      static void binSort(QueueLinked<T>* bin, int curr_char, int num_chars, char (*getRadixChar) (T* item, int index));
	  
	/*pre: Takes in an unsorted array named sort so that we know it is the array that we need to sort,
	       the current character that the algorithm is sorting by, the max number of characters, and a
		   function pointer to sort the data for the sort array.
	  post: Creates a sorted sort array that has its data in ascending data (aka alphabetical order).*/
      static void radixSortAsc(T** sort, int n, int num_chars, char (*getRadixChar) (T* item, int index));  //algorithm 1
	  
	/*pre: Again, it takes in an unsorted array named sort so that we know it is the array that we need
	       to sort, the current character that the algorithm is sorting by, the max number of characters,
		   and a function pointer to sort the data for the sort array.
	  post: Creates a sorted sort array that has its data in descending data (aka reverse alphabetical
	        order).*/
      static void radixSortDesc(T** sort, int n, int num_chars, char (*getRadixChar) (T* item, int index));  //algorithm 2
 
   public:
   
    /*pre: Takes in an unsorted array named unsorted, the number of times that the algorithm needs to sort
	       the data within the array, the max number of characters, a bool variable named asc to tell the 
		   function to order the data in ascending order or in descending order, and again a function pointer
		   to sort the data in the array.
	  post: Creates a sorted sort array that has its data in either ascending or descending order
	        depending on the bool variable asc.*/
      static T** radixSort(T** sort, int num_to_sort, int num_chars, bool asc, char (*getRadixChar) (T* item, int index));
};

template < class T >
T** RadixSort<T>::radixSort(T** unsorted, int num_to_sort, int num_chars, bool asc, char (*getRadixChar) (T* item, int index))
{
   //DO THIS
   
   T** sorted = new T*[num_to_sort];
   
   for (int i = 0; i < num_to_sort; i++)  //copies the data within the unsorted array into the sorted array
   {
	   sorted[i] = unsorted[i];
   }
   
   if (asc)  //sorts the data within the sorted array in ascending order
   {
	   radixSortAsc(sorted, num_to_sort, num_chars, getRadixChar);
   }
   
   else  //sorts the data within the sorted array in descending order
   {
	   radixSortDesc(sorted, num_to_sort, num_chars, getRadixChar);
   }


	return sorted;
}

template < class T >
void RadixSort<T>::radixSortAsc(T** sort, int n, int num_chars, char (*getRadixChar) (T* st, int index))
{
   //DO THIS
   
   QueueLinked<T>* bin = new QueueLinked<T>();
   
   for (int i = 0; i < n; i++)  //copies the data within the sort array into a single bin
   {
	   bin->enqueue(sort[i]);
   }

   binSort(bin, 1, num_chars, getRadixChar);  //sorts the data within the bin in ascending order
   
   for (int i = 0; i < n; i++)  //takes out the data within the sorted bin and puts it into the sort array
   {
	   sort[i] = bin->dequeue();
   }

   delete bin;
}

template < class T >
void RadixSort<T>::binSort(QueueLinked<T>* bin, int curr_char, int num_chars, char (*getRadixChar) (T* st, int index))
{
   //DO THIS
   
   int num_queues = 37;
   QueueLinked<T>** bins = new QueueLinked<T>*[num_queues];
   
   if (curr_char > num_chars)  //in case the current character is somehow higher than the max number of characters
   {
	   return;
   }
   
   for (int i = 0; i < num_queues; i++)  //creates the 37 bins for special characters, letters, and numbers
   {
	   bins[i] = new QueueLinked<T>();
   }
   
   int sz = bin->size();  //takes in the size of the bin
   
   for (int i = 0; i < sz; i++)  //sorts the data from the bin into bins based on its ascii
   {
	   int index;
	   
	   int ascii = (*getRadixChar) (bin->peek(), curr_char);
	   
	   if (ascii >= 65 && ascii <= 91)
	   {
		   ascii += 32;
	   }
	   
	   if (ascii >= 48 && ascii <= 57)
	   {
		   index = ascii - 47;
	   }
	   
	   if (ascii >= 97 && ascii <= 122)
	   {
		   index = ascii - 86;
	   }
	   
	   else
	   {
		   index = 0;
	   }
	   
	   bins[index]->enqueue(bin->dequeue());
   }
   
   for (int i = 0; i < num_queues; i++)  //recurively calls binSort in case there is more than one node within a bin
   {
       int binSize = bins[i]->size();
		   
	   if (binSize > 1)
       {
           binSort(bins[i], curr_char + 1, num_chars, getRadixChar);
       }
   }
	   
   for (int i = 0; i < num_queues; i++)  //takes out the data within each bin from bins into a single, sorted bin
   {
	   int binSize = bins[i]->size();
	   
	   if (binSize > 0)
       {
		   for (int h = 0; h < binSize; h++)
		   {
			   bin->enqueue(bins[i]->dequeue());
		   }
	   }
   }

   for (int i = 0; i < num_queues; i++)
   {
	   delete bins[i];
   }
   
   delete[] bins;
}

template < class T >
void RadixSort<T>::radixSortDesc(T** sort, int n, int num_chars, char (*getRadixChar) (T* st, int index))
{
   int num_queues = 37;  //covers letters and digits
   QueueLinked<T>** bins = new QueueLinked<T>*[num_queues];  

   //must instantiate each of the queues
   for (int i = 0; i < num_queues; i++)
   {
      //DO THIS
	  bins[i] = new QueueLinked<T>();
   }

   for (int i = num_chars; i > 0; i--)  //number of times to bin stuff
   {
      //DO THIS
	  
	  for (int h = 0; h < n; h++)  //loops from 0 to the size of the data
	  {
		  int index;
		  
		  int ascii = (*getRadixChar) (sort[h], i);
		  
		  if (ascii >= 65 && ascii <= 91)
		  {
			  ascii += 32;
		  }
		  
		  if (ascii >= 48 && ascii <= 57)
		  {
			  index = ascii - 47;
		  }
		  
		  if (ascii >= 97 && ascii <= 122)
		  {
			  index = ascii - 86;
		  }
		  
		  else
		  {
			  index = 0;
		  }
		  
		  bins[index]->enqueue(sort[h]);
	  }
	  
	  int index = 0;
	  
	  for (int i = 36; i >= 0; i--)  //takes out the data in descending order
	  {
		  while (!bins[i]->isEmpty())
	      {
			  sort[index] = bins[i]->dequeue();
			  index++;
		  }
	  }
   }

   for (int i = 0; i < num_queues; i++) 
   {
      delete bins[i];
   }

   delete[] bins;
}

#endif
