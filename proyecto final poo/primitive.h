#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "vectores.h"

class Primitive
{
protected:
	GLuint texture;
public:
	vectores position;
	vectores rotation;
	vectores scale;

	void Draw()
	{
		position.x = 0;
	}

	void Update()
	{
	}

	void Cambiar()
	{
		Draw();
	}

	Primitive()
	{
		position.x = 0;
		position.y = 0;
		position.z = 0;

		rotation.x = 0;
		rotation.y = 0;
		rotation.z = 0;

		scale.x = 0;
		scale.y = 0;
		scale.z = 0;
	}

	virtual ~Primitive()
	{
	}
};

#endif