#if !defined (INSTANCEOBJECT_H)
#define INSTANCEOBJECT_H

#include "BasicObject.h"
#include "Node.h"
#include "Color.h"
#include "Texture.h"

class InstanceObject : public Node
{
   private:
      BasicObject* obj;
      Color* diffuse;
      Texture* color_texture;
      Texture* normal_texture;

   public:
      InstanceObject(BasicObject* bo);
      virtual ~InstanceObject();
      void buildTransform(Matrix* matrix);
      void render(Matrix* transform);
      void setDiffuseMaterial(Color* mat);
      void setColorTexture(Texture* tex);
      void setNormalTexture(Texture* tex);
      static unsigned char* readTexture(Texture* tex);
};

#endif
