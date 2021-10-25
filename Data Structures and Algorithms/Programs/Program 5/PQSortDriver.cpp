/*
	Name: Cesar Camarena
	Purpose: Program 5
*/
#include "PQSort.h"
#include "CD.h"
#include "ListArray.h"
#include "Text.h"
using namespace CSC2110;

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
	String* messageOfTitle = new String("I AM ONLY DISPLAYING THE TITLE OF THE ALBUM'S TO MAKE IT CLEANER. PRESS ENTER TO SORT ASCENDINGLY.\n");
    messageOfTitle->displayString();
    cin.ignore();
    delete messageOfTitle;
	
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
	

	
	cds = PQSort<CD>::pqSort(cds, size, true, &CD::compare_items, &CD::compare_keys);
	
	iter = list->iterator();
	
	count = 0;
	while(iter->hasNext())
	{
	   iter->next();
	   
	   CD* cd = cds[count];
	   
	   String* key = cd->getKey();
	   
	   key->displayString();
	   
	   cout << endl;
	   
	   count++;
	}
	
	delete iter;
	
	String* testDescending = new String("\n\t\t\t\t\tPRESS ENTER FOR DESCENDING ORDER.\n");
    testDescending->displayString();
    cin.ignore();
    delete testDescending;
	
	cds = PQSort<CD>::pqSort(cds, size, false, &CD::compare_items, &CD::compare_keys);
	
	iter = list->iterator();
	
	count = 0;
	while(iter->hasNext())
	{
	   iter->next();
	   
	   CD* cd = cds[count];
	   
	   String* key = cd->getKey();
	   
	   key->displayString();
	   
	   cout << endl;
	   
	   count++;
	}
	
	delete iter;
	
	delete[] cds;
	deleteCDs(list);
	
	return 0;
}