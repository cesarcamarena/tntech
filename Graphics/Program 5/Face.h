#if !defined (FACE_H)
#define FACE_H

#include "Pixel.h"
#include "Vertex.h"
#include "ListArray.h"
using CSC1310::ListArray;

class Face
{
   private:
      ListArray<Vertex>* vertices;
      int sze;

   public:
      Face();
      virtual ~Face();
      void addVertex(Vertex* vertex);
      Vertex* getVertex(int index);
      void render(Pixel* px, Matrix* transform, Color* diffuse, Matrix* zbuffer);
      void drawTriangle(Vertex* first, Vertex* second, Vertex* third, Matrix* zbuffer, Pixel* px);
      void displayFace();
      static Vector* getNormal(Vertex* v1, Vertex* v2, Vertex* v3);
};

#endif
