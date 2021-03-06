#if !defined (SCENE_H)
#define SCENE_H

#include "Light.h"
#include "TransformNode.h"
#include "AffineTransforms.h"
#include "ListArray.h"
using CSC1310::ListArray;

class Scene
{
   private:
      ListArray<TransformNode>* transformNodes;
      Vertex* eyepoint;
      Vertex* atpoint;
      Light* light;
      Color* ambient;
      double linearAttenuation;
      double fovx;
      double zmax;
      double zmin;

   public:
      Scene();
      virtual ~Scene();
      void addTransformNode(TransformNode* tn);
      void render(int w, int h);
      //void setPointLight(Light* l);
      //void setEyePoint(Vertex* eye);
};

#endif
