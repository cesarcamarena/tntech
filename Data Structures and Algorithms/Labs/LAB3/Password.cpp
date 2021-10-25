/*
	Cesar Camarena & Adam Rucker
	2/2/2017
	Lab 3/ Fallout Lab
*/	
#include "Password.h"
#include "Text.h"
#include "ListArray.h"
#include "ListArrayIterator.h"
//using CSC2110::ListArrayIterator;
#include <iostream>
using namespace std;
using CSC2110::String;
using CSC2110::ListArray;
using CSC2110::ListArrayIterator;
/*
using namespace CSC2110::String;
using namespace CSC2110::ListArray;
*/
int Password::getNumMatches(String* curr_word, String* word_guess)
{
	int numOfSameCharacters = 0;
	for(int i = 0; i < curr_word->length();i++)
	{
		if(curr_word->charAt(i) == word_guess->charAt(i))
			numOfSameCharacters++;
	}
	
	return numOfSameCharacters;
}

void Password::displayViableWords()
{
	ListArrayIterator<String>* listIterator = viable_words->iterator();
	while(listIterator->hasNext())
	{
		listIterator->next()->displayString();
		cout << endl;
	}
	delete listIterator;
}


Password::Password()
{
	viable_words = new ListArray<String>;
	all_words = new ListArray<String>;
	int len = 0;
}

Password::~Password()
{
	ListArrayIterator<String>* listIterator = all_words->iterator();
	while(listIterator->hasNext())
	{
		String* str = listIterator->next();
		delete str;
	}
	
	delete listIterator;
	delete viable_words;
	delete all_words;
}

void Password::addWord(String* word)
{
	if(word->length() <= 0)
		return;
	if(len == 0)
	{
		len = word->length();
	}
	if(word->length() == len)
	{
		all_words->add(word);
		viable_words->add(word);
	}
		
}

int Password::getNumberOfPasswordsLeft()
{
	return viable_words->size();
}

String* Password::getOriginalWord(int index)
{
	String* str = all_words->get(index);
	return str;
}


void Password::guess(int try_password, int num_matches)
{
	String* password_attempt = all_words->get(try_password);
	
	for(int i =  viable_words->size(); i >= 1; i--)
	{
		int test = getNumMatches(password_attempt, viable_words->get(i));//could have used a local variable to store viable_words->get(i) but it is not needed except in the function call
		
		if(test != num_matches)
		{
			viable_words->remove(i);
		}
	}
}


int Password::bestGuess()
{
   int best_guess_index = -1;
   int best_num_eliminated = -1;
   int num_viable_passwords = getNumberOfPasswordsLeft();

   //loop over ALL words, even if they have been eliminated as the password
   int count = 1;
   ListArrayIterator<String>* all_iter = all_words->iterator();
   while(all_iter->hasNext())
   {
      String* original_word = all_iter->next();

      //loop over only those words that could still be the password
      //count up the number of matches between a possible password and a word in the original list
      int* count_num_matches = new int[len + 1];

      for (int i = 0; i < len; i++) 
      {
         count_num_matches[i] = 0;
      }

      ListArrayIterator<String>* viable_iter = viable_words->iterator();
      while(viable_iter->hasNext())
      {
         String* viable_word = viable_iter->next();
         int num_matches = getNumMatches(viable_word, original_word);
         count_num_matches[num_matches]++;
      }
      delete viable_iter;

      //find the largest number in the count_num_matches array
      //the largest number indicates the guess that will generate the most eliminations
      int most_num_matches = 0;
      for (int j = 0; j < len; j++) 
      {
         int curr_num_matches = count_num_matches[j];
         if (curr_num_matches > most_num_matches)
         {
            most_num_matches = curr_num_matches;
         }
      }

      //compute the fewest that can possibly be eliminated by guessing the current word (original list)
      int num_eliminated = num_viable_passwords - most_num_matches;

      //select the word to guess that maximizes the minimum number of eliminations (minimax)
      if (num_eliminated > best_num_eliminated)
      {
         best_num_eliminated = num_eliminated;
         best_guess_index = count;
      }
      
      count++;
      delete[] count_num_matches;
   }

   delete all_iter;
   return best_guess_index;  //return a 1-based index into the all_words list of words (careful)
}

