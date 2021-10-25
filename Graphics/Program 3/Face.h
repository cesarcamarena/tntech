#if !defined FACE_H
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
      void render(Pixel* px, Matrix* transform);
      void renderDDA(Pixel* px, Vertex* v1, Vertex* v2);
      void renderBresenham(Pixel* px, Vertex* v1, Vertex* v2);
      void displayFace();
};

#endif
