#if !defined (INSTANCEOBJECT_H)
#define INSTANCEOBJECT_H

#include "Pixel.h"
#include "BasicObject.h"
#include "Node.h"
#include "Texture.h"

class InstanceObject : public Node
{
   private:
      BasicObject* obj;
      Color* diffuse;
      double shininess;
	  Texture* texture;

   public:
      InstanceObject(BasicObject* bo);
      virtual ~InstanceObject();
      void setDiffuseMaterial(Color* mat);
      void setShininess(double shine);
      void buildTransform(Matrix* matrix);
      void render(Pixel* px, Matrix* sceneTransform, Matrix* instanceTransform, Vertex* eye, Light* light, Color* amb, double atten, Matrix* zbuffer);
	  unsigned char* readTexture(Texture* tex);
	  void setTexture(Texture* t);
};

#endif
