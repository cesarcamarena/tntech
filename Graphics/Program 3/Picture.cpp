#include "Picture.h"
#include "Color.h"
#include "AffineTransforms.h"
#include "TransformNode.h"

#include "Tokens.h"
using CSC1310::Tokens;
#include "ReadFile.h"
using CSC1310::ReadFile;

#include <math.h>
#include <iostream>
using namespace std;

void Picture::render(Pixel* pix)
{
//while(true)
//{
   //BasicObject* sphere = readObject("sphere.txt")

   BasicObject* cylinder = readObject("cylinder.txt");

   BasicObject* cube = readObject("cube.txt");

   //obtaining the window transform
   int width = pix->getWidth();  //the dimensions of the panel on which the drawing will occur
   int height = pix->getHeight();
   double aspect_ratio = (double) height/width;

   double angle = 90.0;            //field of view specified in degrees
   angle = 3.1415927*angle/180.0;  //get the angle in radians

   double w = 2*tan(angle/2);  //the width of the camera is determined by its fov
   double h = w*aspect_ratio;  //the height of the camera is determined by the width and the aspect ratio of the viewport

   Matrix* aspect = AffineTransforms::scale(2.0/w, 2.0/h, 1.0);  //aspect ratio correction transformation
   //the windowing transform takes width and height in pixels and converts from world coordinates to a coordinate system with (0,0) in the upper left and (width,height) in the lower right
   Matrix* window = AffineTransforms::window(width, height);
   Matrix* transform = window->multiply(aspect);
   //sphere->render(pix, transform);

   //InstanceObject* io =  buildInstanceObject("trs1.txt", sphere);
   //InstanceObject* io2 = buildInstanceObject("trs2.txt", sphere);

   //cube->render(pix, transform);

   Scene* scene = new Scene(transform);

   //scene->addInstanceObject(io);
   //scene->addInstanceObject(io2);

   TransformNode* robotArm1 = new TransformNode();
   TransformNode* robotArm2 = new TransformNode();

   robotArm1->buildTransform(AffineTransforms::scale(.2, .2, .2));
   robotArm1->buildTransform(AffineTransforms::translate(0, 0, -3));

   robotArm2->buildTransform(AffineTransforms::scale(.2, .2, .2));
   robotArm2->buildTransform(AffineTransforms::rotateX(45));
   robotArm2->buildTransform(AffineTransforms::translate(-3, .5, 0));
   robotArm2->buildTransform(AffineTransforms::scale(.2, .2, .2));

   TransformNode* baseTransform = new TransformNode();
   baseTransform->buildTransform(AffineTransforms::rotateY(30));
   baseTransform->buildTransform(AffineTransforms::translate(0, -2, 0));

   robotArm1->addNode(baseTransform);
   robotArm2->addNode(baseTransform);

   TransformNode* lowerArmTransform = new TransformNode();
   lowerArmTransform->buildTransform(AffineTransforms::translate(0, 2, 0));
   lowerArmTransform->buildTransform(AffineTransforms::rotateZ(-20));
   lowerArmTransform->buildTransform(AffineTransforms::translate(0, -2, 0));
   lowerArmTransform->buildTransform(AffineTransforms::translate(0, 3, 0));

   InstanceObject* base = new InstanceObject(cylinder);

   baseTransform->addNode(lowerArmTransform);
   baseTransform->addNode(base);

   TransformNode* upperArmTransform = new TransformNode();
   upperArmTransform->buildTransform(AffineTransforms::translate(0, 1, 0));
   upperArmTransform->buildTransform(AffineTransforms::rotateZ(90));
   upperArmTransform->buildTransform(AffineTransforms::translate(0, -1, 0));
   upperArmTransform->buildTransform(AffineTransforms::translate(0, 3, 0));

   InstanceObject* lowerArm = new InstanceObject(cube);
   lowerArm->buildTransform(AffineTransforms::scale(.2, 2, .2));

   lowerArmTransform->addNode(upperArmTransform);
   lowerArmTransform->addNode(lowerArm);

   InstanceObject* upperArm = new InstanceObject(cube);
   upperArm->buildTransform(AffineTransforms::scale(.2, 1, .2));
   upperArmTransform->addNode(upperArm);

   scene->addNode(robotArm1);
   scene->addNode(robotArm2);

   scene->render(pix);

   delete scene;

}

int getFaceIndex(String* face_indices)
{

	Tokens* tokens  = new Tokens(face_indices, '/');
	int num_tokens = tokens->getNumTokens();

   String* face_index = tokens->getToken(0);
   int index = face_index->a_to_i();

   //delete all of the tokens, used and unused
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
   ReadFile* rf = new ReadFile(file_name);   //for reading

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