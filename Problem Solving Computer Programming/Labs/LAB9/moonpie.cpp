/*
	Program Name: moonpie.cpp
	Author: Cesar Camarena
	Date: 11/2/2016
	Purpose: 
*/
#include <iostream>
using namespace std;

//function prototypes
int* makeArray(int);
void enterStolenMoonPies(int*, int);
int totalMoonPies(int*, int);
float averageMoonPies(int, int);
int highestMoonPies(int*, int);
int lowestMoonPies(int*, int);

int main()
{
	int* moonPiesStolen;
	int days;
	int total;
	float average;
	int most;
	int least;
	
	cout << "How many days did Jane steal moon pies?" << endl;
	cin >> days;
	
	//input validation for days
	while (days < 0)
	{
		cout << "Please enter a number greater than 0." << endl;
		cout << "How many days did Jane steal moon pies?" << endl;
		cin >> days;
	}
	
	//creates array of how many pies jane stole
	moonPiesStolen = makeArray(days);
	
	//user enters how many pies jane stole into array per day
	enterStolenMoonPies(moonPiesStolen, days);
	
	//totals the amount of pies jane stole
	total = totalMoonPies(moonPiesStolen, days);
	
	//averages the amount of pies jane stole
	average = averageMoonPies(total, days);
	
	//finds the most amount of pies jane stole at which day
	most = highestMoonPies(moonPiesStolen, days);
	
	//finds the least amount of pies jane stole at which day
	least = lowestMoonPies(moonPiesStolen, days);
	
	//displays all of the information gathered from previous functions
	cout << "--------------------RESULTS--------------------" << endl;
	cout << "TOTAL # MOON PIES STOLEN:  " << total << endl;
	cout << "AVERAGE # MOON PIES STOLEN PER DAY:  " << average << endl;
	cout << "MOST # MOON PIES STOLEN IN ONE DAY:  " << most << endl;
	cout << "LEAST # MOON PIES STOLEN IN ONE DAY:  " << least << endl;
	
	delete [] moonPiesStolen;
	
	return 0;
}

/*
	The makeArray function will create a an integer array with a
	pointer named moonPiesStolen that will point to it and returns
	it to the main function.
*/
int* makeArray(int days)
{
	int* moonPiesStolen;
	
	moonPiesStolen = new int[days];
	
	return moonPiesStolen;
}

/*
	The enterStolenMoonPies allows the user to enter the amount of
	pies stolen from jane for each day.
*/
void enterStolenMoonPies(int* moonPiesStolen, int days)
{
	cout << "Enter the number of moon pies stolen each day." << endl;
	
	for (int x = 0; x < days; x++)
	{
		cout << "DAY " << (x + 1) << ":  ";
		cin >> *(moonPiesStolen + x);
		cout << endl;
		
		//Validates the user's input.
		while (*(moonPiesStolen + x) < 0)
		{
			cout << "Enter a valid answer!" << endl;
			cout << "DAY " << (x + 1) << ":  ";
			cin >> *(moonPiesStolen + x);
		}
	}
}

/*
	The totalMoonPies function will total the amount of pies stolen
	and returns it to the main function.
*/
int totalMoonPies(int* moonPiesStolen, int days)
{
	int total = 0;
	
	for (int x = 0; x < days; x++)
	{
		total += *(moonPiesStolen + x);
	}
	
	return total;
}

/*
	The averageMoonPies function averages the amount of pies stolen
	per day and returns that value to the main function.
*/
float averageMoonPies(int total, int days)
{
	float average;
	
	average = static_cast<float>(total) / static_cast<float>(days);
	
	return average;
}

/*
	The highestMoonPies function searches the highest amount of
	pies stolen at whichever day and returns it to the main function.
*/
int highestMoonPies(int* moonPiesStolen, int days)
{
	int most = *moonPiesStolen;
	
	for (int x = 0; x < days; x++)
	{
		if (most < *(moonPiesStolen + x))
		{
			most =  *(moonPiesStolen + x);
		}
	}
	
	return most;
}

/*
	The lowestMoonPies function searches the lowest amount of
	pies stolen at whichever day and returns it to the main function.
*/
int lowestMoonPies(int* moonPiesStolen, int days)
{
	int least = *moonPiesStolen;
	
	for (int x = 0; x < days; x++)
	{
		if (least > *(moonPiesStolen + x))
		{
			least = *(moonPiesStolen + x);
		}
	}
	
	return least;
}