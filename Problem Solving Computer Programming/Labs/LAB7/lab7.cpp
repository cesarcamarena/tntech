/*
	Title: lab7.cpp
	Author: Cesar Camarena
	Date: 10/12/16
	Purpose: For Alf to eat cats or pizzas while keeping a running total for both.
*/
#include <iostream>
using namespace std;

int eatCats(int);
void eatPizza(int&);
void drawAlf();

int main()
{
	int choice;
	int cats = 0;
	int pizza = 0;
	
	do
	{
		cout << "\n\n----------  ALF likes to eat cats & pizza!  ----------" << endl;
		cout << "\nWhat would ALF like to do right now?" << endl;
		cout << "1. Eat cats." << endl;
		cout << "2. Eat pizza." << endl;
		cout << "3. Print out his name." << endl;
		cout << "4. Nap." << endl;
		cout << "5. End the program." << endl;
		cout << "CHOOSE 1-5:  ";
		cin >> choice;
		
		while(choice < 1 || choice > 5)
		{
			cout << "Invalid choice. Please select 1-5" << endl;
			cin >> choice;
		}
		
		switch(choice)
		{
			case 1: cats = eatCats(cats);
					break;
					
			case 2: eatPizza(pizza);
					break;
					
			case 3: drawAlf();
					break;
					
			case 4: cout << "\n\nTaking a nap....press enter when you wake up.\n\n\n";
					cin.ignore();
					cin.get();
					break;
					
		}
	}while(choice < 5);
	
	cout << "\nAlf ate " << cats << " cats and " << pizza << " pizzas." << endl;
	
	return 0;
}

/*
	Function Name:  eatCats
	Function Purpose:  To eat a cat or go to the main menu while keeping a
					   running total of how many cats were eaten.
*/
int eatCats(int cats)
{
	int choice;
	
	do
	{
		cout << "\nWould you like to (1) Eat a cat or (2) Go back to the main menu?" << endl;
		cout << "CHOOSE 1-2: ";
		cin >> choice;
		
		while(choice < 1 || choice > 2)
		{
			cout << "Invalid choice. Please select 1-2" << endl;
			cin >> choice;
		}
		
		if (choice == 1)
		{
			cats++;
			cout << "--------  YUM!!  --------\n\n\n" << endl;
		}
	}while(choice < 2);
	
	return (cats);
}

/*
	Function Name:  eatPizza
	Function Purpose: To eat a pizza or go back to the main menu while keeping a
					  running total of how many pizzas were eaten using a
					  reference variable.
*/
void eatPizza(int &pizza)
{
	int choice;
	
	do
	{
		cout << "\nWould you like to (1) Eat a pizza or (2) Go back to the main menu?" << endl;
		cout << "CHOOSE 1-2: ";
		cin >> choice;
		
		while(choice < 1 || choice > 2)
		{
			cout << "Invalid choice. Please select 1-2" << endl;
			cin >> choice;
		}
		
		if (choice == 1)
		{
			pizza++;
			cout << "--------  YUM!!  --------\n\n\n" << endl;
		}
	}while(choice < 2);
}

/*
	Function Name:  drawAlf
	Function Purpose: To draw the word ALF in ASCII art
*/
void drawAlf()
{
	cout << "\n ________  ___       ________ " << endl;
	cout << "|\\   __  \\|\\  \\     |\\  _____\\" << endl;
	cout << "\\ \\  \\|\\  \\ \\  \\    \\ \\  \\__/ " << endl;
	cout << " \\ \\   __  \\ \\  \\    \\ \\   __\\" << endl;
	cout << "  \\ \\  \\ \\  \\ \\  \\____\\ \\  \\_|" << endl;
	cout << "   \\ \\__\\ \\__\\ \\_______\\ \\__\\ " << endl;
	cout << "    \\|__|\\|__|\\|_______|\\|__| " << endl;
}