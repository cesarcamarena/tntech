#if !defined BASIC_OBJECT_H
#define BASIC_OBJECT_H

#include "Face.h"
#include "DeleteObject.h"

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
      void render(Pixel* px, Matrix* transform);
};

#endif
