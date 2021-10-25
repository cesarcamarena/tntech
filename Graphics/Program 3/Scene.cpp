#include "Scene.h"
#include "ListArrayIterator.h"
using CSC1310::ListArrayIterator;

#include <iostream>
using namespace std;

Scene::Scene(Matrix* window)
{
   sceneTransform = window;

   instances = new ListArray<TransformNode>();
}

Scene::~Scene()
{
   //clean up all of the basic object heap-allocated memory
   ListArrayIterator<TransformNode>* io_iter = instances->iterator();
   while (io_iter->hasNext())
   {
      TransformNode* io = io_iter->next();
      delete io;
   }

   delete io_iter;
   delete instances;
   delete sceneTransform;
}

void Scene::buildTransform(Matrix* mat)
{
   Matrix* temp = mat->multiply(sceneTransform);
   delete sceneTransform;
   delete mat;
   sceneTransform = temp;
}

void Scene::addNode(TransformNode* obj)
{
   instances->add(obj);
}

void Scene::render(Pixel* px)
{
   //loop over all the Instance instances in the Scene and render them
   ListArrayIterator<TransformNode>* io_iter = instances->iterator();
   while (io_iter->hasNext())
   {
      TransformNode* io = io_iter->next();
      io->render(px, sceneTransform);
   }
   delete io_iter;
}
