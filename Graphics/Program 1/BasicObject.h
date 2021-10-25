#if !defined (BASICOBJECT_H)
#define BASICOBJECT_H

#include "ListArray.h"
#include "Face.h"
#include "Vertex.h"
#include "Pixel.h"
#include "Matrix.h"

class BasicObject
{
	private:
		ListArray<Face>* faces;
		ListArray<Vertex>* vertices;

	public:
		BasicObject();
		~BasicObject();
		void render(Pixel* p, Matrix* m);
		void addFace(Face* f);
		void addVertex(Vertex* v);
};

#endif