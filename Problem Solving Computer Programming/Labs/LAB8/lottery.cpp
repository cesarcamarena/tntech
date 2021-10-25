/************************************************************
 *	File Name: lottery.cpp									*
 *	Author: Cesar Camarena 									*
 *	Date: 10/26/16 											*
 *	Purpose: Play the lottery!  							*
 ************************************************************/
 
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Global constants
const int ARRAY_SIZE = 5;
const int MAX_RANGE = 9;

// Function prototypes
void generateNumbers(int [], int);
void getUser(int [], int);
int findMatches(int [], int [], int);
void displayValues(int [], int [], int);

int main()
{
	// Variable Definitions
	int lottery[ARRAY_SIZE];
	int user[ARRAY_SIZE];
	int matched;
	int size = ARRAY_SIZE;

	// Generate the random lottery numbers.
	generateNumbers(lottery, size);
   
	// Get the user's numbers.
	getUser(user, size);
   
	// Get the number of matching numbers.
	matched = findMatches(lottery, user, size);
	
	// Display the lottery and user numbers.
	displayValues(lottery, user, size);
   
	// Display the number of matching numbers.
	cout << "\nYou matched " << matched << " numbers." << endl;
   
	// Determine whether the user won the grand prize.
	if (matched == ARRAY_SIZE)
	{
		cout << "You won the grand prize!";
	}

   return 0;
}

// *******************************************************
// The generateNumbers function generates random numbers *
// and stores them in the lottery array.                 *
// *******************************************************
void generateNumbers(int lottery[], int size)
{
	// Seed the random number generator.
	srand(time(0));

	// Generate the random numbers.
	for (int i = 0; i < size; i++)
	{
		lottery[i] = 0 + rand() % MAX_RANGE;
	}
}

// *******************************************************
// The getUser function gets the user's lottery picks.   *
// *******************************************************
void getUser(int user[], int size)
{
	cout << "\n\nEnter your 5 lottery number picks." << endl;
	
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		cout << "Number " << (i + 1) << ":  ";
		cin >> user[i];
		while (user[i] < 0 || user[i] > 9)
		{
			cout << "Enter a number from 0 to 9:  ";
			cin >> user[i];
		}
	}
}

// *******************************************************
// The findMatches function finds the number of the      *
// user's values that match the lottery numbers. The     *
// number of matches is returned.                        *
// *******************************************************

int findMatches(int lottery[], int user[], int size)
{
	int matched = 0;
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		if (lottery[i] == user[i])
		{
			matched++;
		}
	}
	
	return matched;
}

// *******************************************************
// The displayValues function displays the values in the *
// lottery array and the user array.                     *
// *******************************************************
void displayValues(int lottery[], int user[], int size)
{
	// Display the lottery numbers.
	cout << "\nLottery numbers:" << endl;
	
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		cout << "\t" << lottery[i];
	}
	cout << endl;
	
	// Display the user's numbers.
	cout << "Your numbers:" << endl;
	
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		cout << "\t" << user[i];
	}
	cout << endl;
}