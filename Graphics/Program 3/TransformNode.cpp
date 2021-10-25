#include "TransformNode.h"

TransformNode::TransformNode()
{
	nodes = new ListArray<Node>();
}

TransformNode::~TransformNode()
{
	delete nodes;
}

void TransformNode::addNode(Node* node)
{
	nodes->add(node);
}

void TransformNode::buildTransform(Matrix* matrix)
{
	Matrix* temp = matrix->multiply(transform);
	delete transform;
	delete matrix;
	transform = temp;
}

void TransformNode::render(Pixel* px, Matrix* matrix)
{
	Matrix* m = matrix->multiply(transform);

	ListArrayIterator<Node>* iter = nodes->iterator();

	while (iter->hasNext())
	{
		Node* node = iter->next();

		node->render(px, m);
	}

	delete iter;
	delete m;
}
