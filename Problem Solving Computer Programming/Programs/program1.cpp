/*
	File Name: program1.cpp
	Author: Cesar Camarena
	Date: September 19, 2016
	Purpose: First programming assignment in C++ to demonstrate proper code formatting
			 proper variable definitions, data types, input & ouput, relational
			 expressions, strings, and random number generation.
*/

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int main()
{
	//Variable Definitions
	int risk = 0;
	int age;
	int randomNum;
	int riskTotal;
	string name;
	char answer;
	
	//Introduction information.
	cout << "\n--------------------------- MOSQUITOES ---------------------------" << endl;
	cout << "Female mosquitoes need human blood to develop fertile eggs and " << endl;
	cout << "not just anyone's blood will do. The quiz below will determine if " << endl;
	cout << "you are an attractive meal for mosquitoes." << endl;
	cout << "Mosquitoes select their victims by evaluating scent, exhaled carbon" << endl;
	cout << "dioxide, movement and the chemcials in a person's sweat.\n\n\n";
	
	//Asks the user what is their name.
	cout << "What is your name?" << endl;
	cout << "NAME:  ";
	getline(cin, name);
	
	
	//Calculates the risk whether the user lives in one of the worst mosquito cities.
	cout << "\n-------------------------- LOCATION -----------------------------" << endl;
	cout << "Do you live in one of the 20 worst mosquito cities in the US?" << endl;
	cout << "(http://www.orkin.com/press-room/20-worst-mosquito-cities-in-us/)" << endl;
	cout << "ENTER y or n:  ";
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
		risk += 5;
	else if (answer != 'n' && answer!= 'N')
		cout << "Invalid input." << endl;
	
	//Calculates the risk whether the user smells nice.
	cout << "\n------------------------- SCENT ---------------------------------" << endl;
	cout << "Do you wear perfume/cologne or naturally smell like flowers?" << endl;
	cout << "ENTER y or n:  ";
	cin.ignore(10, '\n');
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
		risk += 5;
	else if (answer != 'n' && answer != 'N')
		cout << "Invalid input." << endl;
	
	//Calculates the risk if the user emits large amounts of CO2.
	cout << "\n----------------------- CARBON DIOXIDE -------------------------------" << endl;
	cout << "Do you emit a large quantity of carbon dioxide when you exhale?" << endl;
	cout << "ENTER y or n:  ";
	cin.ignore(10, '\n');
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
		risk += 5;
	else if (answer != 'n' && answer != 'N')
		cout << "Invalid input." << endl;
	
	//Calculates the risk if the user sweats.
	cout << "\n------------------------- SWEAT ---------------------------------" << endl;
	cout << "Do you sweat or move more than most people?" << endl;
	cout << "ENTER y or n:  ";
	cin.ignore(10, '\n');
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
		risk += 5;
	else if (answer != 'n' && answer != 'N')
		cout << "Invalid input." << endl;
	
	//Calculates the risk from the user's age.
	cout << "\n-------------------------  AGE  ---------------------------------" << endl;
	cout << "What is your age?" << endl;
	cout << "AGE:  ";
	cin.ignore(10, '\n');
	cin >> age;
	if (age >= 0)
	{
		if (age >= 0 && age <= 6)
			risk += 25;
		else if (age > 6 && age <= 12)
			risk += 20;
		else if (age > 12 && age <= 19)
			risk += risk + 15;
		else if (age > 19)
			risk += 5;
	}
	else
		cout << "Invalid input." << endl;
	
	//Calculates the risk if the user has high cholesterol.
	cout << "\n----------------------- CHOLESTEROL ------------------------------" << endl;
	cout << "Do you have a high concentration of cholesterol on your skin surface?" << endl;
	cout << "http://www.nhlbi.nih.gov/health/health-topics/topics/hbc" << endl;
	cout << "ENTER y or n:  ";
	cin.ignore(10, '\n');
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
		risk += 5;
	else if (answer != 'n' && answer != 'N')
		cout << "Invalid input." << endl;
	
	//Generates a Random Number representing the "lucky number".
	srand(time(NULL));
	randomNum = rand() % 50 + 1;
	riskTotal = risk + randomNum;
	
	//Prints out the results of the user.
	cout << "\n------------------------ RESULTS -------------------------------" << endl;
	cout << "Your lucky (or unlucky) number is " << randomNum << endl;
	cout << "\nMosquitoes can act as reservoirs of diseases such as West Nile virus," << endl;
	cout << "malaria, yellow fever and dengue fever." << endl;
	cout << "\n" << name << ", you are " << riskTotal << "% likely to contract one ";
	cout << "of these diseases." << endl;
	
	//THE END.
	cout << "\n-------------------------- THE END ------------------------------\n\n";
	
	return 0;
}