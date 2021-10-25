#if !defined INSTANCE_OBJECT_H
#define INSTANCE_OBJECT_H

#include "BasicObject.h"
#include "Matrix.h"

class InstanceObject
{
	private:
		BasicObject* object;
		Matrix* instance;

	public:
		InstanceObject(BasicObject* object);
		~InstanceObject();
		void buildTransform(Matrix* m);
		void render(Pixel* px, Matrix* transform);
};

#endif