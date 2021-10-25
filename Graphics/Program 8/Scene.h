#if !defined (SCENE_H)
#define SCENE_H

#include "TransformNode.h"

class Scene
{
   private:
      ListArray<TransformNode>* transformNodes;
      double lx, ly, lz;
      double ex, ey, ez;
      double ax, ay, az;
      double ux, uy, uz;
      double fovx, nere, fare;

   public:
      Scene();
      virtual ~Scene();
      void addTransformNode(TransformNode* tn);
      void setPointLight(double lx, double ly, double lz);
      void setCamera(double ex, double ey, double ez, double ax, double ay, double az, double ux, double uy, double uz);
      void setPerspective(double fovx, double nere, double faree);
      void render(int w, int h);
};

#endif
