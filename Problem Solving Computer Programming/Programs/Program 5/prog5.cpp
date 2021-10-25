/*
	Program Name: prog5.cpp
	Author: Cesar Camarena
	Date: 11/28/2016
	Purpose: Program 5
*/

#include "prog5.h"

int main()
{
	int choice;						//Holds the value for the menu choice
	int creatures = 0;				//Counter for the creatures
	Creatures myCreatures[100];		//Holds the data for the creatures
	char saveCreatures;				//Holds the value whether the user wants to save
	
	do
	{
		//Prints out the Menu
		cout << "What would you like to do?" << endl;
		cout << "\t1. Enter some Magical Creatures" << endl;
		cout << "\t2. Delete a Magical Creature." << endl;
		cout << "\t3. List/Print Creatures." << endl;
		cout << "\t4. Print Statistics on Creature Cost." << endl;
		cout << "\t5. End Program." << endl;
		cout << "CHOICE:  ";
		cin >> choice;
		
		//Input Validation
		while (choice < 1 || choice > 5)
		{
			cout << "\nERROR! Enter a valid answer." << endl;
			cout << "\nWhat would you like to do?" << endl;
			cout << "\t1. Enter some Magical Creatures" << endl;
			cout << "\t2. Delete a Magical Creature." << endl;
			cout << "\t3. List/Print Creatures." << endl;
			cout << "\t4. Print Statistics on Creature Cost." << endl;
			cout << "\t5. End Program." << endl;
			cout << "\tEnter 1, 2, 3, 4, or 5." << endl;
			cout << "CHOICE:  ";
			cin >> choice;
		}
		
		//Choice will select the function the user wishes to use
		switch(choice)
		{
			case 1: creatures = enterCreatures(myCreatures, creatures);
					break;
			
			case 2: deleteCreature(myCreatures, creatures);
					break;
					
			case 3: printCreatures(myCreatures, creatures);
					break;
			
			case 4: printStatistics(myCreatures, creatures);
					break;
			
			case 5: cout << "\nDo you wish to save your creature list to a file?" << endl;
					cin >> saveCreatures;
					
					while (saveCreatures != 'Y' && saveCreatures != 'y' && saveCreatures != 'N' && saveCreatures != 'n')
					{
						cout << "\nERROR: Enter a valid answer!" << endl;
						cout << "Do you wish to save your creature list to a file?" << endl;
						cin >> saveCreatures;
					}
					
					if (saveCreatures == 'Y' || saveCreatures == 'y')
					{
						saveCreaturesToFile(myCreatures, creatures);
					}
					break;
		}
		
	}while (choice < 6);
	
	return 0;
}