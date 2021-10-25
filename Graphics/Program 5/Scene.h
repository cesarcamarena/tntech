#if !defined (SCENE_H)
#define SCENE_H

#include "Pixel.h"
#include "TransformNode.h"

class Scene
{
   private:
      ListArray<TransformNode>* transformNodes;
      Matrix* sceneTransform;

   public:
      Scene();
      virtual ~Scene();
      void addTransformNode(TransformNode* tn);
      void buildTransform(Matrix* mat);
      void render(Pixel* px);
};

#endif
