#include "BasicObject.h"
#include "ListArrayIterator.h"
using CSC1310::ListArrayIterator;

BasicObject::BasicObject()
{
   faces = new ListArray<Face>();
   vertices = new ListArray<Vertex>();
   sze = 0;
}

BasicObject::~BasicObject()
{
   //clean up all of the basic object heap-allocated memory
   ListArrayIterator<Face>* faceIter = faces->iterator();
   while (faceIter->hasNext())
   {
      Face* face = faceIter->next();
      delete face;
   }

   ListArrayIterator<Vertex>* vertexIter = vertices->iterator();
   while(vertexIter->hasNext())
   {
      Vertex* vertex = vertexIter->next();
      delete vertex;  
   }

   delete faceIter;
   delete faces;
   delete vertexIter;
   delete vertices;
}

void BasicObject::addVertex(Vertex* vertex)
{
   vertices->add(vertex);
}

void BasicObject::addFace(Face* face)
{
   faces->add(sze + 1, face);
   sze++;
}

Face* BasicObject::getFace(int index)
{
   return faces->get(index);
}

void BasicObject::render(Pixel* px, Matrix* sceneTransform, Matrix* instanceTransform, Vertex* eye, Light* light, Color* diffuse, Color* amb, double atten, double shine, Matrix* zbuffer)
{
   ListArrayIterator<Face>* faceIter = faces->iterator();

   while (faceIter->hasNext())
   {
      Face* face = faceIter->next();
      face->render(px, sceneTransform, instanceTransform, eye, light, diffuse, amb, atten, shine, zbuffer);
   }

   delete faceIter;
}
