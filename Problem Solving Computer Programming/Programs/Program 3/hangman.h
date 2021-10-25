/* This is the header file hangman.h 							 */
/* First, we ensure that we only look at this file if we haven't */
/* already defined the word _HEANGMAN_H; then we define it. 	 */

#ifndef _HANGMAN_H
#define _HANGMAN_H

/*  Now we include the other headers we need */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>


using namespace std;

 
/*  Now we include all the function prototypes */
void printWord(char [], char []);
void printStage(int);
void printLettersGuessed(bool [], char []);



#endif