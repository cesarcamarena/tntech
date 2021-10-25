#include "Scene.h"
#include "ListArrayIterator.h"
using CSC1310::ListArrayIterator;

Scene::Scene()
{
   sceneTransform = Matrix::identity(4);
   transformNodes = new ListArray<TransformNode>();
}

Scene::~Scene()
{
   //clean up all of the basic object heap-allocated memory
   ListArrayIterator<TransformNode>* ioIter = transformNodes->iterator();
   while (ioIter->hasNext())
   {
      TransformNode* tn = ioIter->next();
      tn->removeRef();
   }

   delete ioIter;
   delete transformNodes;
   delete sceneTransform;
}

void Scene::buildTransform(Matrix* mat)
{
   Matrix* temp = mat->multiply(sceneTransform);
   delete sceneTransform;
   delete mat;
   sceneTransform = temp;
   sceneTransform->displayMatrix();
}

void Scene::addTransformNode(TransformNode* tn)
{
   transformNodes->add(tn);
   tn->addRef();
}

void Scene::render(Pixel* px)
{
   //loop over all the Instance instances in the Scene and render them
   ListArrayIterator<TransformNode>* ioIter = transformNodes->iterator();
   while (ioIter->hasNext())
   {
      TransformNode* tn = ioIter->next();
      tn->render(px, sceneTransform);
   }
   delete ioIter;
}
