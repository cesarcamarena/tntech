/*
	File Name: lab2.cpp
	Author: Cesar Camarena
	Date: September 1, 2016
	Purpose: 2nd Lab - Calculating circumference and area of the circle.
*/

#include <iostream>
using namespace std;
int main()
{
	//Variable Definitions
	float diameter = 7.5;
		  PI = 3.14159265359;
		  circumference;
		  area;
		  
	//Calculating circumference and area of the circle
	 circumference = PI * diameter;
	 area = PI * (diameter/2) * (diameter/2);
	
	//Prints results to screen
	cout << "The circumference of the circle is " << circumference << ".\n";
	cout << "The area of the circle is " << area << ".\n";
	
	//Calculating circumference and area of the circle
	 circumference = PI * (diameter * 2);
	 area = PI * diameter * diameter;
	
	//Prints results to screen
	cout << "The circumference of the circle is " << circumference << ".\n";
	cout << "The area of the circle is " << area << ".\n";
	return 0;
}