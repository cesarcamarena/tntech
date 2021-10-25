#include "AffineTransforms.h"
#include <math.h>

double AffineTransforms::PI = 3.1415927;

Matrix* AffineTransforms::translate(double x, double y, double z)
{
   Matrix* T = new Matrix(4, 4);

   T->setElement(1,1,1);
   T->setElement(1,2,0);
   T->setElement(1,3,0);
   T->setElement(1,4,x);

   T->setElement(2,1,0);
   T->setElement(2,2,1);
   T->setElement(2,3,0);
   T->setElement(2,4,y);

   T->setElement(3,1,0);
   T->setElement(3,2,0);
   T->setElement(3,3,1);
   T->setElement(3,4,z);

   T->setElement(4,1,0);
   T->setElement(4,2,0);
   T->setElement(4,3,0);
   T->setElement(4,4,1);

   return T;
}

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

Matrix* AffineTransforms::rotateX(double degrees)
{
   Matrix* R = new Matrix(4, 4);
   double rad = degrees*PI/180.0;

   R->setElement(1,1,1);
   R->setElement(1,2,0);
   R->setElement(1,3,0);
   R->setElement(1,4,0);

   R->setElement(2, 1, 0);
   R->setElement(2, 2, cos(rad));
   R->setElement(2, 3, -1*sin(rad));
   R->setElement(2, 4, 0);

   R->setElement(3, 1, 0);
   R->setElement(3, 2, sin(rad));
   R->setElement(3, 3, cos(rad));
   R->setElement(3, 4, 0);

   R->setElement(4,1,0);
   R->setElement(4,2,0);
   R->setElement(4,3,0);
   R->setElement(4,4,1);

   return R;
}

Matrix* AffineTransforms::rotateY(double degrees)
{
   Matrix* R = new Matrix(4, 4);
   double rad = degrees*PI/180.0;

   R->setElement(1, 1, cos(rad));
   R->setElement(1, 2, 0);
   R->setElement(1, 3, sin(rad));
   R->setElement(1, 4, 0);

   R->setElement(2,1,0);
   R->setElement(2,2,1);
   R->setElement(2,3,0);
   R->setElement(2,4,0);

   R->setElement(3, 1, -1*sin(rad));
   R->setElement(3, 2, 0);
   R->setElement(3, 3, cos(rad));
   R->setElement(3, 4, 0);

   R->setElement(4,1,0);
   R->setElement(4,2,0);
   R->setElement(4,3,0);
   R->setElement(4,4,1);

   return R;
}

Matrix* AffineTransforms::rotateZ(double degrees)
{
   Matrix* R = new Matrix(4, 4);
   double rad = degrees*PI/180.0;

   R->setElement(1, 1, cos(rad));
   R->setElement(1, 2, -1*sin(rad));
   R->setElement(1, 3, 0);
   R->setElement(1, 4, 0);

   R->setElement(2, 1, sin(rad));
   R->setElement(2, 2, cos(rad));
   R->setElement(2, 3, 0);
   R->setElement(2, 4, 0);

   R->setElement(3, 1, 0);
   R->setElement(3, 2, 0);
   R->setElement(3, 3, 1);
   R->setElement(3, 4, 0);

   R->setElement(4, 1, 0);
   R->setElement(4, 2, 0);
   R->setElement(4, 3, 0);
   R->setElement(4, 4, 1);

   return R;
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


