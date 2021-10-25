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

#include "ListArrayIterator.h"
using CSC1310::ListArrayIterator;

#include <math.h>
#include <iostream>
using namespace std;

void Picture::render(Pixel* px)
{
//while(true)
//{
   const char* fileName1 = "sphere.txt";
   BasicObject* sphere = readObject(fileName1);

   const char* fileName2 = "trs.txt";
   InstanceObject* sphereInstance = buildInstanceObject(fileName2, sphere);

   //obtaining the window transform
   int widthPixels = px->getWidth();  //the dimensions of the panel on which the drawing will occur
   int heightPixels = px->getHeight();

   Scene* scene = new Scene();
   const char* fileName3 = "camera.txt";
   scene->buildTransform(getCameraTransform(fileName3));
   const char* fileName4 = "fov.txt";
   scene->buildTransform(getPerspectiveTransform(fileName4, widthPixels, heightPixels));
   scene->buildTransform(AffineTransforms::window(widthPixels, heightPixels));

   TransformNode* tn = new TransformNode();
   tn->addChild(sphereInstance);
   scene->addTransformNode(tn);

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
         face->addVertex(vertex2);
         face->addVertex(vertex3);

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

   //standard TRS form
   io->buildTransform(scale);  //deletes the matrix when done
   io->buildTransform(rotX);  
   io->buildTransform(rotY);  
   io->buildTransform(rotZ); 
   io->buildTransform(translate); 

   delete rf;
   return io;
}

Matrix* Picture::getCameraTransform(const char* file_name)
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

   Vertex* eye = new Vertex(ex, ey, ez);
   Vertex* at = new Vertex(ax, ay, az);
   Vector* up = new Vector(ux, uy, uz);

   Matrix* camera = AffineTransforms::cameraTransform(eye, at, up);

   delete eye;
   delete at;
   delete up;
   delete rf;

   return camera;
}

Matrix* Picture::getPerspectiveTransform(const char* file_name, int nx, int ny)
{
   ReadFile* rf = new ReadFile(file_name);

   //fov
   String* line = rf->readLine();  //skip this line
   delete line;
   line = rf->readLine();
   double fov = line->a_to_f();
   delete line;

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

   Matrix* A = AffineTransforms::aspect(fov, nx, ny);
   Matrix* N = AffineTransforms::perspectiveNorm(zmax, zmin);
   Matrix* NA = N->multiply(A);

   delete rf;
   delete A;
   delete N;
   
   return NA;
}
