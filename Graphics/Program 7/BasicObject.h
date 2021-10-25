#if !defined BASIC_OBJECT_H
#define BASIC_OBJECT_H

#include "Face.h"
#include "Node.h"

class BasicObject : public DeleteObject
{
   private:
      ListArray<Face>* faces;
      ListArray<Vertex>* vertices;
      int sze;

   public:
      BasicObject();
      virtual ~BasicObject();
      void addFace(Face* face);
      void addVertex(Vertex* vertex);
      Face* getFace(int index);
      void render(Pixel* px, Matrix* sceneTransform, Matrix* instanceTransform, Vertex* eye, Light* light, Color* diffuse, Color* ambient, double atten, double shine, Matrix* zbuffer, unsigned char* tColors, Texture* tex);
};

#endif
