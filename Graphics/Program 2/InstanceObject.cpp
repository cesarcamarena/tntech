#include "InstanceObject.h"
#include "BasicObject.h"
#include "Matrix.h"

#include <iostream>
using namespace std;

InstanceObject::InstanceObject(BasicObject* o)
{
	object = o;

	instance = new Matrix(4, 4);
	instance->setElement(1, 1, 1);
	instance->setElement(2, 2, 1);
	instance->setElement(3, 3, 1);
	instance->setElement(4, 4, 1);

	object->addRef();
}

InstanceObject::~InstanceObject()
{
	object->removeRef();
	delete instance;
}

void InstanceObject::buildTransform(Matrix* m)
{
	instance = m->multiply(instance);
}

void InstanceObject::render(Pixel* px, Matrix* transform)
{
	object->render(px, transform->multiply(instance));
}