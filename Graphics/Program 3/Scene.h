#if !defined (SCENE_H)
#define SCENE_H

#include "Pixel.h"
#include "InstanceObject.h"
#include "TransformNode.h"

class Scene
{
   private:
      ListArray<TransformNode>* instances;
      Matrix* sceneTransform;

   public:
      Scene(Matrix* window);
      virtual ~Scene();
      void addNode(TransformNode* obj);
      void render(Pixel* px);
      void buildTransform(Matrix* mat);
};

#endif
