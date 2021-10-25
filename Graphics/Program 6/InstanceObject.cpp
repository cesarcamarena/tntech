#include "InstanceObject.h"

InstanceObject::InstanceObject(BasicObject* bo)
{
   obj = bo;
   obj->addRef();
   diffuse = new Color(1.0, 1.0, 1.0);
   shininess = 20;
}

InstanceObject::~InstanceObject()
{
   obj->removeRef();  //several ios can use the same bo, so delete is tricky
   delete diffuse;
}

void InstanceObject::setDiffuseMaterial(Color* mat)
{
   Color* temp = diffuse;
   diffuse = mat;
   delete temp;
}

void InstanceObject::setShininess(double shine)
{
   shininess = shine;
}

void InstanceObject::buildTransform(Matrix* matrix)
{
   //multiple calls to this method will achieve the proper concatenation (later matrices are on the left)
   Matrix* temp = matrix->multiply(transform);
   delete transform;
   delete matrix;
   transform = temp;
}

void InstanceObject::render(Pixel* px, Matrix* sceneTransform, Matrix* laterTransform, Vertex* eye, Light* light, Color* amb, double atten, Matrix* zbuffer)
{
   Matrix* updatedMatrix = laterTransform->multiply(transform);
   obj->render(px, sceneTransform, updatedMatrix, eye, light, diffuse, amb, atten, shininess, zbuffer);
   delete updatedMatrix;
}
