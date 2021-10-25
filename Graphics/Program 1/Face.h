#if !defined (FACE_H)
#define FACE_H

#include "ListArray.h"
#include "ListArrayIterator.h"
#include "Vertex.h"
#include "Pixel.h"
#include "Matrix.h"

using CSC1310::ListArray;
using CSC1310::Matrix;
using CSC1310::ListArrayIterator;

class Face
{
	private:
		ListArray<Vertex>* vertices;

	public:
		Face();
		~Face();
		void addVertex(Vertex* v);
		ListArray<Vertex>* getVertices();
		void render(Pixel* p, Matrix* m);
		void renderDDA(Pixel* p, Vertex* v1, Vertex* v2);
		void renderBresenham(Pixel* p, Vertex* v1, Vertex* v2);
};

#endif