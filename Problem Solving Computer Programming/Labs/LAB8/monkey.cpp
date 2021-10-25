/*
	Title: lab8.cpp
	Author: Cesar Camarena
	Date: 10/26/16
	Purpose:
*/
#include <iostream>
using namespace std;

//Global constants
const int MONKEYS = 3;
const int DAYS = 7;

//Function prototypes
void getFoodEaten(double [][DAYS]);
void displayAverageDaily(double [][DAYS]);
void displayLeastEaten(double [][DAYS]);
void displayMostEaten (double [][DAYS]);

int main()
{
	//Variable Definitions
	double monkeyData[MONKEYS][DAYS];
	
	//Get data of food eaten from user
	getFoodEaten(monkeyData);
	
	//Display the average amount of food eaten daily
	displayAverageDaily(monkeyData);
	
	//Display the least amount of food eaten
	displayLeastEaten(monkeyData);
	
	//Display the most amount of food eaten
	displayMostEaten(monkeyData);
	
	return 0;
}

/*
	The getFoodEaten function obtains the data of the amount of pounds
	eaten by each monkey for each day, and then stores that data into
	the 2D array monkeyData.
*/
void getFoodEaten(double monkeyData[MONKEYS][DAYS])
{
	for (int x = 0; x < MONKEYS; x++)
	{
		for (int y = 0; y < DAYS; y++)
		{
			cout << "Enter the pounds eaten by monkey number " << (x + 1) << " on day ";
			cout << (y + 1) << ": ";
			cin >> monkeyData[x][y];
		}
		cout << endl;
	}
}

/*
	The displayAverageDaily function calculates the average amount of
	food eaten daily and then displays it.
*/
void displayAverageDaily(double monkeyData[MONKEYS][DAYS])
{
	for (int y = 0; y < DAYS; y++)
	{
		float sum = 0;
		float average;
		
		for (int x = 0; x < MONKEYS; x++)
		{
			sum += monkeyData[x][y];
		}
		
		average = sum / MONKEYS;
		
		cout << "The average amount eaten on day " << (y + 1) << " is " << average << " pounds.";
		cout << endl;
	}
}

/*
	The displayLeastEaten function searches in the monkeyData array
	and finds the monkey that ate the least amount in the week, and
	then displays it to the user.
*/
void displayLeastEaten(double monkeyData[MONKEYS][DAYS])
{
	int least = monkeyData[0][0];
	int leastX;
	int leastY;
	
	for (int x = 0; x < MONKEYS; x++)
	{
		for (int y = 0; y < DAYS; y++)
		{
			if (monkeyData[x][y] < least)
			{
				least = monkeyData[x][y];
				leastX = x;
				leastY = y;
			}
		}
	}
	
	cout << "\nMonkey number " << (leastX + 1) << " ate the least amount of food, ";
	cout << least << " pounds, on day " << (leastY + 1) << endl;
}

/*
	The displayMostEatenEaten function searches in the monkeyData array
	and finds the monkey that ate the most amount in the week, and
	then displays it to the user.
*/
void displayMostEaten(double monkeyData[MONKEYS][DAYS])
{
	int most = monkeyData[0][0];
	int mostX;
	int mostY;
	
	for (int x = 0; x < MONKEYS; x++)
	{
		for (int y = 0; y < DAYS; y++)
		{
			if (monkeyData[x][y] > most)
			{
				most = monkeyData[x][y];
				mostX = x;
				mostY = y;
			}
		}
	}
	
	cout << "\nMonkey number " << (mostX + 1) << " ate the most amount of food, ";
	cout << most << " pounds, on day " << (mostY + 1) << endl;
}
