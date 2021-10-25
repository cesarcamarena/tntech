/*
	Title:  jellybeans.cpp
	Date: 10/26/2016
	Author: Cesar Camarena
	Purpose: jellybean program to practice ch 9
*/

#include "jellybeans.h"

int main()
{
	int flavors, total;
	int* jellybeanarray;
	
	cout << "\n\nHow many flavors of jellybeans do you hae?\n?";
	cin >> flavors;
	
	jellybeanarray = makeArray(flavors);
	cout << endl << endl;
	
	fillArray(jellybeanarray, flavors);
	cout << endl << endl;
	
	printArray(jellybeanarray, flavors);
	cout << endl << endl;
	
	total = totalJellyBeans(jellybeanarray, flavors);
	
	cout << "You ate a total of " << total << " jellybeans!!\n\n";
	
	delete [] jellybeanarray;  //release the dynamically allocated memory
	
	return 0;
}