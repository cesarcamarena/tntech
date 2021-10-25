/*
	Title: program2.cpp
	Author: Cesar Camarena
	Date: 10/7/16
	Purpose: Cooking Conversion Program
*/
#include <iostream>
#include <iomanip>
using namespace std;

int convertTemps(int);
void viewSolidMeasurements();
void convertLiquids(int&);

int main()
{
	//Variable definitions
	int choice;
	int conversions = 0;
	
	do
	{
		cout << "\n\n--MAIN MENU--" << endl;
		cout << "\nWhat would you like to look at?" << endl;
		cout << "1. Oven Temperatures & Conversions" << endl;
		cout << "2. View Solids Measurements" << endl;
		cout << "3. Liquids Measurements & Conversions" << endl;
		cout << "4. End the Program" << endl;
		cout << "CHOOSE 1-4:  ";
		cin >> choice;  //Getting input from user
		
		//Validates user's choice
		while (choice < 1 || choice > 4)
		{
			cout << "\nInvalid choice. Please select 1-4" << endl;
			cin >> choice;
		}
		
		//Input from user chooses which function they choose to use
		switch(choice)
		{
			case 1: conversions = convertTemps(conversions);
					break;
					
			case 2: viewSolidMeasurements();
					break;
					
			case 3: convertLiquids(conversions);
					break;
					
		}
	} while (choice < 4);
	
	//Displays how many conversions the user made during the program
	cout << "\n\nThank you for using the measurement program." << endl;
	cout << "Hopefully you can cook something really special for me" << endl;
	cout << "because you made " << conversions << " conversions!" << endl;
	
	return 0;
}

/*
	Function Name: convertTemps
	Function Purpose: Converts temperature to either celsius or fahrenheit, and
					  keeps a running total of how many conversions the user
					  makes.
*/
int convertTemps(int conversions)
{
	//Variable definitions
	int choice;
	float temperature;
	float convertedTemp;
	
	do
	{
		cout << "\n\n--OVEN TEMPERATURES--" << endl;
		cout << "\nWater boils at 100 degrees Celsius and 212 degrees Fahrenheit." << endl;
		cout << "Water freezes at 0 degrees Celsius and 32 degrees Fahrenheit." << endl;
		
		cout << "\nWhat do you want to do?" << endl;
		cout << "1. Convert a temperature from Celsius to Fahrenheit." << endl;
		cout << "2. Convert a temperature from Fahrenheit to Celsius." << endl;
		cout << "3. Go back to MAIN MENU." << endl;
		cout << "CHOOSE 1-3: ";
		cin >> choice; //Getting input from user
		
		//Validates user's choice
		while(choice < 1 || choice > 3)
		{
			cout << "\nInvalid choice. Please select 1-3" << endl;
			cin >> choice;
		}
		
		//Input from user chooses how the program will convert their temperature
		switch(choice)
		{
			case 1: cout << "What is the temperature in Celsius?" << endl;
					cin >> temperature;
					
					//Converts celsius to fahrenheit
					convertedTemp = temperature * 1.8 + 32;
					conversions++;
					
					//Prints result
					cout << "\nRESULT:  " << setprecision(2) << fixed << temperature << " degrees Celsius is " << setprecision(2) << fixed << convertedTemp << " degrees Fahrenheit." << endl;
					break;
					
			case 2: cout << "What is the temperature in Fahrenheit?" << endl;
					cin >> temperature;
					
					//Converts fahrenheit to celsius
					convertedTemp = (temperature - 32) * 5/9;
					conversions++;
					
					//Prints result
					cout << "\nRESULT:  " << setprecision(2) << fixed << temperature << " degrees Fahrenheit is " << setprecision(2) << fixed << convertedTemp << " degrees Celsius." << endl;
					break;
					
		}
		
	}while (choice < 3);
	
	return (conversions);
}

/*
	Function Name: viewSolidMeasurements
	Function Purpose: Displays solid measurements for butter and dry goods.
*/
void viewSolidMeasurements()
{
	//Variable definitions
	int choice;
	
	do
	{
		cout << "\n\n--SOLIDS MEASUREMENTS--" << endl;
		cout << "\nWhat do you want to do?" << endl;
		cout << "1. View a chart for butter." << endl;
		cout << "2. View a chart for Dry Goods such as flower & sugar." << endl;
		cout << "3. Go back to MAIN MENU." << endl;
		cout << "CHOOSE 1-3:  ";
		cin >> choice;  //Getting input from user
		
		//Validates user's choice
		while (choice < 1 || choice > 3)
		{
			cout << "\nInvalid choice. Please select 1-3" << endl;
			cin >> choice;
		}
		
		//Input from user chooses what measurement they would like to view
		switch(choice)
		{
			case 1: cout << setw(40) << "BUTTER" << endl;
					cout << setw(30) << "CUPS" << setw(20) << "GRAMS" << endl;
					cout << setw(30) << "1/4 cup of Butter" << setw(20) << "57 grams" << endl;
					cout << setw(30) << "1/3 cup of Butter" << setw(20) << "76 grams" << endl;
					cout << setw(30) << "1/2 cup of Butter" << setw(20) << "113 grams" << endl;
					cout << setw(30) << "1 cup of Butter" << setw(20) << "227 grams" << endl;
					
					break;
					
			case 2: cout << setw(48) << "DRY GOODS (FLOUR & SUGAR)" << endl;
					cout << setw(20) << "1/8 cup" << setw(20) << "16 grams" << setw(20) << ".563 ounces" << endl;
					cout << setw(20) << "1/4 cup" << setw(20) << "32 grams" << setw(20) << "1.13 ounces" << endl;
					cout << setw(20) << "1/3 cup" << setw(20) << "43 grams" << setw(20) << "1.5 ounces" << endl;
					cout << setw(20) << "1/2 cup" << setw(20) << "64 grams" << setw(20) << "1.5 ounces" << endl;
					cout << setw(20) << "2/3 cup" << setw(20) << "85 grams" << setw(20) << "2.25 ounces" << endl;
					cout << setw(20) << "3/4 cup" << setw(20) << "96 grams" << setw(20) << "3 ounces" << endl;
					cout << setw(20) << "1 cup" << setw(20) << "128 grams" << setw(20) << "4.5 ounces" << endl;
					
					break;
					
		}
		
	}while (choice < 3);
}

/*
	Function Name: convertLiquids
	Function Purpose: Converts liquid measurements to whatever measurement
					  the user would like to convert to, and keeps a running
					  total of the amount of conversions the user makes.
*/
void convertLiquids(int &conversions)
{
	//Variable definitions
	int choice;
	float gallons;
	float quarts;
	float pints;
	float cups;
	
	do
	{
		cout << "\n\n--LIQUIDS MEASUREMENTS--" << endl;
		cout << "\nWhat measurement do you know?" << endl;
		cout << "1. I know how many gallons I have." << endl;
		cout << "2. I know how many quarts I have." << endl;
		cout << "3. I know how many pints I have." << endl;
		cout << "4. I know how many cups I have." << endl;
		cout << "5. Go back to MAIN MENU." << endl;
		cout << "CHOOSE 1-5:  ";
		cin >> choice;  //Getting input from user
		
		//Validates user's choice
		while(choice < 1 || choice > 5)
		{
			cout << "Invalid choice. Please select 1-5" << endl;
			cin >> choice;
		}
		
		//Input from user chooses what liquid measure they would like to convert
		switch(choice)
		{
			case 1: cout << "How many gallons do you have?" << endl;
					cin >> gallons;
					
					//Converts gallons to quarts, pints, and cups
					quarts = gallons * 4;
					pints =  gallons * 8;
					cups = gallons * 16;
					conversions++;
					
					//Prints result
					cout << "\nRESULT:  " << gallons << " gallons is " << quarts << " quarts, " << pints << " pints, or " << cups << " cups." << endl;
					break;
					
			case 2: cout << "How many quarts do you have?" << endl;
					cin >> quarts;
					
					//Converts quarts to gallons, pints, and cups
					gallons =  quarts / 4;
					pints =  quarts * 2;
					cups = quarts * 4;
					conversions++;
					
					//Prints result
					cout << "\nRESULT:  " << quarts << " quarts is " << gallons << " gallons, " << pints << " pints, or " << cups << " cups." << endl;
					break;
					
			case 3: cout << "How many pints do you have?" << endl;
					cin >> pints;
					
					//Converts pints to gallons, quarts, and cups
					gallons = pints / 8;
					quarts = pints / 2;
					cups = pints * 2;
					conversions++;
					
					//Prints result
					cout << "\nRESULT:  " << pints << " pints is " << gallons << " gallons, " << quarts << " quarts, or " << cups << " cups." << endl;
					break;
					
			case 4: cout << "How many cups do you have?" << endl;
					cin >> cups;
					
					//Converts cups to gallons, quarts, and pints
					gallons =  cups / 16;
					quarts = cups / 4;
					pints = cups / 2;
					conversions++;
					
					//Prints result
					cout << "\nRESULT:  " << cups << " cups is " << gallons << " gallons, " << quarts << " quarts, & " << pints << " pints." << endl;
					break;
					
		}
	}while(choice < 5);
}