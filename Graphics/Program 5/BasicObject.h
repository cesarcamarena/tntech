#if !defined (BASICOBJECT_H)
#define BASICOBJECT_H

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
      void render(Pixel* px, Matrix* transform, Color* diffuse, Matrix* zbuffer);
};

#endif
