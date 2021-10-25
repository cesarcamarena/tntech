/*
	Program Name: inventory.cpp
	Author: Cesar Camarena
	Date: 11/30/2016
	Purpose: lab12
*/
#include <iostream>
using namespace std;

//structure
struct Soap
{
	string description;
	int parts;
};

//function prototypes
void addParts(Soap*, int);
void removeParts(Soap*, int);

const int SIZE = 10;

//main function
int main()
{
	int binNum;
	char addOrRemove;
	
	Soap inventory[SIZE] = {
							{"Olive Oil", 10},
							{"Essential Oils", 5},
							{"Coconut Oil", 15},
							{"Waxes and Butters", 21},
							{"Decorative Botanicals", 7},
							{"Clays", 5},
							{"Colors", 5},
							{"Glycerin", 25},
							{"Sodium Laureth Sulfate(SLES)", 18},
							{"Perservatives", 12}
						   };
	do
	{
		for (int x = 0; x < SIZE; x++)
		{
			cout << "Bin #  " << (x + 1) << ",  Part: " << inventory[x].description;
			cout << ", Quantity: " << inventory[x].parts << endl;
		}
		
		cout << "\nEnter 0 to quit, or choose a bin Number: ";
		cin >> binNum;
		
		//input validation
		while (binNum < 0 || binNum > 10)
		{
			cout << "\nEnter a valid answer!" << endl;
			cout << "Enter 0 to quit, or choose a bin Number; ";
			cin >> binNum;
		}
		
		if (binNum != 0)
		{
			cout << "Add or Remove Parts (A or R)?  ";
			cin >> addOrRemove;
		}
		
		while (addOrRemove != 'A' && addOrRemove != 'R' && addOrRemove != 'a' && addOrRemove != 'r' && binNum != 0)
		{
			cout << "\nEnter a valid answer!" << endl;
			cout << "Add or Remove Parts (A or R)?  ";
			cin >> addOrRemove;
		}
		
		if ((addOrRemove == 'A' && binNum != 0) || (addOrRemove == 'a' && binNum != 0))
		{
			addParts(inventory, binNum);
		}
		
		if ((addOrRemove == 'R' && binNum != 0)|| (addOrRemove == 'r' && binNum !=0))
		{
			removeParts(inventory, binNum);
		}
		
	} while (binNum != 0);
		
	return 0;
}

void addParts(Soap* inventory, int binNum)
{
	int addedParts;
	
	cout << "How many parts to add? ";
	cin >> addedParts;
	
	//input validation
	while (addedParts < 0)
	{
		cout << "Error: Use positive values." << endl;
		cout << "\nHow many parts to add? ";
		cin >> addedParts;
	}
	
	while (addedParts + inventory[binNum - 1].parts > 30)
	{
		cout << "\nError: The bin can only hold 30 parts." << endl;
		cout << "How many parts to add? ";
		cin >> addedParts;
	}
	
	while (addedParts < 0)
	{
		cout << "Error: Use positive values." << endl;
		cout << "\nHow many parts to add? ";
		cin >> addedParts;
	}
	
	inventory[binNum - 1].parts += addedParts;
}

void removeParts(Soap* inventory, int binNum)
{
	int removedParts;
	
	cout << "How many parts to remove? ";
	cin >> removedParts;
	
	//input validation
	while (removedParts < 0)
	{
		cout << "\nError: Use positive values." << endl;
		cout << "How many parts to remove? ";
		cin >> removedParts;
	}
	
	while (removedParts > inventory[binNum - 1].parts)
	{
		cout << "\nError: You are attempting to remove more parts ";
		cout << "than the bin is holding." << endl;
		cout << "How many parts to remove? ";
		cin >> removedParts;
	}
	
	while (removedParts < 0)
	{
		cout << "\nError: Use positive values." << endl;
		cout << "How many parts to remove? ";
		cin >> removedParts;
	}
	
	inventory[binNum - 1].parts -= removedParts;
}