#if !defined (PICTURE_H)
#define PICTURE_H

#include "Pixel.h"
#include "BasicObject.h"
#include "InstanceObject.h"

class Picture
{
   public:
      static void render(Pixel* px);
      static BasicObject* readObject(const char* fileName);
      static InstanceObject* buildInstanceObject(const char* fileName, BasicObject* obj);
      static Matrix* getCameraTransform(const char* fileName, Vertex* eye);
      static Matrix* getPerspectiveTransform(const char* fileName, int width, int height);
      static void getShadingValues(const char* file, Light* l, Color* c, double& at, double& sh);

   private:
};

#endif
