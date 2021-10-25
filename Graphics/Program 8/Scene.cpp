#include "Scene.h"
#include <GL/glut.h>
#include "AffineTransforms.h"
#include "ListArrayIterator.h"
using CSC1310::ListArrayIterator;

#include <iostream>
using namespace std;

Scene::Scene()
{
   transformNodes = new ListArray<TransformNode>();
}

Scene::~Scene()
{
   ListArrayIterator<TransformNode>* ioIter = transformNodes->iterator();
   while (ioIter->hasNext())
   {
      TransformNode* tn = ioIter->next();
      tn->removeRef();
   }

   delete ioIter;
   delete transformNodes;
}

void Scene::setPointLight(double lxx, double lyy, double lzz)
{
   lx = lxx;
   ly = lyy;
   lz = lzz;
}

void Scene::setCamera(double exx, double eyy, double ezz, double axx, double ayy, double azz, double uxx, double uyy, double uzz)
{
   ex = exx;
   ey = eyy;
   ez = ezz;
   ax = axx;
   ay = ayy;
   az = azz;
   ux = uxx;
   uy = uyy;
   uz = uzz;
}

void Scene::setPerspective(double fov, double n, double f)
{
	fovx = fov;
	nere = n;
	fare = f;
}

void Scene::addTransformNode(TransformNode* tn)
{
   transformNodes->add(tn);
   tn->addRef();
}

void Scene::render(int w, int h)
{
   glClear(GL_DEPTH_BUFFER_BIT);
   glClear(GL_COLOR_BUFFER_BIT);

   glMatrixMode(GL_PROJECTION);
   
   glLoadIdentity();
   float ratio = ((double) h)/w;

   Matrix* perspective = AffineTransforms::perspectiveNorm(fovx, ratio, nere, fare);
   const float* perspective_array = perspective->toArrayColumnMajor();
   glMultMatrixf(perspective_array);
   delete perspective;

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(ex, ey, ez, ax, ay, az, ux, uy, uz);

   GLfloat position0[] = {lx, ly, lz, 1.0};
   GLfloat specular0[] = {1.0, 1.0, 1.0, 1.0};

   GLfloat ambientLight[] = {0.05, 0.05, 0.05, 1.0};
   GLfloat ambientMat[] = {1.0, 1.0, 1.0, 1.0};

   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
   glLightfv(GL_LIGHT0, GL_POSITION, position0);
   glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);

   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientMat);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular0);

   Matrix* identity = Matrix::identity(4);

   ListArrayIterator<TransformNode>* ioIter = transformNodes->iterator();
   while (ioIter->hasNext())
   {
      TransformNode* tn = ioIter->next();
      tn->render(identity);
   }

   delete ioIter;
   delete identity;
}
