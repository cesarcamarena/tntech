#include "InstanceObject.h"

InstanceObject::InstanceObject(BasicObject* bo)
{
   obj = bo;
   obj->addRef();
}

InstanceObject::~InstanceObject()
{
   obj->removeRef();
}

void InstanceObject::buildTransform(Matrix* matrix)
{
   //multiple calls to this method will achieve the proper concatenation (later matrices are on the left)
   Matrix* temp = matrix->multiply(transform);
   delete transform;
   delete matrix;
   transform = temp;
}

void InstanceObject::render(Pixel* px, Matrix* laterTransform)
{
   Matrix* updatedMatrix = laterTransform->multiply(transform);
   obj->render(px, updatedMatrix);
   delete updatedMatrix;
}
