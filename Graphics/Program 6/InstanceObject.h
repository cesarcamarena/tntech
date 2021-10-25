#if !defined (INSTANCEOBJECT_H)
#define INSTANCEOBJECT_H

#include "Pixel.h"
#include "BasicObject.h"
#include "Node.h"

class InstanceObject : public Node
{
   private:
      BasicObject* obj;
      Color* diffuse;
      double shininess;

   public:
      InstanceObject(BasicObject* bo);
      virtual ~InstanceObject();
      void setDiffuseMaterial(Color* mat);
      void setShininess(double shine);
      void buildTransform(Matrix* matrix);
      void render(Pixel* px, Matrix* sceneTransform, Matrix* instanceTransform, Vertex* eye, Light* light, Color* amb, double atten, Matrix* zbuffer);
};

#endif
