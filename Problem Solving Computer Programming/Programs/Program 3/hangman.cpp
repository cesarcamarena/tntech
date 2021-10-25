/*
	Title: hangman.cpp
	Author: Cesar Camarena
	Date: 10/28/16
	Purpose: Hangman Game!
*/

#include "hangman.h"

int main()
{
	//Variable definitions
	char word[21];  //Array of word read from "word bank"
	char underScores[21];  //Array that will at first hold all underscores
	char alphabet[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";  //Array of all uppercase letters in the alphabet
	bool userGuesses[26];  //Array of true/false toggle for each letter of the alphabet
	char letter;
	bool alreadyGuessed;
	int wordLength;
	bool wordGuessed;
	bool again;
	char userInput;
	bool letterFound;
	ifstream inFile;
	
	//Checks to see if the game can read from the text file.
	inFile.open("wordBank.txt");
	if (!inFile)
	{
		cout << "A word could not be found in the word bank." << endl;
	}
	//Program proceeds to the game if the file is read.
	else
	{
		do
		{
			//Initializes the userGuesses array to all false, and sets up the
			//underScores for the game.
			for (int count = 0; count < 26; count++)
			{
				userGuesses[count] = 0;
			}
			
			for (int count = 0; count < 21; count++)
			{
				underScores[count] = '_';
			}
			
			//Initializes the game to stage 0.
			int stage = 0;
			
			//Initializes the game to the word to have been guessed yet.
			wordGuessed = false;
			
			//Reads in the first word of the text file into the character
			//array named word.
			inFile >> word;
			
			//The game starts while the program is not on the last stage and
			//the word has not been guessed yet.
			while (stage != 6 && wordGuessed == false)
			{
				//Prints underscores for the length of the word.
				printWord(word, underScores);
				
				//Prints the stages of the game as the user enters a wrong answer.
				printStage(stage);
				
				//Prints the letters that the user has already guessed.
				printLettersGuessed(userGuesses, alphabet);
				
				do
				{
					//Obtains the letter guess from the user.
					cout << "  WHAT LETTER DO YOU GUESS?  ";
					cin >> letter;
					letter = toupper(letter); //The toupper function will make letter uppercase.
					alreadyGuessed = false;
					cout << endl;
					
					//Tests to see if the user has already guessed that letter.
					for (int x = 0; x < 26; x++)
					{
						if (letter == alphabet [x])
						{
							if (userGuesses[x] == true)
							{
								alreadyGuessed = true;
								cout << "  OOPS! YOU HAVE ALREADY GUESSED THAT LETTER!!  " << endl;
							}
						}
					}
				} while (alreadyGuessed);
				
				//Records the letter from the user as a letter they have guessed.
				for (int x = 0; x < 26; x++)
				{
					if (letter == alphabet [x])
					{
						userGuesses[x] = true;
					}
				}
				
				letterFound = false;
				
				//Determines if the letter the user entered is correct, if so
				//then it will display that they were correct.
				for (int x = 0; x < 21; x++)
				{
					if (letter == word[x])
					{
						cout << setfill('>') << setw(54) << ">" << "  CORRECT!  " << setw(54) << ">" << endl;
						underScores[x] = word[x];
						
						letterFound = true;
					}
				}
				
				//If the user entered a letter that wasn't in the word, then
				//it will display if they were wrong and stage will increment.
				if (letterFound == false)
				{
					cout << setfill('>') << setw(55) << ">" << "  WRONG!  " << setw(55) << ">" << endl;
					
					stage++;
					
					if (stage == 6)
					{
						printStage(stage);
					}
					
				}
				
					cout << "   Press ENTER to Continue." << endl;
					cin.ignore();
					cin.get();
				
				wordLength = strlen(word);
				
				//If the user has guessed every letter in the word, then
				//the game will display that they have won.
				if (strncmp(word, underScores, wordLength) == 0)
				{
					wordGuessed = true;
					cout << setfill(' ') << setw(45) << " " << "YES!  THE WORD WAS:  " << word << endl;
					cout << setfill('>') << setw(54) << ">" << "  YOU WIN!  " << setw(54) << ">" << endl;
				}
			}
			
			//Asks the user if they want to play the game again.
			cout << "   Do you want to play HANGMAN again? (y/n):  ";
			cin >> userInput;
			
			//Determines if their was valid.
			while (userInput != 'Y' && userInput != 'y' && userInput != 'N' && userInput != 'n')
			{
				cout << "\nPlease input a valid answer." << endl;
				cout << "\n\'Y\' for running the program again and \'N\' to end the program." << endl;
				cin >> userInput;
			}
			
			//If their answer was valid, then the game with either play
			//again, or stop depending on their answer.
			if (userInput == 'Y' || userInput == 'y')
				again = true;
			else if (userInput == 'N' || userInput == 'n')
				again = false;
			
		} while (again);
	}
	
	//Closes the text file once the user stops playing the game.
	inFile.close();
	return 0;
}