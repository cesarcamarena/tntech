#include "TransformNode.h"
#include "ListArrayIterator.h"
using CSC1310::ListArrayIterator;

#include <GL/glut.h>

TransformNode::TransformNode() : Node()
{
   children = new ListArray<Node>();
   sze = 0;
}

TransformNode::~TransformNode()
{
   ListArrayIterator<Node>* iter = children->iterator();

   while (iter->hasNext())
   {
      Node* node = iter->next();
      node->removeRef();
   }

   delete children;
   delete iter;
}

void TransformNode::addChild(Node* child)
{
   children->add(sze + 1, child);
   child->addRef();
   sze++;
}

Node* TransformNode::getNode(int index)
{
   return children->get(index);
}

void TransformNode::buildTransform(Matrix* matrix)
{
   //in order to right multiply, concatentating transforms, use the Matrix multiply method thusly
   //multiple calls to this method will achieve the concatenation
   Matrix* temp = matrix->multiply(transform);
   delete transform;
   delete matrix;
   transform = temp;
}

void TransformNode::render(Matrix* later)
{
   //transform passed in from higher in the scene graph
   Matrix* updatedMatrix = later->multiply(transform);

   //glPushMatrix();
   //glPushAttrib(GL_CURRENT_BIT);

   ListArrayIterator<Node>* iter = children->iterator();
   while (iter->hasNext())
   {
      Node* node = iter->next();
      node->render(updatedMatrix);
   }

   //glPopMatrix();
   //glPopAttrib();

   delete iter;
   delete updatedMatrix;
}
