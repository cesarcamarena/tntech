#include "DeleteObject.h"

#include <iostream>
using namespace std;

DeleteObject::DeleteObject()
{	
   ref = 0;
}

DeleteObject::~DeleteObject(){}

void DeleteObject::addRef()
{
   ref++;
}

void DeleteObject::removeRef()
{
   ref--;
   if (ref == 0)
   {
      delete this;
   }
}
