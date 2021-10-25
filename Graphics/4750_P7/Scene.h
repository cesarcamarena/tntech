#if !defined (SCENE_H)
#define SCENE_H

#include "Pixel.h"
#include "TransformNode.h"

class Scene
{
   private:
      ListArray<TransformNode>* transformNodes;
      Matrix* sceneTransform;
      Vertex* eyepoint;
      Light* light;
      Color* ambient;
      double linearAttenuation;

   public:
      Scene(Color* amb, double atten);
      virtual ~Scene();
      void addTransformNode(TransformNode* tn);
      void buildTransform(Matrix* mat);
      void render(Pixel* px);
      void setPointLight(Light* l);
      void setEyePoint(Vertex* eye);
};

#endif
