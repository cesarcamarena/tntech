/*
	Title:  halloweenStore.cpp
	Author:  April Crockett
	Date:  10/3/2016
	Purpose:  chapter 6 practice, menu based programs
*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <ctime>

using namespace std;

//global constants
const float TAX = .0975;

//function prototypes
int getMenuChoice();
void enterSales();
void totalSales();

int main()
{
	//variable definitions
	int choice;
	char deleteResponse;
	
	do
	{
		//get the user's menu choice
		choice = getMenuChoice();
		switch(choice)
		{
			case 1:	enterSales();
					break;
					
			case 2: totalSales();
					break;
					
			case 3: //because this code is pretty short, I decided not to put it in a seperate function
					cout << "You wish to delete the sales.txt file? (y or n):  ";
					cin >> deleteResponse;
					if (deleteResponse == 'y')
					{	
						if(remove("sales.txt") != 0)
							cout << "Error deleting file!\n\n";
						else
							cout << "File deleted.\n\n";
					}
					else
						cout << "You chose not to delete the file.\n\n";
					break;
			
			case 4:	cout << "\nThank you and Have a Spooky Day!\n\n";
		}
	}while(choice != 4);
	
	return 0;
}

/*
	Function:  getMenuChoice
	Purpose:  To display the menu, read in user's choice, and
			  then validate the users choice, and return back
			  to main.
*/
int getMenuChoice()
{
	int choice;
	cout << "\n\n-----------------------------------------------------\n";
	cout << "Halloween House Management Program\n\n";
	cout << "Please select from the following menu items: \n";
	cout << "1.  Enter sales.\n";
	cout << "2.  Tally Sales for the Day.\n";
	cout << "3.  Delete Sales for the Day.\n";
	cout << "4.  End Program.\n";
	cin >> choice;
	
	while(choice < 1 || choice > 4)
	{
		cout << "Invalid choice.  Please select 1-4.\n";
		cin >> choice;
	}
	
	return choice;
}

/*
	Function: enterSales
	Purpose:  User will enter sales for the day and the program will
			  write the sales to sales.txt output file.
*/
void enterSales()
{
	int choice, quantity;
	char runAgain;
	float price, total;
	ofstream outFile;
	
	//open the output file
	outFile.open("sales.txt");
	
	do
	{
		cout << "\nYou chose to enter sales.";
		//display menu
		cout << "\n\nChoose the department from the following menu:\n";
		cout << "1.  Candy\n";
		cout << "2.  Costumes\n";
		cout << "3.  Decorations\n";
		cout << "Choose 1, 2, or 3:  ";
		cin >> choice;
		
		//validate choice
		while(choice < 1 || choice > 3)
		{
			cout << "Invalid choice.  Please choose 1, 2, or 3.\n";
			cin >> choice;
		}
				
		switch(choice)
		{
			case 1: outFile << "Candy\r\n";
					break;
					
			case 2: outFile << "Costumes\r\n";
					break;
					
			case 3:	outFile << "Decorations\r\n";
					break;
		}
		
		cout << "\nWhat is the price of the item?  ";
		cin >> price;
		cout << "\nHow many did they buy?  ";
		cin >> quantity;
		
		total = price * quantity * (1+TAX);
		outFile << setprecision(2) << fixed;
		outFile << total << "\r\n";
		
		cout << "\nDo you want to enter more sales? (y or n):  ";
		cin >> runAgain;
	}while(runAgain == 'y' || runAgain == 'Y');
	
	outFile.close();
}

/*
	Function:	totalSales()
	Purpose:  	This function will total all the sales in each of the
				three departments from the sales.txt file and print
				out the totals to the screen.
*/

void totalSales()
{
	//define the three accumulators that will keep running totals for each department
	float candySales = 0.0;
	float costumeSales = 0.0;
	float decorationSales = 0.0;
	float saleAmtTax;
	char line[25]; //this is a character array - also known as a c-string
	ifstream inFile; //input file
	time_t rawtime; //needed to get store the current date & time
	
	inFile.open("sales.txt");
	if(inFile.fail())
		cout << "Error opening input file.\n\n";
	else
	{
		//read from the file with a while loop into the c-string
		while(inFile >> line)
		{
			if(strcmp(line, "Candy") == 0) //strcmp is a c-string compare function
			{
				inFile >> saleAmtTax;
				candySales = candySales + saleAmtTax;
			}
			else if(strcmp(line, "Costumes") == 0)
			{
				inFile >> saleAmtTax;
				costumeSales = costumeSales + saleAmtTax;
			}
			else if(strcmp(line, "Decorations") == 0)
			{
				inFile >> saleAmtTax;
				decorationSales = decorationSales + saleAmtTax;
			}
			else
				cout << "Error processing data from sales.txt\n";
				
		}
		cout << setprecision(2) << fixed;
		time(&rawtime);  //get the current date & time
		
		cout << "\n\nTOTAL SALES ON " << ctime(&rawtime) << "\n"; //prints current date & time
		cout << "-----------------------------------------------------\n";
		cout << setw(13)<< "CANDY: " << setw(10) << candySales << endl;
		cout << setw(13)<< "COSTUMES: " << setw(10) << costumeSales << endl;
		cout << setw(13) << "DECORATIONS: " << setw(10) << decorationSales << endl;
		cout << "-----------------------------------------------------\n";
		cout << endl;
		inFile.close();
	}		
}

