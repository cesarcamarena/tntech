#if !defined (NODE_H)
#define NODE_H

#include "Pixel.h"
#include "DeleteObject.h"
#include "Light.h"

class Node : public DeleteObject
{
   private:

   protected:
      Matrix* transform;

   public:
      Node();
      virtual ~Node();
      virtual void render(Pixel* px, Matrix* sceneTransform, Matrix* instanceTransform, Vertex* eye, Light* light, Color* amb, double atten, Matrix* zbuffer) = 0;
};

#endif
