#if !defined (TRANSFORM_NODE_H)
#define TRANSFORM_NODE_H

#include "Node.h"
#include "ListArray.h"
#include "ListArrayIterator.h"
using CSC1310::ListArray;
using CSC1310::ListArrayIterator;

class TransformNode : public Node
{
	private:
		ListArray<Node>* nodes;

	public:
		TransformNode();
		~TransformNode();
		void addNode(Node* node);
		void buildTransform(Matrix* matrix);
		void render(Pixel* px, Matrix* matrix);
};

#endif