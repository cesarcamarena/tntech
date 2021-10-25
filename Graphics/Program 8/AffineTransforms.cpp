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

Matrix* AffineTransforms::perspectiveNorm(double fovx, double ratio, double zmax, double zmin)
{
   double angle = 3.1415927*fovx/180.0;  //get the angle in radians
   double xmax = tan(angle/2);           //the width of the camera is determined by its fov
   double ymax = xmax*ratio;  //the height of the camera is determined by the aspect ratio of the panel upon which the image will be rendered

   //render the object using a perspective normalization matrix
   //transform and distort the object into the canonical clipping volume
   //assumes a symmetrical field of view (xmin = -xmax)

   //near plane zmax maps to -1
   //far plane zmin maps to +1
   //see perspective.xls to view the nonlinear ordering of depths (but depth ordering is preserved)
   double alpha = -1*(zmax + zmin)/(zmax - zmin);  
   double beta = 2*zmax*zmin/(zmax - zmin);    // zmin/far goes to -1 and zmax/near goes to +1
         
   //scale for fov and aspect ratio (fov determines xmax and ymax)
   //want sides of length 2 (if xmax is 1, the side has length 2) 
   //the below transform maintains aspect ratio   
                         
   Matrix* scale = new Matrix(4, 4);
   scale->setElement(1, 1, 1.0/xmax);  
   scale->setElement(1, 2, 0);
   scale->setElement(1, 3, 0);
   scale->setElement(1, 4, 0);
   scale->setElement(2, 1, 0);
   scale->setElement(2, 2, 1.0/ymax);
   scale->setElement(2, 3, 0);
   scale->setElement(2, 4, 0);
   scale->setElement(3, 1, 0);
   scale->setElement(3, 2, 0);
   scale->setElement(3, 3, 1);
   scale->setElement(3, 4, 0);
   scale->setElement(4, 1, 0);
   scale->setElement(4, 2, 0);
   scale->setElement(4, 3, 0);
   scale->setElement(4, 4, 1);

   Matrix* perspective = new Matrix(4, 4);
   perspective->setElement(1, 1, 1);
   perspective->setElement(1, 2, 0);
   perspective->setElement(1, 3, 0);
   perspective->setElement(1, 4, 0);
   perspective->setElement(2, 1, 0);
   perspective->setElement(2, 2, 1);
   perspective->setElement(2, 3, 0);
   perspective->setElement(2, 4, 0);
   perspective->setElement(3, 1, 0);
   perspective->setElement(3, 2, 0);
   perspective->setElement(3, 3, alpha);
   perspective->setElement(3, 4, beta);
   perspective->setElement(4, 1, 0);
   perspective->setElement(4, 2, 0);
   perspective->setElement(4, 3, -1);
   perspective->setElement(4, 4, 0);

   Matrix* temp = perspective->multiply(scale);
   delete scale;
   delete perspective;
   return temp;
}



