#include "AffineTransforms.h"
#include <math.h>

Matrix* AffineTransforms::scale(double x, double y, double z)
{
   Matrix* S = new Matrix(4, 4);

   S->setElement(1,1,x);
   S->setElement(1,2,0);
   S->setElement(1,3,0);
   S->setElement(1,4,0);

   S->setElement(2,1,0);
   S->setElement(2,2,y);
   S->setElement(2,3,0);
   S->setElement(2,4,0);

   S->setElement(3,1,0);
   S->setElement(3,2,0);
   S->setElement(3,3,z);
   S->setElement(3,4,0);

   S->setElement(4,1,0);
   S->setElement(4,2,0);
   S->setElement(4,3,0);
   S->setElement(4,4,1);

   return S;
}

//transform to pixel coords
Matrix* AffineTransforms::window(int xPixels, int yPixels)
{
   Matrix* result = new Matrix(4, 4);
   double nx = xPixels;
   double ny = yPixels;

   //translate (0,0) to the center of the window, and then scale to the correct size so that (1,0) is on the extreme right of the window
   result->setElement(1, 1, nx/2.0);  
   result->setElement(1, 2, 0);
   result->setElement(1, 3, 0);
   result->setElement(1, 4, (nx - 1)/2.0);  
   result->setElement(2, 1, 0);
   result->setElement(2, 2, -ny/2.0);  
   result->setElement(2, 3, 0);
   result->setElement(2, 4, (ny - 1)/2.0);  
   result->setElement(3, 1, 0);
   result->setElement(3, 2, 0);
   result->setElement(3, 3, 1);
   result->setElement(3, 4, 0);
   result->setElement(4, 1, 0);
   result->setElement(4, 2, 0);
   result->setElement(4, 3, 0);
   result->setElement(4, 4, 1.0);

   return result;
}

Matrix* AffineTransforms::translate(double x, double y, double z)
{
   Matrix* m = new Matrix(4, 4);

   m->setElement(1, 1, 1);
   m->setElement(2, 2, 1);
   m->setElement(3, 3, 1);
   m->setElement(4, 4, 1);
   m->setElement(1, 4, x);
   m->setElement(2, 4, y);
   m->setElement(3, 4, z);

   return m;
}

Matrix* AffineTransforms::rotateX(double degrees)
{
   Matrix* x = new Matrix(4, 4);
   double pi = 3.1415927;
   double radians = degrees * pi/180;

   x->setElement(1, 1, 1);
   x->setElement(2, 2, cos(radians));
   x->setElement(2, 3, -1*sin(radians));
   x->setElement(3, 2, sin(radians));
   x->setElement(3, 3, cos(radians));
   x->setElement(4, 4, 1);

   return x;
}

Matrix* AffineTransforms::rotateY(double degrees)
{
   Matrix* y = new Matrix(4, 4);
   double pi = 3.1415927;
   double radians = degrees * pi/180;

   y->setElement(1, 1, cos(radians));
   y->setElement(1, 3, -1*sin(radians));
   y->setElement(2, 2, 1);
   y->setElement(3, 1, sin(radians));
   y->setElement(3, 3, cos(radians));
   y->setElement(4, 4, 1);

   return y;
}

Matrix* AffineTransforms::rotateZ(double degrees)
{
   Matrix* z = new Matrix(4, 4);
   double pi = 3.1415927;
   double radians = degrees * pi/180;

   z->setElement(1, 1, cos(radians));
   z->setElement(1, 2, -1*sin(radians));
   z->setElement(2, 1, sin(radians));
   z->setElement(2, 2, cos(radians));
   z->setElement(3, 3, 1);
   z->setElement(4, 4, 1);

   return z;
}