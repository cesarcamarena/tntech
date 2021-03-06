#if !defined (NODE_H)
#define NODE_H

#include "Pixel.h"
#include "DeleteObject.h"
#include "Matrix.h"
using CSC1310::Matrix;

class Node : public DeleteObject
{
   private:

   protected:
      Matrix* transform;

   public:
      Node();
      virtual ~Node();
      virtual void render(Pixel* px, Matrix* matrix, Matrix* zbuffer) = 0;
};

#endif
