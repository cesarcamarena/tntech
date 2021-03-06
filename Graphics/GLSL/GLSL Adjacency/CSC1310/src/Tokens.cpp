#include "Tokens.h"
using CSC1310::Tokens;

#include <iostream>
using namespace std;

Tokens::Tokens(String* str, char delimiter)
{
   max_tokens = 1;
   sz = 0;

   tokens = new String*[max_tokens];
   for (int i = 0; i < max_tokens; i++)
   {
      tokens[i] = NULL;
   }

   int str_len = str->length();
   int current_loc = 0;

   int count = 0;
   while(current_loc < str_len)
   {
	   //I changed this line so that the sphere adjacency file would be read in
	   //it could not process a single digit number as the last index in the face
	   //this is probably due to the CR LF or something
      int next_loc = str->find(delimiter, current_loc);

      if (next_loc > 0)  //a delimiter as the first character is a problem
      {
         String* temp_token = str->substr(current_loc, next_loc - 1);
		 char* temp_c_str = temp_token->get_c_str();  //returns a new char array
		 String* token = new String(temp_c_str);
		 delete[] temp_c_str;
		 delete temp_token;
         addToken(token);
         count++;
      }
      current_loc = next_loc + 1;
   }
}

Tokens::~Tokens()
{
   delete[] tokens;
}

int Tokens::getNumTokens()
{
   return sz;
}

void Tokens::displayTokens()
{
   int num_tokens = sz;
   String** strings = tokens;

   for (int i = 0; i < num_tokens; i++)
   {
      String* str = strings[i];
      str->displayString();
      cout << endl;
   }
}

void Tokens::resize()
{
   String** resize_strings = new String*[2*max_tokens];
   for (int i = 0; i < sz; i++)
   {
      resize_strings[i] = tokens[i];
   }

   for (int i = sz; i < 2*sz; i++)
   {
      resize_strings[i] = NULL;
   }

   delete[] tokens;
   tokens = resize_strings;
   max_tokens = 2*max_tokens;
}

void Tokens::addToken(String* str)
{
   if (sz == max_tokens)
   {
      resize();
   }

   tokens[sz] = str;
   sz++;
}

String* Tokens::getToken(int index)
{
   if (index < 0 && index >= sz) return NULL;
   return tokens[index];
}
