/*
*/
#include <iostream>
using namespace std;

const int SIZE = 4;

int main()
{
	//variable definitions
	int* numBooksArray[SIZE];  //array of libraries
	int numGenres;
	int largestGenre, largestLibrary, largestNumBooks;
	
	cout << "\n\nHow many genres of books do you have?  ";
	cin >> numGenres;
	
	//create the arrays
	for(int library = 0; library < SIZE; library++)
	{
		//dynamically allocate a new array of size numGeneres and set to the pointer
		*(numBooksArray + library) = new int[numGenres]; 
	}
	
	//allow user to enter data
	cout << "\n\nPlease enter the number of books in each genre.\n";
	for(int library = 0; library < SIZE; library++)
	{
		for(int genre = 0; genre < numGenres; genre++)
		{
			cout << "\nLIBRARY " << (library + 1) << "  GENRE " << (genre + 1) << ":  " ;
			cin >> *(*(numBooksArray + library) + genre);
		}
	}
	
	//get the largest number of books (library, genre, & number of books)
	largestLibrary = 0;
	largestGenre = 0;
	largestNumBooks = *(*(numBooksArray + 0) + 0);
	for(int library = 0; library < SIZE; library++)
	{
		for(int genre = 0; genre < numGenres; genre++)
		{
			if(*(*(numBooksArray + library) + genre) > largestNumBooks)
			{
				largestNumBooks = *(*(numBooksArray + library) + genre);
				largestLibrary = library;
				largestGenre = genre;
			}
		}
	}
	
	cout << "\n\nLIBRARY " << (largestLibrary + 1) << " has the highest number";
	cout << " of books in GENRE " << (largestGenre + 1) << "\nwhich contains ";
	cout << largestNumBooks << " books!!\n\n";
	
	for(int library = 0; library < SIZE; library++)
	{
		//release dynamically allocated arrays
		delete [] *(numBooksArray + library); 
	}
	
	return 0;
}