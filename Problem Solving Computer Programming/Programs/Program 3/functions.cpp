#include "hangman.h"

/*
	Function Name: printWord
	Function Purpose: To display the underscores and letters of the word.
*/
void printWord(char word[], char underScores[])
{
	int wordLength;
	wordLength = strlen(word);
	
	cout << setfill('*') << setw(120) << "*" << endl;
	cout << "   WORD:  ";
	
	for (int x = 0; x < wordLength; x++)
	{
		cout << underScores[x] << " ";
	}
	cout << endl;
}

/*
	Function Name: printStage
	Function Purpose: Prints the stages of the game.
*/
void printStage(int stage)
{
	switch(stage)
	{
		case 0:		cout << "                       \n";
					cout << "       +-----+         \n";
					cout << "       |     |         \n";
					cout << "       |               \n";
					cout << "       |               \n";
					cout << "       |               \n";
					cout << "       |               \n";
					cout << "       |               \n";
					cout << "       |               \n";
					cout << "   --------------      \n";
					break;
					
		case 1:		cout << "                       \n";
					cout << "       +-----+         \n";
					cout << "       |     |         \n";
					cout << "       |     O         \n";
					cout << "       |               \n";
					cout << "       |               \n";
					cout << "       |               \n";
					cout << "       |               \n";
					cout << "       |               \n";
					cout << "   --------------      \n";
					break;
					
		case 2:		cout << "                       \n";
					cout << "       +-----+         \n";
					cout << "       |     |         \n";
					cout << "       |     O         \n";
					cout << "       |     |         \n";
					cout << "       |     |         \n";
					cout << "       |               \n";
					cout << "       |               \n";
					cout << "       |               \n";
					cout << "   --------------      \n";
					break;
					
		case 3:		cout << "                       \n";
					cout << "       +-----+         \n";
					cout << "       |     |         \n";
					cout << "       |     O         \n";
					cout << "       |     |\\       \n";
					cout << "       |     |         \n";
					cout << "       |               \n";
					cout << "       |               \n";
					cout << "       |               \n";
					cout << "   --------------      \n";
					break;
					
		case 4:		cout << "                       \n";
					cout << "       +-----+         \n";
					cout << "       |     |         \n";
					cout << "       |     O         \n";
					cout << "       |    /|\\       \n";
					cout << "       |     |         \n";
					cout << "       |               \n";
					cout << "       |               \n";
					cout << "       |               \n";
					cout << "   --------------      \n";
					break;
					
		case 5:		cout << "                       \n";
					cout << "       +-----+         \n";
					cout << "       |     |         \n";
					cout << "       |     O         \n";
					cout << "       |    /|\\       \n";
					cout << "       |     |         \n";
					cout << "       |      \\       \n";
					cout << "       |               \n";
					cout << "       |               \n";
					cout << "   --------------      \n";
					break;
					
		case 6:		cout << "                       \n";
					cout << "       +-----+         \n";
					cout << "       |     |         \n";
					cout << "       |     O         \n";
					cout << "       |    /|\\       \n";
					cout << "       |     |         \n";
					cout << "       |    / \\       \n";
					cout << "       |               \n";
					cout << "       |   DEAD!       \n";
					cout << "   --------------      \n\n";
					break;
	}
}

/*
	Function Name: printLettersGuessed
	Function Purpose: Displays the letters that the user has already guessed.
*/
void printLettersGuessed(bool usersGuesses[], char alphabet[])
{
	bool lettersHaveBeenGuessed = false;
	cout << "\n\n   LETTERS YOU HAVE ALREADY GUESSED:  ";
	
	for (int x = 0; x <= 25; x++)
	{
		if (usersGuesses[x] == true)
		{
			cout << alphabet[x] << " ";
			lettersHaveBeenGuessed = true;
		}
	}
	
	if (lettersHaveBeenGuessed == false)
	{
		cout << "(none have been guessed yet)";
	}
	
	cout << endl << endl << setfill('-') << setw(120) << "-" << endl;
}