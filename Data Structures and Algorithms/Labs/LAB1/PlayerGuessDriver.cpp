/*
	File Name: PlayerGuessDriver.cpp
	Author: Cesar Camarena
	Date: January 22, 2017
	Purpose: Lab 1 - Guessing Game
*/
#if !defined (GUESS_ENUM)
#define GUESS_ENUM
   enum GuessEnum {EXACT, TOO_LOW, TOO_HIGH};
#endif

#include "Text.h"
#include "ReadFile.h"
#include "Random.h"
#include "Keyboard.h"

#include <iostream>
using namespace std;

/*
	The getSecret function calls the getRandomInt function with the range[0] being the minimum value,
	and the range[0] being the maximum value that the random integer will be. Then it returns the
	random integer.
*/
int getSecret (int* range)
{
	return getRandomInt(range[0], range[1]);
}

/*
	The getRange function calls in the readString function so that the user may enter the file name
	containing the range, and then calls the getText function to convert the String from readString
	to a cstring. Then, it uses the createReadFile to create an inputFile. With the inputFile being
	created and opened, the function calls two readLine functions to read in the 2 range values as
	strings. Lastly, it calls the a_to_i function to convert the 2 string range values into integer
	data types and returns the int pointer to the dynamically created array, and also deletes the
	inputFile.
*/
int* getRange()
{
	String* inputFilename = readString("Enter the file name containing the range for the secret number: ");
	const char* inputFilenameCstring = getText(inputFilename);
	ReadFile* inputFile = createReadFile(inputFilenameCstring);
	String* lower = readLine(inputFile);
	String* upper = readLine(inputFile);
	
	int* range = new int[2];
	
	range[0] = a_to_i(lower);
	range[1] = a_to_i(upper);
	
	destroyReadFile(inputFile);
	
	return range;
}

/*
	The getGuess function calls in the getValidatedInt function and passes the arguments of what
	the user guesses within the valid range values. The valid range values where passed to this
	function beforehand with a pointer pointing to the 2 range values.
*/
int getGuess(int* range)
{
	return getValidatedInt("Enter your guess: ", range[0], range[1]);
}

/*
	The processGuess function creates a string saying whether it is "Too high" or "Too low", and
	then displays the string, and then destroys the string. The function then returns a GuessEnum.
*/
GuessEnum processGuess(int guess, int secret)
{
	if (guess < secret)
	{
		String* too_low = createString("Too low\n\n");
		displayString(too_low);
		destroyString(too_low);
		
		return TOO_LOW;
	}
	
	if (guess > secret)
	{
		String* too_high = createString("Too high\n\n");
		displayString(too_high);
		destroyString(too_high);
		
		return TOO_HIGH;
	}
	
	if (guess == secret)
	{
		return EXACT;
	}
}

/*
	The play function calls in the getGuess and processGuess functions in order for the play
	function to know whether the guess was too low or not. This function keeps a running total
	of the amount of guesses the user takes. Then it returns the total amount of guesses.
*/
int play (int* range, int secret)
{
	int total_guess = 1;
	int guess;
	
	do
	{
		guess = getGuess(range);
		GuessEnum result = processGuess(guess, secret);
	
		if (result == TOO_LOW)
		{
			total_guess++;
		}
		
		if (result == TOO_HIGH)
		{
			total_guess++;
		}
	
		if (result == EXACT)
		{
			return total_guess;
		}
		
	} while (guess != secret);
}

/*
	This starts the game by asking the user if they are ready to play, and then
	calls in the getRange, getSecret, and play functions in order of it to play
	the guessing game. Lastly, it displays the total amount of guesses the user
	made when they win.
*/
int main()
{
   int total_guess;
   
   String* n = createString("n");
   String* ready_str = readString("Are you ready to play? (y/n) ");

   while (compare(n, ready_str) != 0)
   {
      destroyString(ready_str);

	  randomInit();
	  int* range = getRange();
	  int secret = getSecret(range);
	  total_guess = play(range, secret);

      delete [] range;

      cout << "You got it in " << total_guess << " guesses!\n" << endl;
      cin.ignore();
      ready_str = readString("Are you ready to play? (y/n) ");
   }

   destroyString(ready_str);
   destroyString(n);
   return 0;
}
