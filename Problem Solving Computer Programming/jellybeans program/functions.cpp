/*
	Title:  functions.cpp
	Date: 10/26/2016
	Author:  Cesar Camarena
	Purpose: jellybean program to practice ch 9
*/

#include "jellybeans.h"

int* makeArray(int f)
{
	int* arr;
	arr = new int[f];  //dynamically allocate array of f elements
	
	return arr;
}

void fillArray(int* arr, int f)
{
	for (int x = 0; x < f; x++)
	{
		cout << "How many of flavor " << (x + 1) << " did you eat?";
		cin >> *(arr + x);
	}
}

voidprintArray(int* arr, int f)
{
	for(int x = 0; x < f; x++)
	{
		cout << "FLAVOR " << (x + 1) << ":  " << *(arr + x) << endl;
	}
}

int toalJellyBeans(int* arr, int f)
{
	int total = 0;
	
	for(int x = 0; x < f; x++)
	{
		total += *(arr + x);
	}
	
	return total;
}