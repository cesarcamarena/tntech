/*
	File Name: lab3b.cpp
	Author: Cesar Camarena
	Date: September 8, 2016
	Purpose: 3rd Lab Part B - Total for apples.
*/

#include <iostream>
using namespace std;

int main()
{
	//Variable definitions.
	float price;
	int   quantity;
	float amount;
	float tax;
	float total;
		  
	//Get the price for one apple.
	cout << "\nWhat is the price of one apple in US dollars?\n$  ";
	cin >> price;
	
	//Get the quantity of apples.
	cout << "\nHow many apples did you buy?\nQUANTITY:  ";
	cin >> quantity;
	
	//Calculating the total and the total with tax.
	amount = price * quantity;
	tax = .0975 * amount;
	total = amount + tax;
	
	//Display the price, quantity, amount, tax amount and total purchase.
	cout << "PRICE PER APPLE:  $" << price << endl;
	cout << "QUANTITY:          " << quantity << " APPLES" << endl;
	cout << "PRICE x QUANTITY: $" << amount << endl;
	cout << "TAX:              $" << tax << endl;
	cout << "TOTAL:            $" << total << endl;
	return 0;
}