/*
	File Name: lab5.cpp
	Author: Cesar Camarena
	Date: September 22, 2016
	Purpose: Compute a student's bill for this semester at Hogwarts.
*/

#include <iostream>
using namespace std;

int main()
{
	char inOut;  //In-country or out-of-country variable
	char houseShack;  //In house or in the Shrieking Shack variable
	char userInput;
	bool again = true;
	int tuition = 0;  //Tuition cost
	
	//Ghoulish Hogwarts
	while (again)
  {
	cout << "\n      .\'(     .-./(     )\\.-.        .\'(     /`-.      /`-.  .-,.-.,-.   )\\.--.  " << endl;
	cout << "  ,\') \\  )  ,\'     )  ,\' ,-,_)   ,\') \\  )  ,\' _  \\   ,\' _  \\ ) ,, ,. (  (   ._.\' " << endl;
	cout << " (  \'-\' (  (  .-, (  (  .   __  (  /(/ /  (  \'-\' (  (  \'-\' ( \\( |(  )/   `-.`.   " << endl;
	cout << "  ) .-.  )  ) \'._\\ )  ) \'._\\ _)  )    (    )   _  )  ) ,_ .\\'    ) \\     ,_ (  \\  " << endl;
	cout << " (  ,  ) \\ (  ,   (  (  ,   (   (  .\'\\ \\  (  ,\' ) \\ (  \' ) \\    \\ (    (  \'.)  ) " << endl;
	cout << "  )/    )/  )/ ._.\'   )/\'._.\'    )/   )/   )/    )/  )/   )/     )/     \'._,_.\'  " << endl;

	//In-country or Out-of-country input from user
	cout << "\n\nWelcome to Hogwarts School of Witchcraft and Wizardry!" << endl;
	cout << "Please input \'I\' if you are in-country or \'0\' if you are out-of-country" << endl;
	cin >> inOut;
	
	//Validates user input for In or Out-of-country.
	while (inOut != 'I' && inOut != 'i' && inOut != 'O' && inOut != 'o')
	{
		cout << "\nPlease input a valid answer" << endl;
		cout << "\n\'I\' for in-country and \'O\' for out-of-country." << endl;
		cin >> inOut;
	}
	
	//Determines if user is In or Out of Country
	if (inOut == 'I' || inOut == 'i')
		tuition += 3000;
	else if (inOut == 'O' || inOut == 'o')
		tuition += 4500;
	
	//House or Shrieking Shack from user
	cout << "\nPlease input \'Y\' if you will be staying in one of the four houses" << endl;
	cout << "and \'N\' if you will be hiding out in the Shrieking Shack." << endl;
	cin >> houseShack;
	
	//Validates user input for housing.
	while (houseShack != 'Y' && houseShack != 'y' && houseShack != 'N' && houseShack != 'n')
	{
		cout << "\nPlease input a valid answer" << endl;
		cout << "\n\'Y\' for Housing and \'N\' for hiding out in the Srieking Shack." << endl;
		cin >> houseShack;
	}
	
	//Gets input of Housing or Shrieking Shack from user
	if (houseShack == 'Y' || houseShack == 'y')
		if (inOut == 'I' || inOut == 'i')
			tuition += 2500;
		else if (inOut == 'O' || inOut == 'o')
			tuition += 3500;
	
	//Prints tuition cost and asks user if they want to run the program again.
	cout << "\nYour total bill for this semester is $" << tuition << endl;
		tuition = 0;
	cout << "\nWould you like to run the program again? (y/n)" << endl;
	cin >> userInput;
	
	//Validates user input for running the program again.
	while (userInput != 'Y' && userInput != 'y' && userInput != 'N' && userInput != 'n')
	{
		cout << "\nPlease input a valid answer." << endl;
		cout << "\n\'Y\' for running the program again and \'N\' to end the program." << endl;
		cin >> userInput;
	}
	
	//Makes the program keep running or closes it.
	if (userInput == 'Y' || userInput == 'y')
		again = true;
	else if (userInput == 'N' || userInput == 'n')
		again = false;
  }
	
return 0;
}