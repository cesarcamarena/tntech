#if !defined (TRANSFORMNODE_H)
#define TRANSFORMNODE_H

#include "Node.h"

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
      void render(Pixel* px, Matrix* sceneTransform, Matrix* instanceTransform, Vertex* eye, Light* light, Color* amb, double atten, Matrix* zbuffer);
      Node* getNode(int index);
};

#endif
