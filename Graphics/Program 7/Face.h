#if !defined (FACE_H)
#define FACE_H

#include "Pixel.h"
#include "Light.h"
#include "Texture.h"

class Face
{
   private:
      ListArray<Vertex>* vertices;
      int sze;
      double* sCoords;
      double* tCoords;

   public:
      Face();
      virtual ~Face();
      void addVertex(Vertex* vertex);
      Vertex* getVertex(int index);
      void setSCoords(double s1, double s2, double s3);
      void setTCoords(double t1, double t2, double t3);
      double getS(int index);
      double getT(int index);
      void render(Pixel* px, Matrix* sceneTransform, Matrix* instanceTransform, Vertex* eye, Light* light, Color* diffuse, Color* amb, double atten, double shine, Matrix* zbuffer, unsigned char* tColors, Texture* tex);
      void drawTriangle(Vertex* first, Vertex* second, Vertex* third, Matrix* zbuffer, Pixel* px, unsigned char* tColors, Texture* tex);
      void calculateColor(Vertex* vertex, Vertex* eye, Light* light, Color* diffuse, Color* amb, double atten, double shine);
      static Vector* getNormal(Vertex* v1, Vertex* v2, Vertex* v3);
      static Vector* averageNormals(Vertex* v, Matrix* normalTransform);
      void displayFace();
};

#endif
