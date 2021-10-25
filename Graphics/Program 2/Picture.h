#if !defined (PICTURE_H)
#define PICTURE_H

#include "Pixel.h"
#include "BasicObject.h"
#include "InstanceObject.h"
#include "Scene.h"

class Picture
{
   public:
      static void render(Pixel* px);
      static BasicObject* readObject(const char* fileName);
      static InstanceObject* buildInstanceObject(const char* file_name, BasicObject* obj);

   private:
};

#endif
