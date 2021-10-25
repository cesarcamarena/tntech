#include "InstanceObject.h"
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GL/glut.h>
using namespace std;

InstanceObject::InstanceObject(BasicObject* bo) : Node()
{
   obj = bo;
   obj->addRef();
   diffuse = new Color(1.0, 1.0, 1.0);
   normal_texture = NULL;
   color_texture = NULL;
}

InstanceObject::~InstanceObject()
{
   obj->removeRef();
   delete diffuse;

   if (normal_texture != NULL)
   {
      delete normal_texture;
   }

   if (color_texture != NULL)
   {
      delete color_texture;
   }
}

void InstanceObject::setColorTexture(Texture* tex)
{
   if (color_texture == NULL)
   {
      color_texture = tex;
   }
   else
   {
      delete color_texture;
      color_texture = tex;
   }
}

void InstanceObject::setNormalTexture(Texture* tex)
{
   if (normal_texture == NULL)
   {
       normal_texture = tex;
   }
   else
   {
      delete normal_texture;
      normal_texture = tex;
   }
}

void InstanceObject::setDiffuseMaterial(Color* mat)
{
   Color* temp = diffuse;
   diffuse = mat;
   delete temp;
}

void InstanceObject::buildTransform(Matrix* matrix)
{
   Matrix* temp = matrix->multiply(transform);
   delete transform;
   delete matrix;
   transform = temp;
}

void InstanceObject::render(Matrix* laterTransform)
{
   if (normal_texture != NULL)
   {
      GLuint* texNum = new GLuint[2];
      glGenTextures(2, texNum);

      unsigned char* textureColors = readTexture(normal_texture);
      int w = normal_texture->getWidth();
      int h = normal_texture->getHeight();

      glActiveTexture(GL_TEXTURE2); 
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, texNum[0]);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, textureColors);

      textureColors = readTexture(color_texture);
      int w2 = color_texture->getWidth();
      int h2 = color_texture->getHeight();

      glActiveTexture(GL_TEXTURE3);
      glEnable(GL_TEXTURE_2D);
 
      glBindTexture(GL_TEXTURE_2D, texNum[1]);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w2, h2, 0, GL_RGB, GL_UNSIGNED_BYTE, textureColors);
   }
   else
   {
      glDisable(GL_TEXTURE_2D);
   }

   Matrix* updatedMatrix = laterTransform->multiply(transform);

   glPushMatrix();
   glPushAttrib(GL_CURRENT_BIT);

   const float* updated_array = updatedMatrix->toArrayColumnMajor();
   glMultMatrixf(updated_array);

   GLfloat diffuse0[] = {diffuse->getRed(), diffuse->getGreen(), diffuse->getBlue(), 1.0};
  
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse0);
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20.0);

   obj->render();

   glPopMatrix();
   glPopAttrib();

   delete[] updated_array;
   delete updatedMatrix;
}

unsigned char* InstanceObject::readTexture(Texture* tex)
{
   int width = tex->getWidth();
   int height = tex->getHeight();
   int numColors = width*height*3;
   const char* textureFile = tex->getFileName();

   unsigned char* textureColors = new unsigned char[numColors];  

   ifstream infile(textureFile, ios::binary);   
   infile.read((char*)textureColors, numColors);
   infile.close();

   return textureColors;
}
