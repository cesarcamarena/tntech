#include "ListArray.h"
#include "Face.h"
#include "Vertex.h"
#include "Pixel.h"
#include "Matrix.h"
#include "BasicObject.h"

BasicObject::BasicObject()
{
	faces = new ListArray<Face>();
	vertices = new ListArray<Vertex>();
}

BasicObject::~BasicObject()
{
	ListArrayIterator<Face>* facesIterator = faces->iterator();
	while (facesIterator->hasNext())
	{
		delete facesIterator->next();
	}

	ListArrayIterator<Vertex>* verticesIterator = vertices->iterator();
	while (verticesIterator->hasNext())
	{
		delete verticesIterator->next();
	}

	delete facesIterator;
	delete verticesIterator;
}

void BasicObject::render(Pixel* p, Matrix* m)
{
	ListArrayIterator<Face>* facesIterator = faces->iterator();

	while (facesIterator->hasNext())
	{
		Face* face = facesIterator->next();
		face->render(p, m);
	}

	delete facesIterator;
}

void BasicObject::addFace(Face* f)
{
	faces->add(f);
}

void BasicObject::addVertex(Vertex* v)
{
	vertices->add(v);
}