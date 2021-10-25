#if !defined (INSTANCEOBJECT_H)
#define INSTANCEOBJECT_H

#include "Pixel.h"
#include "BasicObject.h"
#include "Node.h"

class InstanceObject : public Node
{
   private:
      BasicObject* obj;
      //Matrix* transform;

   public:
      InstanceObject(BasicObject* bo);
      virtual ~InstanceObject();
      void buildTransform(Matrix* matrix);
      void render(Pixel* px, Matrix* transform);
};

#endif
