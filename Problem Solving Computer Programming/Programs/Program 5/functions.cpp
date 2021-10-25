/*
	Program Name: functions.cpp
	Author: Cesar Camarena
	Date: 11/28/2016
	Purpose: Program 5
*/

#include "prog5.h"

/*
	Function Name: enterCreatures
	Function Purpose: The user is able to enter the file name they wish to load in
					  or manually enter in the information if they have less than
					  100 creatures.
*/
int enterCreatures(Creatures* myCreatures, int creatures)
{
	int choice;
	char fileName[26], danger, again;
	ifstream creaturesFile;
	string numFromFile;
	string tempString;
	
	if (creatures > 99)
	{
		cout << "\nThe zoo is at full capacity!" << endl;
	}
	else
	{
		//Display menu
		cout << "\nWhat do you want to do?" << endl;
		cout << "\t1.  Load my creatures from a file." << endl;
		cout << "\t2.  Enter one creature manually." << endl;
		cout << "\tChoose 1 or 2." << endl;
		cout << "CHOICE:  ";
		cin >> choice;
		
		//Input Validation
		while (choice < 1 || choice > 2)
		{
			cout << "\nEnter a valid answer!" << endl;
			cout << "CHOICE:  ";
			cin >> choice;
		}
		
		if (choice == 1)
		{
			//Loads in the file that the user wishes to load in.
			cout << "What is the name of the file with your list of creatures? ";
			cout << "(ex: filename.txt)" << endl;
			cout << "FILENAME:  ";
			cin.ignore();
			cin.getline(fileName, 50);
			cout << endl << endl;
			
			creaturesFile.open(fileName);
			if (creaturesFile)
			{
				//Reads in the data of the file to the structure array
				getline(creaturesFile, tempString, '#');  //attempt one read
				while(!creaturesFile.eof())
				{
					myCreatures[creatures].name = tempString;
					getline(creaturesFile, myCreatures[creatures].description, '#');
					
					getline(creaturesFile, numFromFile, '#');
					myCreatures[creatures].length = convertToFloat(numFromFile);
					
					getline(creaturesFile, numFromFile, '#'); //read in the creatures age from the file
					myCreatures[creatures].height = convertToFloat(numFromFile);

					// getline(inFile, numberReadFromFile, '#'); //read in the creatures age from the file
					getline(creaturesFile, myCreatures[creatures].origin, '#');

					getline(creaturesFile, numFromFile, '#'); //read in whether the creature is dangerous or not (1 means yes, 0 means no)
					myCreatures[creatures].danger = convertToFloat(numFromFile); //convert the string to a float and then place in structure array

					getline(creaturesFile, numFromFile, '#');
					myCreatures[creatures].costData.hours = convertToFloat(numFromFile);

					getline(creaturesFile, numFromFile, '#');
					myCreatures[creatures].costData.costOfCreature = convertToFloat(numFromFile);

					getline(creaturesFile, numFromFile, '#');
					myCreatures[creatures].costData.costOfFood = convertToFloat(numFromFile);

					getline(creaturesFile, numFromFile, '#');
					myCreatures[creatures].costData.costOfSupplies = convertToFloat(numFromFile);
					
					creatures++;
					
					getline(creaturesFile, tempString, '#'); 
				}
				
				cout << "All creatures from " << fileName << " have been added to the program." << endl;
				creaturesFile.close();
			}
			
			else
			{
				cout << "File could not be opened!" << endl;
			}
		}
		
		//This option is if the user wishes to manually enter in the information
		if (choice == 2)
		{
			do
			{
				//Enter in the name of the creature
				cout << "\nNAME: ";
				cin.ignore();
				getline(cin, myCreatures[creatures].name);
				
				//Enter in the description of the creature
				cout << "\nDESCRIPTION:  ";
				getline(cin, myCreatures[creatures].description);
				
				//Enter in the length of the creature
				cout << "\nAVERAGE LENGTH (in feet):  ";
				cin >> myCreatures[creatures].length;
				
				//Enter in the height of the creature
				cout << "\nAVERAGE HEIGHT (in feet):  ";
				cin >> myCreatures[creatures].height;
				
				//Enter in the location of the creature
				cout << "\nLOCATION:  ";
				cin.ignore();
				getline(cin, myCreatures[creatures].origin);
				
				//Enter whether it is dangerous or not
				cout << "\nIS IT A DANGEROUS CREATURE? (y or n):  ";
				cin >> danger;
				
				if (tolower(danger) == 'y')
					myCreatures[creatures].danger = 1;
				else
					myCreatures[creatures].danger = 0;
				
				//Enter how many hours you spend caring for the creature
				cout << "\nHow many hours do you spend caring for the " << myCreatures[creatures].name << "?" << endl;
				cout << "COST PER HOUR:  ";
				cin >> myCreatures[creatures].costData.hours;
				
				//Enter in the cost per hour for caring for the creature
				cout << "\nWhat is the cost per hour for caring for the " << myCreatures[creatures].name << "?" << endl;
				cout << "COST PER HOUR:  ";
				cin >> myCreatures[creatures].costData.costOfCreature;
				
				//Enter in the cost for the food
				cout << "\nHow much money do you spend on food for the " << myCreatures[creatures].name << "?" << endl;
				cout << "FOOD:  ";
				cin >> myCreatures[creatures].costData.costOfFood;
				
				//Enter in the cost of grooming and medical supplies
				cout << "\nHow much money do you spend on grooming and medical supplies for the " << myCreatures[creature].name << "?" << endl;
				cout << "SUPPLY COST:  ";
				cin >> myCreatures[creatures].costData.costOfSupplies;
				
				creatures++;
				
				//Determines if the user wants to run again
				cout << "\nThe " << myCreatures[creatures].name << " has been added." << endl;
				cout << "Want to add more creatures? (y or n):  ";
				cin >> again;
				
				//Input Validation
				while (again != 'Y' && again != 'y' && again != 'N' && again != 'n')
				{
					cout << "\nEnter a valid answer!" << endl;
					cout << "Want to add more creatures? (y or n):  ";
					cin >> again;
				}
				
			}while (again == 'Y' || again == 'y');
		}
	}
	
	return (creatures);
}

/*
	Function Name: deleteCreature
	Function Purpose: Deletes a creatures from the list
*/
int deleteCreature(Creatures* myCreatures, int creatures)
{
	string name;
	bool ifFound;
	
	//Lists all creatures
	cout << "\nThe following is a list of all the creatures you take care of:" << endl;
	for (int x = 0; x < creatures; x++)
	{
		cout << myCreatures[x].name << endl;
	}
	
	//Selects which creature to remove
	cout << "\n\nWhat creature do you wish to remove?" << endl;
	cout << "CREATURE NAME:  ";
	cin >> name;
	
	ifFound = moveArrayElements(myCreatures, name, creatures);
	
	if (ifFound == true)
	{
		creatures--;
	}
	
	return (creatures);
}

/*
	Function Name: moveArrayElements
	Function Purpose: Moves the creatures elements in the creatures array
*/
bool moveArrayElements(Creatures* myCreatures, string name, int creatures)
{
	bool ifFound;
	
	for (int x = 0; x < creatures; x++)
	{
		if (name == myCreatures[x].name)
		{
			ifFound = true;
			for (int y = x; y < creatures; y++)
			{
				myCreatures[y].name = myCreatures[y + 1].name;
				myCreatures[y].description = myCreatures[y + 1].description;
				myCreatures[y].length = myCreatures[y + 1].length;
				myCreatures[y].height = myCreatures[y + 1].height;
				myCreatures[y].origin = myCreatures[y + 1].origin;
				myCreatures[y].danger = myCreatures[y + 1].danger;
				myCreatures[y].costData.hours = myCreatures[y + 1].costData.hours;
				myCreatures[y].costData.costOfCreature = myCreatures[y + 1].costData.costOfCreature;
				myCreatures[y].costData.costOfFood = myCreatures[y + 1].costData.costOfFood;
				myCreatures[y].costData.costOfSupplies = myCreatures[y + 1].costData.costOfFood;
			}
		}
		else
		{
			ifFound = false;
		}
	}
	
	return (ifFound);
}

/*
	Function Name: printCreatures
	Function Purpose: Prints out the data of all of the creatures whether onto the screen
					  or file
*/
void printCreatures(Creatures* myCreatures, int creatures)
{
	int choice;
	char fileName[26];
	ofstream creaturesFile;
	
	cout << "\nWhat would you like to do?" << endl;
	cout << "\t1. Print Creatures to the Screen." << endl;
	cout << "\t2. Print Creatures to a file." << endl;
	cout << "\tChoose 1 or 2:  ";
	cin >> choice;
	
	while (choice < 1 || choice > 2)
	{
		cout << "\nERROR! Enter a valid answer." << endl;
		cout << "\nWhat would you like to do?" << endl;
		cout << "\t1. Print Creatures to the Screen." << endl;
		cout << "\t2. Print Creatures to a file." << endl;
		cout << "\tChoose 1 or 2." << endl;
		cin >> choice;
	}
	
	if (choice == 1)
	{
		for (int x = 0; x < creatures; x++)
		{
			cout << "---------------------------------------------------------------" << endl;
			cout << "CREATURE " << (x + 1) << ":" << endl;
			cout << "Name:\t\t" << myCreatures[x].name << endl;
			cout << "Description:" << endl;
			cout << myCreatures[x].description << endl;
			cout << "\nLength:" << setw(15) << " " << myCreatures[x].length << " feet" << endl;
			cout << "Height:" << setw(15) << " " << myCreatures[x].height << " feet" << endl;
			cout << "Location:" << setw(13) << " " << myCreatures[x].origin << endl;
			cout << "Dangerous?";
			
			if (myCreatures[x].danger == 1)
				cout << setw(12) << " " << "Yes" << endl;
			if (myCreatures[x].danger == 0)
				cout << setw(12) << " " << "No" << endl;
			
			cout << "Number of Hours to Care for Creature:" << setw(13) << myCreatures[x].costData.hours << " hours" << endl;
			cout << "Cost Per Hour of Taking Care of Creature:" << setw(10) << "$ " << myCreatures[x].costData.costOfCreature << endl;
			cout << "Cost to Feed Creature:" << setw(13) << "$ " << myCreatures[x].costData.costOfFood << endl;
			cout << "Grooming & Supplies Cost:" << setw(10) << "$ " << myCreatures[x].costData.costOfSupplies << endl << endl;
		}
	}
	
	if (choice == 2)
	{
		cout << "\nWhat is the name of the file you wish to print ";
		cout << "the creatures to?" << endl;
		cin.ignore();
		cin.getline(fileName, 50);
		creaturesFile.open(fileName);
		
		for (int x = 0; x < creatures; x++)
		{
			creaturesFile << "---------------------------------------------------------------" << endl;
			creaturesFile << "CREATURE " << (x + 1) << ":" << endl;
			creaturesFile << "Name:\t\t" << myCreatures[x].name << endl;
			creaturesFile << "Description:" << endl;
			creaturesFile << myCreatures[x].description << endl;
			creaturesFile << "\nLength:" << setw(15) << " " << myCreatures[x].length << " feet" << endl;
			creaturesFile << "Height:" << setw(15) << " " << myCreatures[x].height << " feet" << endl;
			creaturesFile << "Location:" << setw(13) << " " << myCreatures[x].origin << endl;
			creaturesFile << "Dangerous?";
			
			if (myCreatures[x].danger == 1)
				creaturesFile << setw(12) << " " << "Yes" << endl;
			if (myCreatures[x].danger == 0)
				creaturesFile << setw(12) << " " << "No" << endl;
			
			creaturesFile << "Number of Hours to Care for Creature:" << setw(13) << myCreatures[x].costData.hours << " hours" << endl;
			creaturesFile << "Cost Per Hour of Taking Care of Creature:" << setw(10) << "$ " << myCreatures[x].costData.costOfCreature << endl;
			creaturesFile << "Cost to Feed Creature:" << setw(13) << "$ " << myCreatures[x].costData.costOfFood << endl;
			creaturesFile << "Grooming & Supplies Cost:" << setw(10) << "$ " << myCreatures[x].costData.costOfSupplies << endl << endl;
		}
		
		cout << "Your creatures have been written to " << fileName << "." << endl;
		
		creaturesFile.close();
	}
}

/*
	Function Name: 
	Function Purpose: 
*/
void printStatistics(Creatures* myCreatures, int creatures)
{
	float cost;
	float total = 0;
	
	cout << "\nCOST OF EACH CREATURE FOR ONE WEEK:" << endl;
	cout << "\nCREATURE" << setw(15) << right << "COST" << endl;
	for (int x = 0; x < creatures; x++)
	{
		cost = (myCreatures[x].costData.hours * myCreatures[x].costData.costOfCreature) + myCreatures[x].costData.costOfFood + myCreatures[x].costData.costOfSupplies;
		total += cost;
		
		cout << setw(20) << left << myCreatures[x].name << setprecision(2) << fixed << right << "$ " << cost << endl;
	}
	
	cout << setw(21) << left << "\nTOTAL COST:" << "$ " << setprecision(2) << fixed << total << endl << endl;
}

/*
	Function Name: saveCreaturesToFile
	Function Purpose: Saves all of the information of the creatures into a file that is
					  formatted to fit all in a single line separated by #
*/
void saveCreaturesToFile(Creatures* myCreatures, int creatures)
{
	char fileName[26];
	ofstream creaturesFile;
	
	cout << "What would you like to name the file as?" << endl;
	cin.getline(fileName, 50);
	
	creaturesFile.open(fileName);
	
	for (int x = 0; x < creatures; x++)
	{
		creaturesFile << myCreatures[x].name << "#";
		creaturesFile << myCreatures[x].description << "#";
		creaturesFile << myCreatures[x].length << "#";
		creaturesFile << myCreatures[x].height << "#";
		creaturesFile << myCreatures[x].origin << "#";
		creaturesFile << myCreatures[x].costData.hours << " hours" << "#";
		creaturesFile << myCreatures[x].costData.costOfCreature << "#";
		creaturesFile << myCreatures[x].costData.costOfFood << "#";
		creaturesFile << myCreatures[x].costData.costOfSupplies << "#";
	}
		
	cout << "Your creatures were successfully saved to the " << fileName << " file." << endl;
	
	creaturesFile.close();
}

/*
	Function Name: convertToFloat
	Function Purpose: Converts the float values from a file to floats.
*/
float convertToFloat(string s)
{
	istringstream i(s);
	float x;
	if (!(i >> x))
		x = 0;
	return x;
}