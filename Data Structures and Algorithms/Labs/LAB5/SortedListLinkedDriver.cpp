/*
	Cesar Camarena
	Shubham Patel
	Lab 5
*/
#include "SortedListLinked.h"
#include "CD.h"
using CSC2110::CD;
#include "ListArray.h"
using CSC2110::ListArray;
#include "ListArrayIterator.h"
using CSC2110::ListArrayIterator;
#include <iostream>
using namespace std;

void addCDs(ListArray<CD>* list, SortedListLinked<CD>* lb)
{
   ListArrayIterator<CD>* iter = list->iterator();

   //DO THIS
   //iterate over and add the cds to the list box (use lb->addItem)
	while (iter->hasNext())
	{
		CD* cd = iter->next();
		lb->add(cd);
	}


   delete iter;
}

void deleteCDs(ListArray<CD>* list)
{
   ListArrayIterator<CD>* iter = list->iterator();

   //DO THIS  
   //iterate over and delete the cds
	while (iter->hasNext())
	{
		CD* cd = iter->next();
		delete cd;
	}



   delete iter;
}

int main(int argc, char* argv[])
{
   ListArray<CD>* cds = CD::readCDs("testCDs.txt");
   //DO THIS
   //create and test the sorted linked list 
   SortedListLinked<CD>* lb = new SortedListLinked<CD>(&CD::compare_items);
   
   addCDs(cds, lb);
   
   //this tests with 5 CDs to see if it displays them in order
   ListLinkedIterator<CD>* iter = lb->iterator();
   while (iter->hasNext())
   {
	   CD* cd = iter->next();
	   cd->displayCD();
   }
   
   delete iter;
   deleteCDs(cds);
   delete cds;
   delete lb;
   
   cout << "-------------------------------------------------------------------------------------------------------\n\n";
   //separates tests
   
   //this tests with 10 CDs to see if it displays them order
   cds = CD::readCDs("testCDs2.txt");
   lb = new SortedListLinked<CD>(&CD::compare_items);
   
   addCDs(cds, lb);
   
   iter = lb->iterator();
   while (iter->hasNext())
   {
	   CD* cd = iter->next();
	   cd->displayCD();
   }
   
   delete iter;
   deleteCDs(cds);
   delete cds;
   delete lb;
   
   
   
   cout << "-------------------------------------------------------------------------------------------------------\n\n";
   //separates tests
   
   //this tests the remove and get function with 5 CDs and displays them in order
   cds = CD::readCDs("testCDs.txt");
   lb = new SortedListLinked<CD>(&CD::compare_items);
   
   addCDs(cds, lb);
   
   CD* removedCD = cds->get(2);
   lb->remove(removedCD);
   
   removedCD = cds->get(3);
   lb->remove(removedCD);
   
   removedCD = cds->get(4);
   lb->remove(removedCD);
   
   iter = lb->iterator();
   while (iter->hasNext())
   {
	   CD* cd = iter->next();
	   cd->displayCD();
   }
   
   delete iter;
   deleteCDs(cds);
   delete cds;
   delete lb;

   cout << "-------------------------------------------------------------------------------------------------------\n\n";
   //separates tests
   
   //this tests with all CDs to see if it displays them order
   cds = CD::readCDs("cds.txt");
   lb = new SortedListLinked<CD>(&CD::compare_items);
   
   addCDs(cds, lb);
   
   iter = lb->iterator();
   while (iter->hasNext())
   {
	   CD* cd = iter->next();
	   cd->displayCD();
   }
   
   delete iter;
   deleteCDs(cds);
   delete cds;
   delete lb;
   
   return 0;
}