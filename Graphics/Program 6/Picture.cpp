#include "Picture.h"
#include "Color.h"
#include "AffineTransforms.h"
#include "Scene.h"
#include "Vertex.h"
#include "Vector.h"

#include "Tokens.h"
using CSC1310::Tokens;
#include "ReadFile.h"
using CSC1310::ReadFile;

#include <math.h>
#include <iostream>
using namespace std;

void Picture::render(Pixel* px)
{
//while(true)
//{
   const char* fileName1 = "sphere.txt";
   BasicObject* sphere = readObject(fileName1);
   //delete[] fileName;

   const char* fileName2 = "trs.txt";
   InstanceObject* sphereInstance = buildInstanceObject(fileName2, sphere);
   //delete[] fileName;

   const char* fileName3 = "shade.txt";
   Light* pointLight = new Light();
   pointLight->setLocation(new Vertex(0, 0, 0));
   pointLight->setColor(new Color(1, 1, 1));

   Color* ambientColor = new Color(0, 0, 0);
   double linearAttenuation = 0;
   double shininess = 0;
   getShadingValues(fileName3, pointLight, ambientColor, linearAttenuation, shininess);
   //delete[] fileName;
   sphereInstance->setShininess(shininess);

   //obtaining the window transform
   int widthPixels = px->getWidth();  //the dimensions of the panel on which the drawing will occur
   int heightPixels = px->getHeight();
   Scene* scene = new Scene(ambientColor, linearAttenuation);

   const char* fileName4 = "camera.txt";
   Vertex* eye = new Vertex(0, 0, 4);
   scene->buildTransform(getCameraTransform(fileName4, eye));

   const char* fileName5 = "fov.txt";
   scene->buildTransform(getPerspectiveTransform(fileName5, widthPixels, heightPixels));
   scene->buildTransform(AffineTransforms::window(widthPixels, heightPixels));

   TransformNode* tn = new TransformNode();
   tn->addChild(sphereInstance);
   scene->addTransformNode(tn);

   scene->setPointLight(pointLight);
   scene->setEyePoint(eye);

   scene->render(px);
   delete scene;
//}
}

int getFaceIndex(String* face_indices)
{
	Tokens* tokens  = new Tokens(face_indices, '/');
	int num_tokens = tokens->getNumTokens();

   String* face_index = tokens->getToken(0);
   int index = face_index->a_to_i();

   //the rest of the tokens are not used, but need to be deleted
   for (int i = 0; i < num_tokens; i++)
   {
      String* temp = tokens->getToken(i);
      delete temp;
   }
   
   delete tokens;
   return index;
}

BasicObject* Picture::readObject(const char* file_name)
{
   BasicObject* obj = new BasicObject();
   ReadFile* rf = new ReadFile(file_name); //assumed to be a read if a delimiter is specified

   ListArray<Vertex> vertices;
   double x, y, z;
   String* v = new String("v");
   String* f = new String("f");

   String* line = rf->readLine();
   while (!rf->eof())
   {
      Tokens* tokens = new Tokens(line, ' ');
	  int num_tokens = tokens->getNumTokens();
      String* token = tokens->getToken(0);

      //all vertices are held in the vertices list so that the faces can be created
      if (token->compare(v) == 0)  //vertices
      {
         delete token;

         token = tokens->getToken(1);
         x = token->a_to_f();
         delete token;

         token = tokens->getToken(2);
         y = token->a_to_f();
         delete token;

         token = tokens->getToken(3);
         z = token->a_to_f();
         delete token;

         Vertex* vertex = new Vertex(x, y, z);
         vertices.add(vertex);
         obj->addVertex(vertex);
      }

      else if (token->compare(f) == 0)  //face definition
      {
         delete token;

         String* face_indices = tokens->getToken(1);
         int index1 = getFaceIndex(face_indices);
         delete face_indices;
		 
         face_indices = tokens->getToken(2);
         int index2 = getFaceIndex(face_indices);
         delete face_indices;
		 
         face_indices = tokens->getToken(3);
         int index3 = getFaceIndex(face_indices);
         delete face_indices;

         Face* face = new Face();

         Vertex* vertex1 = vertices.get(index1);
         Vertex* vertex2 = vertices.get(index2);
         Vertex* vertex3 = vertices.get(index3);

         face->addVertex(vertex1);
         vertex1->addFace(face);  //vertices need to remember which faces they belong to
         face->addVertex(vertex2);
         vertex2->addFace(face);
         face->addVertex(vertex3);
         vertex3->addFace(face);

         obj->addFace(face);
      }

      //still need to delete the tokens even if the line is completely disregarded
      else  
      {
			for (int i = 0; i < num_tokens; i++)
			{
				String* temp = tokens->getToken(i);
				delete temp;
			}
      }

	  delete line;
      delete tokens;
	  line = rf->readLine();
   }

   delete line;
   delete v;
   delete f;
   delete rf;
   
   return obj;
}

InstanceObject* Picture::buildInstanceObject(const char* file_name, BasicObject* obj)
{
   InstanceObject* io = new InstanceObject(obj);
   ReadFile* rf = new ReadFile(file_name);

   //scale transformation
   String* line = rf->readLine();  //skip this line 
   delete line;
   line = rf->readLine();
   float sx = line->a_to_f();
   delete line;
   line = rf->readLine();
   float sy = line->a_to_f();
   delete line;
   line = rf->readLine();
   float sz = line->a_to_f();
   delete line;
   Matrix* scale = AffineTransforms::scale(sx, sy, sz);

   //rotation transformations
   line = rf->readLine();  //skip this line
   delete line;
   line = rf->readLine();
   float rx = line->a_to_f();
   delete line;
   Matrix* rotX = AffineTransforms::rotateX(rx);
   line = rf->readLine();
   float ry = line->a_to_f();
   delete line;
   Matrix* rotY = AffineTransforms::rotateY(ry);
   line = rf->readLine();
   float rz = line->a_to_f();
   delete line;
   Matrix* rotZ = AffineTransforms::rotateZ(rz);

   //translation transformation
   line = rf->readLine();  //skip this line
   delete line;
   line = rf->readLine();
   float tx = line->a_to_f();
   delete line;
   line = rf->readLine();
   float ty = line->a_to_f();
   delete line;
   line = rf->readLine();
   float tz = line->a_to_f();
   delete line;
   Matrix* translate = AffineTransforms::translate(tx, ty, tz);
   
   //material
   line = rf->readLine();  //skip this line
   delete line;
   line = rf->readLine();
   double mr = line->a_to_f();
   delete line;
   line = rf->readLine();
   double mg = line->a_to_f();
   delete line;
   line = rf->readLine();
   double mb = line->a_to_f();
   delete line;
   Color* mat = new Color(mr, mg, mb);
   io->setDiffuseMaterial(mat);

   //standard TRS form
   io->buildTransform(scale);  //deletes the matrix when done
   io->buildTransform(rotX);  
   io->buildTransform(rotY);  
   io->buildTransform(rotZ); 
   io->buildTransform(translate); 

   delete rf;
   return io;
}

Matrix* Picture::getCameraTransform(const char* file_name, Vertex* eye)
{
   ReadFile* rf = new ReadFile(file_name);

   //eye point
   String* line = rf->readLine();  //skip this line
   delete line;
   line = rf->readLine();
   double ex = line->a_to_f();
   delete line;
   line = rf->readLine();
   double ey = line->a_to_f();
   delete line;
   line = rf->readLine();
   double ez = line->a_to_f();
   delete line;

   //at point
   line = rf->readLine();  //skip this line
   delete line;
   line = rf->readLine();
   double ax = line->a_to_f();
   delete line;
   line = rf->readLine();
   double ay = line->a_to_f();
   delete line;
   line = rf->readLine();
   double az = line->a_to_f();
   delete line;

   //up vector
   line = rf->readLine();  //skip this line
   delete line;
   line = rf->readLine();
   double ux = line->a_to_f();
   delete line;
   line = rf->readLine();
   double uy = line->a_to_f();
   delete line;
   line = rf->readLine();
   double uz = line->a_to_f();
   delete line;
   
   eye->setX(ex);
   eye->setY(ey);
   eye->setZ(ez);
   Vertex* at = new Vertex(ax, ay, az);
   Vector* up = new Vector(ux, uy, uz);

   Matrix* camera = AffineTransforms::cameraTransform(eye, at, up);

   delete at;
   delete up;
   delete rf;

   return camera;
}

Matrix* Picture::getPerspectiveTransform(const char* file_name, int width, int height)
{
   ReadFile* rf = new ReadFile(file_name);

   //fov
   String* line = rf->readLine();  //skip this line
   delete line;
   line = rf->readLine();
   double fov = line->a_to_f();
   delete line;

   double angle = 3.1415927*fov/180.0;  //get the angle in radians
   double xmax = tan(angle/2);           //the width of the camera is determined by its fov
   double ymax = xmax*(height)/(width);  //the height of the camera is determined by the aspect ratio of the panel upon which the image will be rendered

   //zmax
   line = rf->readLine();  //skip this line
   delete line;
   line = rf->readLine();
   double zmax = line->a_to_f();
   delete line;

   //zmin
   line = rf->readLine();  //skip this line
   delete line;
   line = rf->readLine();
   double zmin = line->a_to_f();
   delete line;

   Matrix* pn = AffineTransforms::perspectiveNorm(xmax, ymax, zmax, zmin);

   delete rf;
   return pn;
}

void Picture::getShadingValues(const char* file_name, Light* pointLight, Color* ambientColor, double& atten, double& shine)
{
   ReadFile* rf = new ReadFile(file_name);

   //point light
   String* line = rf->readLine();  //skip this line
   delete line;
   line = rf->readLine();
   double px = line->a_to_f();
   delete line;
   line = rf->readLine();
   double py = line->a_to_f();
   delete line;
   line = rf->readLine();
   double pz = line->a_to_f();
   delete line;

   pointLight->setLocation(new Vertex(px, py, pz));

   //ambient color
   line = rf->readLine();  //skip this line
   delete line;
   line = rf->readLine();
   double ar = line->a_to_f();
   delete line;
   line = rf->readLine();
   double ag = line->a_to_f();
   delete line;
   line = rf->readLine();
   double ab = line->a_to_f();
   delete line;

   ambientColor->setRed(ar);
   ambientColor->setGreen(ag);
   ambientColor->setBlue(ab);

   //linear attenuation
   line = rf->readLine();  //skip this line
   delete line;
   line = rf->readLine();
   atten = line->a_to_f();
   delete line;

   //shininess
   line = rf->readLine();  //skip this line
   delete line;
   line = rf->readLine();
   shine = line->a_to_f();
   delete line;

   delete rf;
}
