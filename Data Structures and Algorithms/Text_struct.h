#if !defined STRING_STRUCT
#define STRING_STRUCT

struct String_struct
{
   const char* text;
   int sz;  //length of string not including null terminator
};

String_struct* createString(const char* char_array);
void displayString(String_struct* str);
void destroyString(String_struct* str);
int length(String_struct* str);
const char* getText(String_struct* str);

int a_to_i(String_struct* str);
float a_to_f(String_struct* str);
String_struct* i_to_a(int number);
String_struct* f_to_a(float number);

//find the location of a particular character in a String and return the index if found
//preconditions:
//	str is the String being examined for the character delimiter (str must point to a valid String)
//      delimiter is the character being searched for
//      start is the index to start the search at (the first index of the String is 0, start cannot exceed the length of the String)
//postconditions:
//	if the preconditions are met, the index of the first delimiter encountered at or after the start index is returned
//	if the delimiter is not present in the String at index start or later, -1 is returned
//      if the preconditions are not met, no guarantees on output are made
int find(String_struct* str, char delimiter, int start);

//creates a new String that is extracted from an existing String with characters specified by the start and end indices
//preconditions:
//	str is the String from which the substring will be extracted (str must point to a valid String)
//	start and end are the indices used to create the substring
//	start must be less than or equal to end, start must be >= 0, end must be >= 0, end < the length of the String
//postconditions:
//	if the preconditions are met, the String extracted from the parameter String
//	that starts at index start and ends at index end is created and returned
//	the original string is unaffected
String_struct* substr(String_struct* str, int start, int end);

//need to document that this compare only has three possible return values (-1, 0, 1)
int compare(String_struct* str1, String_struct* str2);

#endif