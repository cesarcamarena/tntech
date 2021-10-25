/*
	Name: Cesar Camarena
	Purpose: Program 1
*/
#include "SortedListArray.h"
#include "CD.h"
using CSC2110::CD;
#include "ListArray.h"
using CSC2110::ListArray;
#include "ListArrayIterator.h"
using CSC2110::ListArrayIterator;

using CSC2110::SortedListArray;

#include <iostream>
using namespace std;

void addCDs(ListArray<CD>* cds, SortedListArray<CD>* sortedCDs)
{
	ListArrayIterator<CD>* iter = cds->iterator();
	
	while (iter->hasNext())
	{
		sortedCDs->add(iter->next());
	}
}

void deleteCDs(ListArray<CD>* cds)
{
   ListArrayIterator<CD>* iter = cds->iterator();

   while(iter->hasNext())
   {
      CD* cd = iter->next();
      delete cd;
   }
   delete iter;
}

int main()
{
   ListArray<CD>* cds = CD::readCDs("cds.txt");	//TESTS FOR ONLY 7 CDS

   //thoroughly test your sorted list here
   SortedListArray<CD>* sortedCDs = new SortedListArray<CD>(&CD::compare_items, &CD::compare_keys);

   //Testing to see if size function works
   if (sortedCDs->isEmpty())
   {
	   cout << "Sorted list is empty...for now.\n" << endl;
   }
   
   //Add CDs here to make it not empty anymore
   
   addCDs(cds, sortedCDs);
   
   cout << "The sorted list shouldn't be empty anymore\n" << endl;
   
   //Displays the size of the sortedListArray
   if (!(sortedCDs->isEmpty()))
   {
	   cout << "The size of the sorted list is: " << sortedCDs->size() << endl;
   }
   
   cout << "---------------------------------------------------------------------\n";
   
   ListArrayIterator<CD>* iter = sortedCDs->iterator();
   
   //Displays everything in the sortedListArray
   while (iter->hasNext())
   {
	   CD* cd = iter->next();
	   cd->displayCD();
   }
   
   delete iter;
   
   cout << "Going to remove the band Obscura\n\n";
   
   cout << "---------------------------------------------------------------------\n";
   //Going to test the remove function
   
   
   //Removes the artist Obscura
   String* artist = new String("Obscura");
   sortedCDs->remove(artist);
   
   iter = sortedCDs->iterator();
   while (iter->hasNext())
   {
	   CD* cd = iter->next();
	   cd->displayCD();
   }

   if (!(sortedCDs->isEmpty()))
   {
	   cout << "The new size of the sorted list is: " << sortedCDs->size() << endl << endl;
   }
   
   cout << "---------------------------------------------------------------------\n";
   
   
   delete iter;
   
   //Going to test the get function
   
   cout << "Obtaining the Misery Index CD" << endl;
   
   artist = new String("Misery Index");
   
   CD* cd = sortedCDs->get(artist);
   
   cd->displayCD();
   
   cout << "---------------------------------------------------------------------\n";
   
   //Going to test the add function to see if I can add a cd
   
   cout << "Going to add Drake to my CDs" << endl << endl;
   
   artist = new String("Drake");
   String* title = new String("One Dance");
   CD* newCD = new CD(artist, title, 2015, 10, 1);
   
   sortedCDs->add(newCD);
   
   //Displays the sorted list with the new cd
   iter = sortedCDs->iterator();
   while (iter->hasNext())
   {
	   CD* cd = iter->next();
	   cd->displayCD();
   }
   
   delete iter;
   
   
   //Displays the size of the sorted list
   if (!(sortedCDs->isEmpty()))
   {
	   cout << "The size of the sorted list is: " << sortedCDs->size() << endl;
   }
   
   //Removes the newly added artist
   sortedCDs->remove(artist);
   
   //Attempts to get the newly added artist (should obtain nothing).
   cd = sortedCDs->get(artist);
   
   
   cout << "---------------------------------------------------------------------\n";
   
   //Makes sure Drake has been deleted
   if (cd == NULL)
   {
	   cout << "Drake has been deleted!\n" << endl; //Validating items that aren't there worked
   }
   
   //Attempting to remove Drake again
   cout << "Going to remove Drake again\n" << endl;
   
   //This time it will display that the artist was not found
   sortedCDs->remove(artist);
   
   iter = sortedCDs->iterator();
   while (iter->hasNext())
   {
	   CD* cd = iter->next();
	   cd->displayCD();
   }
   
   if (!(sortedCDs->isEmpty()))
   {
	   cout << "The final size of the sorted list is: " << sortedCDs->size() << endl;
   }
   
   
   delete iter;
   

   delete artist;
   delete title;
   delete newCD;
   
   delete sortedCDs;

   deleteCDs(cds);
   delete cds;

   return 0;
}
