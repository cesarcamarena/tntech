/*
	Name: Cesar Camarena
	Purpose: Program 3
*/
#include "RadixSort.h"
#include "CD.h"
using CSC2110::CD;
#include "ListArray.h"
using CSC2110::ListArray;
#include "ListArrayIterator.h"
using CSC2110::ListArrayIterator;
#include "Text.h"
using CSC2110::String;

#include <iostream>
using namespace std;

void deleteCDs(ListArray<CD>* list)
{
   ListArrayIterator<CD>* iter = list->iterator();

   while(iter->hasNext())
   {
      CD* cd = iter->next();
      delete cd;
   }
   delete iter;
}

int main()
{
   ListArray<CD>* list = CD::readCDs("cds.txt");
   int size = list->size();

   CD** cds = new CD*[size];

   ListArrayIterator<CD>* iter = list->iterator();
   int count = 0;
   while(iter->hasNext())
   {
      CD* cd = iter->next();
      cds[count] = cd;
      count++;
   }
   delete iter;

   //DO THIS
   //test both radix sort methods using the cds array
   
   CD** sortedCDS = new CD*[size];
   
   sortedCDS = RadixSort<CD>::radixSort(cds, size, 500, true, &CD::getRadixChar);  //sorts the sortedCDs in ascending order
   
   iter = list->iterator();
   
   count = 0;
   
   String* messageOfTitle = new String("\n\nI AM ONLY DISPLAYING THE TITLE OF THE ALBUM'S TO MAKE IT CLEANER. PRESS ENTER TO SORT ASCENDINGLY.\n");
   messageOfTitle->displayString();
   cin.ignore();
   delete messageOfTitle;
   
   while (iter->hasNext())  //displays the data in ascending order
   {
	   iter->next();
	   
	   CD* cd = sortedCDS[count];
	   
	   String* key = cd->getKey();
	   
	   key->displayString();
	   
	   cout << endl;
	   
	   count++;
   }
   
   delete iter;
   
   sortedCDS = RadixSort<CD>::radixSort(cds, size, 500, false, &CD::getRadixChar);  //sorts the sorted CDS in descending order
   
   iter = list->iterator();
   
   count = 0;
   
   while (iter->hasNext())  //displays the data in descending order
   {
	   iter->next();
	   
	   CD* CD = sortedCDS[count];
	   
	   String* key = CD->getKey();
	   
	   key->displayString();
	   
	   cout << endl;
	   
	   count++;
   }

   delete[] cds;

   deleteCDs(list);
   delete list;

   return 0;
}
