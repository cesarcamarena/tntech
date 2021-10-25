#include "InstanceObject.h"
#include <fstream>

using namespace std;

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
   obj->render(px, sceneTransform, updatedMatrix, eye, light, diffuse, amb, atten, shininess, zbuffer, readTexture(texture), texture);
   delete updatedMatrix;
}

unsigned char* InstanceObject::readTexture(Texture* tex)
{
   int width = tex->getWidth();
   int height = tex->getHeight();
   int numColors = width*height*3;
   char* textureFile = tex->getFileName();

   unsigned char* textureColors = new unsigned char[numColors];  

   ifstream infile(textureFile, ios::binary);   
   infile.read((char*)textureColors, numColors);
   infile.close();

   return textureColors;
}

void InstanceObject::setTexture(Texture* t)
{
   texture = t;
}