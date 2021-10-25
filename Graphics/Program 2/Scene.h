#if !defined SCENE_H
#define SCENE_H

#include "InstanceObject.h"
#include "ListArray.h"
#include "ListArrayIterator.h"

using CSC1310::ListArray;
using CSC1310::ListArrayIterator;

class Scene
{
	private:
		ListArray<InstanceObject>* scene;
		Matrix* window;

	public:
		Scene(Matrix* w);
		~Scene();
		void render(Pixel* p);
		void addInstanceObject(InstanceObject* io);
};

#endif