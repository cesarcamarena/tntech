#include "Scene.h"
#include "ListArrayIterator.h"
using CSC1310::ListArrayIterator;

Scene::Scene(Color* amb, double atten)
{
   sceneTransform = Matrix::identity(4);
   
   transformNodes = new ListArray<TransformNode>();
   light = new Light();
   light->setLocation(new Vertex(3, 3, 3));
   light->setColor(new Color(1, 1, 1));
   eyepoint = new Vertex(0, 0, 4);
   ambient = amb;
   linearAttenuation = atten;
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

   delete light;
   delete eyepoint;
   delete ambient;
}

void Scene::buildTransform(Matrix* mat)
{
   Matrix* temp = mat->multiply(sceneTransform);
   delete sceneTransform;
   delete mat;
   sceneTransform = temp;
}

void Scene::setPointLight(Light* l)
{
   Light* temp = light;
   light = l;
   delete temp;
}

void Scene::setEyePoint(Vertex* eye)
{
   Vertex* temp = eyepoint;
   eyepoint = eye;
   delete temp;
}

void Scene::addTransformNode(TransformNode* tn)
{
   transformNodes->add(tn);
   tn->addRef();
}

void Scene::render(Pixel* px)
{
   //create the zbuffer matrix
   int width = px->getWidth();
   int height = px->getHeight();
   Matrix* zbuffer = new Matrix(height, width);    //rows come first

   //populate zbuffer with -1
   for (int i = 1; i <= height; i++)
   {
      for (int j = 1; j <= width; j++)
      {
         zbuffer->setElement(i, j, -1.0);
      }
   }
   
   //loop over all the Instance instances in the Scene and render them
   ListArrayIterator<TransformNode>* ioIter = transformNodes->iterator();
   while (ioIter->hasNext())
   {
      TransformNode* tn = ioIter->next();
      Matrix* identity = Matrix::identity(4);
      tn->render(px, sceneTransform, identity, eyepoint, light, ambient, linearAttenuation, zbuffer);
      delete identity;
   }

   delete ioIter;
   delete zbuffer;
}
