/*
	File Name: lab6.cpp
	Author: Cesar Camarena
	Date: September 29, 2016
	Purpose:
*/

#include <iostream>
using namespace std;

//Function Prototypes
void GoblinSickDays();
int DisplayCoolMessage(int);

int main()
{
	int choice;              //To hold a menu choice
	int timesOfMessage = 0;  //To hold the amount of times the user sees the cool message.
	
	do
	{
		//Display the Menu Choice.
		cout << "\nWELCOME TO GRINGOTT\'s BANK!" << endl;
		cout << "Please choose one of the folling option:" << endl;
		cout << "     1 - Enter Goblin Sick Days" << endl;
		cout << "     2 - Display Something Cool" << endl;
		cout << "     3 - End the Program" << endl;
		cout << "\nCHOICE: ";
		cin >> choice;
		
		//Validate the user's choice for the menu.
		while (choice < 1 || choice > 3)
		{
			cout << "Please enter a valid menu choice: ";
			cin >> choice;
		}
		
		//Displays Goblin Sick Days or the cool message
		switch (choice)
		{
			case 1: GoblinSickDays();
					break;
			case 2: timesOfMessage = DisplayCoolMessage(timesOfMessage);
					break;
		}
	} while (choice < 3);
	
	cout << "\n\nYou chose to display the cool message " << timesOfMessage << " times." << endl;
	cout << "\nBye!\n\n";
	
	return 0;
}

//Definition of GoblinSickDays function. Displays the amount of sick days for each
//Goblin teller during each of the last three years.
void GoblinSickDays()
{
	int x,
	    goblinTellers,
	    y,
	    sickDays,
		totalSickDays = 0;
	
	cout << "\nHow many Goblin tellers worked at Gringotts during each "
		 << "of the last three years?" << endl;
	cin >> goblinTellers;
	
	for (x = 1; x <= goblinTellers; x++)
	{
		for (y = 1; y <= 3; y++)
		{
			cout << "How many sick days was Goblin " << x << " out for, during year " << y << "?" << endl;
			cin >> sickDays;
			totalSickDays += sickDays;
			
		}
	}
	cout << "The " << goblinTellers << " were out sick for a total of " << totalSickDays << " days "
	     << "during the last 3 years" << endl;
	
}

//Definition of DisplayCoolMessage function which will keep a running total of how many times
//the user saw the cool message and displays it when they choose the exit the program.
int DisplayCoolMessage(int timesOfMessage)
{
	cout << "\n\n  /$$$$$$            /$$                                 /$$     /$$             " << endl;
	cout << " /$$__  $$          |__/                                | $$    | $$             " << endl;
	cout << "| $$  \\__/  /$$$$$$  /$$ /$$$$$$$   /$$$$$$   /$$$$$$  /$$$$$$ /$$$$$$   /$$$$$$$" << endl;
	cout << "| $$ /$$$$ /$$__  $$| $$| $$__  $$ /$$__  $$ /$$__  $$|_  $$_/|_  $$_/  /$$_____/" << endl;
	cout << "| $$|_  $$| $$  \\__/| $$| $$  \\ $$| $$  \\ $$| $$  \\ $$  | $$    | $$   |  $$$$$$ " << endl;
	cout << "| $$  \\ $$| $$      | $$| $$  | $$| $$  | $$| $$  | $$  | $$ /$$| $$ /$$\\____  $$" << endl;
	cout << "|  $$$$$$/| $$      | $$| $$  | $$|  $$$$$$$|  $$$$$$/  |  $$$$/|  $$$$//$$$$$$$/" << endl;
	cout << " \\______/ |__/      |__/|__/  |__/ \\____  $$ \\______/    \\___/   \\___/ |_______/ " << endl;
	cout << "                                   /$$  \\ $$                                     " << endl;
	cout << "                                  |  $$$$$$/                                     " << endl;
	cout << "                                   \\______/                                      \n\n";
	
	timesOfMessage++;
	
	return (timesOfMessage);
}