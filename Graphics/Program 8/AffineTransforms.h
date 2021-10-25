#if !defined (AFFINETRANSFORMS_H)
#define AFFINETRANSFORMS_H

#include "Matrix.h"
using CSC1310::Matrix;

class AffineTransforms
{
   private:
      static double PI;

   public:
      static Matrix* translate(double x, double y, double z);
      static Matrix* scale(double x, double y, double z);
      static Matrix* rotateX(double degrees);
      static Matrix* rotateY(double degrees);
      static Matrix* rotateZ(double degrees);
      static Matrix* perspectiveNorm(double fovx, double ratio, double zmax, double zmin);
};

#endif
