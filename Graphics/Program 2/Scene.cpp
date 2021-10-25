#include "Scene.h"

Scene::Scene(Matrix* w)
{
	scene = new ListArray<InstanceObject>();
	window = w;
}

Scene::~Scene()
{
	ListArrayIterator<InstanceObject>* iter = scene->iterator();
	while(iter->hasNext())
	{
		delete iter->next();
	}

	delete iter;
	delete scene;
}

void Scene::render(Pixel* p)
{
	ListArrayIterator<InstanceObject>* iter = scene->iterator();

	while(iter->hasNext())
	{
		InstanceObject* object = iter->next();
		object->render(p, window);
	}

	delete iter;
}

void Scene::addInstanceObject(InstanceObject* io)
{
	scene->add(io);
}