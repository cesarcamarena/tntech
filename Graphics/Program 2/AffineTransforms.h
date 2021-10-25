#if !defined AFFINE_TRANSFORMS_H
#define AFFINE_TRANSFORMS_H

#include "Matrix.h"
using CSC1310::Matrix;

class AffineTransforms
{
   private:

   public:
      static Matrix* window(int xPixels, int yPixels);
      static Matrix* scale(double x, double y, double z);
      static Matrix* translate(double x, double y, double z);
      static Matrix* rotateX(double degrees);
      static Matrix* rotateY(double degrees);
      static Matrix* rotateZ(double degrees);
};

#endif
