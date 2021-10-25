#if !defined TRANSFORM_NODE_H
#define TRANSFORM_NODE_H

#include "Node.h"
#include "ListArray.h"
using CSC1310::ListArray;

class TransformNode : public Node
{
   private:
      ListArray<Node>* children;
      int sze;

   public:
      TransformNode();
      virtual ~TransformNode();
      void addChild(Node* child);
      void buildTransform(Matrix* matrix);
      void render(Pixel* px, Matrix* later);
      //Node* getNode(int index);
};

#endif
