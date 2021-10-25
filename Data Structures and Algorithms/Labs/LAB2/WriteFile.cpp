/*
	Cesar Camarena & Anthony Palmer
	1/26/2017
	Lab 2 - CSC 2111
*/

#include "WriteFile.h"
#include <sstream>

WriteFile::WriteFile(const char* file_name)
{
   output_file.open(file_name);
   closed = false;
}

WriteFile::~WriteFile()
{
   close();
}

void WriteFile::close()
{
   if (!this->closed)
   {
      output_file.close();
      closed = true;
   }
}

void WriteFile::writeLine(String* line)
{
   if (!closed && line->length() > 0)
   {
      output_file << line->getText() << endl;
   }
}