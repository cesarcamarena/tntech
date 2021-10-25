/*
	File Name: lab4.cpp
	Author: Cesar Camarena
	Date: September 12, 2016
	Purpose: Totaling the price of discounted tees.
*/

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	int quantity;
	int PRICE = 12;
	float total;
	float discount;
	string name;
	
	cout << "\n\nWelcome to 80sTees.com!!\n\n";
	cout << "All shirts are $12.\n";
	cout << "We offer quantity discounts as follows:\n\n";
	cout << "\t" << setw(21) << left << "Number of Shirts" << setw(8) << left << "Discount\n";
	cout << "\t" << setw(21) << left << "5-10" << setw(8) << left << "10%\n";
	cout << "\t" << setw(21) << left << "11-20" << setw(8) << left << "15%\n";
	cout << "\t" << setw(21) << left << "21-30" << setw(8) << left << "20%\n";
	cout << "\t" << setw(21) << left << "31 or more" << setw(8) << left << "25%\n";
	
	cout << "\nWhat is your full name (first & last)?\nNAME: ";
	getline(cin, name);
	cout << name << ", how many shirts would you like?\nNUMBER OF SHIRTS: ";
	cin >> quantity;
	
	if (quantity > 0)
	{
		if (quantity >= 5 && quantity <= 10)
			discount = PRICE * .9;
		else if (quantity >= 11 && quantity <= 20)
			discount = PRICE * .85;
		else if (quantity >= 21 && quantity <= 30)
			discount = PRICE * .8;
		else if (quantity >= 31)
			discount = PRICE * .75;
		
		total = quantity * discount;
		
		cout << "\n\n----------------------------------------\n";
		cout << "BILL FOR:  " << name << endl;
		cout << "DISCOUNTED COST:  $" << setprecision(2) << fixed << discount << " (per shirt)\n";
		cout << "TOTAL COST:  $" << setprecision(2) << fixed << total << endl;
	}
	else
		cout << "Invalid input:  Please enter a non-negative integer\n";
	return 0;
}