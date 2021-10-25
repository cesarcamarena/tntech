/*
	Title: pollution.cpp
	Date: 11/14/2016
	Author: Cesar Camarena
	Purpose: Program 4
*/

#include "pollution.h"

const int SIZE = 3; //number of factories
const float CO_MAX_LIMIT = 35; //35 ppm per hour
const float NO2_MAX_LIMIT = 100; //100 ppb per hour
const float O3_MAX_LIMIT = .070; //.070 ppm per 8 hours

int main()
{
	//variable definitions
	string factoryNames[SIZE];
	float* factoryCOData[SIZE];
	float* factoryNO2Data[SIZE];
	float* factoryO3Data[SIZE];
	int years;
	float limit;
	float largestAmount = 0;
	string largestFactoryName;
	int largestYear = 0;
	
	//User enters factory names
	cout << "\n---------------------------------------------------------------------\n\n\n";
	enterFactoryNames(factoryNames, SIZE);
	
	//User enters how many years of data they have
	cout << "How many years of data do you have?" << endl;
	cin >> years;
	
	//Validates the answer
	while (years < 0)
	{
		cout << "\nPlease enter a valid answer." << endl;
		cout << "How many years of data do you have?" << endl;
		cin >> years;
	}
	cout << endl;
	
	//User enters their data for each year of pollution for each factory
	cout << "Please enter data for each factory." << endl;
	cout << "---------------------------------------------------------------------" << endl;
	for (int x = 0; x < SIZE; x++)
	{
		cout << "\nFACTORY:  " << *(factoryNames + x) << endl << endl;
		
		*(factoryCOData + x) = makeArray(years);
		enterCOData(*(factoryCOData + x), years);
		
		*(factoryNO2Data + x) = makeArray(years);
		enterNO2Data(*(factoryNO2Data + x), years);
		
		*(factoryO3Data + x) = makeArray(years);
		enterO3Data(*(factoryO3Data + x), years);
		cout << "---------------------------------------------------------------------" << endl;
	}
	
	//Displays which factory went above their pollution limit
	cout << "\n\nFACTORIES over the CARBON MONOXIDE pollutant level (35):" << endl;
	printOverLimit(factoryNames, factoryCOData, years, CO_MAX_LIMIT);
	cout << endl;
	
	cout << "FACTORIES over the NITROGEN DIOXIDE pollutant level (100):" << endl;
	printOverLimit(factoryNames, factoryNO2Data, years, NO2_MAX_LIMIT);
	cout << endl;
	
	cout << "FACTORIES over the OZONE pollutant level (0.07):" << endl;
	printOverLimit(factoryNames, factoryO3Data, years, O3_MAX_LIMIT);
	cout << endl;
	
	//Displays which factory produced the most amount of pollution, and which year it was when it was produced
	getLargest(factoryNames, factoryCOData, years, largestFactoryName, largestAmount, largestYear);
	cout << "\n---------------------------------------------------------------------\n\n\n";
	cout << "The " << largestFactoryName << " factory produced the most carbon monoxide" << endl;
	cout << "pollution with " << largestAmount << " parts per million in year " << largestYear << ".";
	cout << endl << endl;
	
	getLargest(factoryNames, factoryNO2Data, years, largestFactoryName, largestAmount, largestYear);
	cout << "The " << largestFactoryName << " factory produced the most nitrogen dioxide pollution" << endl;
	cout << "with " << largestAmount << " parts per million in year " << largestYear << ".";
	cout << endl << endl;
	
	getLargest(factoryNames, factoryO3Data, years, largestFactoryName, largestAmount, largestYear);
	cout << "The " << largestFactoryName << " factory produced the most ozone pollution with " << largestAmount << endl;
	cout << "parts per million in year " << largestYear << ".";
	cout << endl << endl;
	cout << "\n---------------------------------------------------------------------";
	
	return 0;
}