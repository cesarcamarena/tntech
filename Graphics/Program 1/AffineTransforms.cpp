#include "AffineTransforms.h"
#include <math.h>

#include <iostream>
using namespace std;

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


Matrix* AffineTransforms::windowing(double nx, double ny)
{
   Matrix* W = new Matrix(4, 4);

   W->setElement(1,1,nx/2);
   W->setElement(2,2,(-1*ny)/2);
   W->setElement(3,3,1);
   W->setElement(4,4,1);
   W->setElement(1, 4, (nx-1)/2);
   W->setElement(2, 4, (ny-1)/2);

   return W;
}

Matrix* AffineTransforms::aspectRatio(double w, double h)
{
   Matrix* A = new Matrix(4, 4);

   double ratio = (h/w) * 2;

   A->setElement(1, 1, 1);
   A->setElement(2, 2, 2/ratio);
   A->setElement(3, 3, 1);
   A->setElement(4, 4, 1);

   return A;
}