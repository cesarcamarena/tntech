#if !defined (FACE_H)
#define FACE_H

#include "Pixel.h"
#include "Light.h"

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
      void render(Pixel* px, Matrix* sceneTransform, Matrix* instanceTransform, Vertex* eye, Light* light, Color* diffuse, Color* amb, double atten, double shine, Matrix* zbuffer);
      void drawTriangle(Vertex* first, Vertex* second, Vertex* third, Matrix* zbuffer, Pixel* px);
      void calculateColor(Vertex* vertex, Vertex* eye, Light* light, Color* diffuse, Color* amb, double atten, double shine);
      static Vector* getNormal(Vertex* v1, Vertex* v2, Vertex* v3);
      static Vector* averageNormals(Vertex* v, Matrix* normalTransform);
      void displayFace();
};

#endif
