#if !defined (AFFINETRANSFORMS_H)
#define AFFINETRANSFORMS_H

#include "Matrix.h"
using CSC1310::Matrix;

class AffineTransforms
{
   private:

   public:
      static Matrix* scale(double x, double y, double z);
      static Matrix* windowing(double x, double y);
      static Matrix* aspectRatio(double w, double h);
};

#endif
