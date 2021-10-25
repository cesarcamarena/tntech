/*
	Cesar Camarena & Adam Rucker
	2/2/2017
	Lab 3/ Fallout Lab
*/	
#if !defined PASSWORD_H
#define PASSWORD_H

#include "ListArray.h"
#include "Text.h"
//complete the includes

using CSC2110::String;
using CSC2110::ListArray;

class Password
{
   private:
      ListArray<String>* viable_words;  //the list of words that can still be the password
      ListArray<String>* all_words;  //the original list of words
      int len;  //the length of the first word entered is stored to check that all subsequent words have the same length

      //a private helper method to report the number of character matches between two Strings
      int getNumMatches(String* curr_word, String* word_guess);

   public:
		Password();
		~Password();
		/*
			Pre:Receives a String pointer
			Post: Adds the string pointer to the List
		*/
		void addWord(String* word);
		/*
			Pre: Receives a guess and number of matches
			Post: Finds the guesses that are still viable and removes the rest
		*/
		void guess(int try_password, int num_matches);
		/*
			Pre:
			Post:Returns the number of possible passwords left
		*/
		int getNumberOfPasswordsLeft();
		/*
			Pre:
			Post: Displays the possible passwords that have not been eliminated
		*/	
		void displayViableWords();
		//was given to us
		int bestGuess();
		/*
			Pre:Receives an index
			Post Returns a word from the List of all passwords not just viable ones
		*/
		String* getOriginalWord(int index);

};

#endif
