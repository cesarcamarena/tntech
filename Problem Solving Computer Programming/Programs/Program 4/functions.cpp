/*
	Title: functions.cpp
	Date: 11/14/2016
	Author: Cesar Camarena
	Purpose: Program 4 functions
*/

#include "pollution.h"

/*
	Function Name: enterFactoryNames
	Function Purpose: To enter the names of factories
*/
void enterFactoryNames(string factoryNames[], int SIZE)
{
	for (int x = 0; x < SIZE; x++)
	{
		cout << "Name of FACTORY " << (x + 1) << ":  ";
		getline(cin, *(factoryNames + x));
		cout << endl;
	}
}

/*
	Function Name: makeArray
	Function Purpose: To create arrays for each factory by its amount of years of data
*/
float* makeArray(int years)
{
	float* factoryData;
	
	factoryData = new float[years];
	
	return factoryData;
}

/*
	Function Name: enterCOData
	Function Purpose: To enter the data for CO for each factory
*/
void enterCOData(float* factoryData, int years)
{
	cout << "Carbon Monoxide (CO) average level per hour (in parts per million)" << endl;
	
	for (int x = 0; x < years; x++)
	{
		cout << "\tYEAR " << (x + 1) << ":  ";
		cin >> *(factoryData + x);
	}
	cout << endl;
}

/*
	Function Name: enterNO2Data
	Function Purpose: To enter the data for NO2 for each factory
*/
void enterNO2Data(float* factoryData, int years)
{
	cout << "Nitrogen Dioxide (NO2) average level per hour (in parts per billion)" << endl;
	
	for (int x = 0; x < years; x++)
	{
		cout << "\tYEAR " << (x + 1) << ":  ";
		cin >> *(factoryData + x);
	}
	cout << endl;
}

/*
	Function Name: enterO3Data
	Function Purpose: To enter the data for O3 for each factory
*/
void enterO3Data(float* factoryData, int years)
{
	cout << "Ozone (O3) average level per 8 hours (in parts per million)" << endl;
	
	for (int x = 0; x < years; x++)
	{
		cout << "\tYEAR " << (x + 1) << ":  ";
		cin >> *(factoryData + x);
	}
	cout << endl;
}

/*
	Function Name: printOverLimit
	Function Purpose: To display which factories went over their pollution limit
*/
void printOverLimit(string factoryNames[], float** factoryData, int years, float limit)
{
	bool overLimit;
	bool allFalse = true;
	 
	for (int x = 0; x < 3; x++)
	{
		overLimit = false;
		
		for (int y = 0; y < years; y++)
		{
			if(*(*(factoryData + x) + y) > limit)
			{
				overLimit = true;
				allFalse = false;
			}
		}
		if (overLimit == true)
		{
			cout << *(factoryNames + x) << endl;
		}
	}
	
	
	if (allFalse == true)
	{
		cout << "Yay! There are no factories over the limit!!" << endl;
	}
}

/*
	Function Name: getLargest
	Function Purpose: To obtain which factory produced the largest amount of pollution
*/
void getLargest(string factoryNames[], float** factoryData, int years, string& largestFactoryName, float& largestAmount, int& largestYear)
{
	largestFactoryName = *(factoryNames + 0);
	largestAmount = *(*(factoryData + 0) + 0);
	largestYear = 0;
	
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < years; y++)
		{
			if (*(*(factoryData + x) + y) > largestAmount)
			{
				largestFactoryName = *(factoryNames + x);
				largestYear = y + 1;
				largestAmount = *(*(factoryData + x) + y);
			}
		}
	}
}