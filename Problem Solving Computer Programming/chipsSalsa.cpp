#include <iostream>
using namespace std;

//function prototypes
void enterNumJars(string[], int[], int);

int main()
{
	const int SIZE = 5;
	int total = 0; //accumulator
	string salsaNames[SIZE] = {"mild", "medium", "sweet", "hot", "zesty"};
	int jarsSold[SIZE];
	int highestSold, lowestSold;
	string highestName, lowestName;
	
	enterNumJars(salsaNames, jarsSold, SIZE);
	
	//print sales for each salsa type
	for(int x = 0; x < SIZE; x++)
	{
		cout << "\nNumber of jars for the " << salsaNames[x] << " salsa: " << jarsSold[x];
	}
	//find the total
	for(int x = 0; x < SIZE; x++)
	{
		total += jarsSold[x];
	}
	cout << "\n\nTOTAL JARS SOLD:  " << total;
	
	//find highest
	highestSold = jarsSold[0];
	highestName = salsaNames[0];
	for(int x = 1; x < SIZE; x++)
	{
		if(jarsSold[x] > highestSold)
		{
			highestSold = jarsSold[x];
			highestName = salsaNames[x];
		}
	}
	cout << "\n\nHIGHEST SELLING SALSA:  " << highestName << " salsa at " << highestSold << " jars.";
	
	//find lowest
	lowestSold = jarsSold[0];
	lowestName = salsaNames[0];
	for(int x = 1; x < SIZE; x++)
	{
		if(jarsSold[x] < lowestSold)
		{
			lowestSold = jarsSold[x];
			lowestName = salsaNames[x];
		}
	}
	cout << "\n\nLOWEST SELLING SALSA:  " << lowestName << " salsa at " << lowestSold << " jars.";
	
	cout << endl << endl;
	
	return 0;
}
void enterNumJars(string name[], int sold[], int size)
{
	cout << endl << endl;
	for(int x = 0; x < size; x++)
	{
		cout << "Enter the number of jars sold for the " << name[x] << " salsa: ";
		cin >> sold[x];
		while(sold[x] < 0)
		{
			cout << "You entered a negative number. Enter a positive number: ";
			cin >> sold[x];
		}
	}
	
}