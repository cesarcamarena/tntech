/*
	File Name: lab3a.cpp
	Author: Cesar Camarena
	Date: September 8, 2016
	Purpose: 3rd Lab Part A - Number of slices per pizza.
*/

#include <iostream>
using namespace std;

int main()
{
	//Variable Definitions
	float PI = 3.14159265359;
	float diameter;
	float area;
	int	  slices;
		
	//Get the value for diameter.
	cout << "\nWhat is the diameter of the pizza in inches?\n";
	cin >> diameter;
	
	//Calculating the number of slices for pizza.
	area = PI * (diameter/2) * (diameter/2);
	slices = area/14.125;
	
	cout << "\nYou should cut the pizza in " << slices << " slices.\n";
	return 0;
}