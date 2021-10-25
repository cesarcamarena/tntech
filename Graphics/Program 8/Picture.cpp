#include "Picture.h"
#include "BasicObject.h"
#include "InstanceObject.h"
#include "AffineTransforms.h"
#include "TransformNode.h"
#include "Scene.h"

#include <iostream>
using namespace std;

void Picture::render(int w, int h)
{

//while(true)
//{

   const char* fileName1 = "sphere_texture.txt";
   BasicObject* obj = new BasicObject(fileName1);

   Matrix* scale1 = AffineTransforms::scale(1, 1, 1);
   Matrix* rotY = AffineTransforms::rotateY(180.0);
   //Matrix* rotX = AffineTransforms::rotateX(90.0);
   Matrix* translate1 = AffineTransforms::translate(0.0, 0.0, 0.0);
   InstanceObject* io = new InstanceObject(obj);
   const char* normal_str = "MoonNormal.raw";
   Texture* moon_normal = new Texture(normal_str, 512, 256);
   const char* color_str = "MoonColor.raw";
   Texture* moon_color = new Texture(color_str, 512, 256);
   io->setNormalTexture(moon_normal);
   io->setColorTexture(moon_color);
   io->setDiffuseMaterial(new Color(1.0, 0.0, 0.0));

   TransformNode* tn1 = new TransformNode();
   tn1->buildTransform(scale1);
   //tn1->buildTransform(rotX);
   tn1->buildTransform(rotY);
   tn1->buildTransform(translate1);
   tn1->addChild(io);

   Scene* scene = new Scene();
   scene->setPointLight(3, 3, 3);
   scene->setCamera(0, 0, 4, 0, 0, 0, 0, 1, 0);
   scene->setPerspective(45.0, -2.0, -20.0);
   scene->addTransformNode(tn1);
   
   scene->render(w, h);

   delete scene;

//}
}
