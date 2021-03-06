#pragma once

#include "primitive.h"
class Water : public Primitive
{
public:
	float min, max;

	Water(char *texturePath);
	~Water(void);
	void trasladar(float x, float y, float z);
	void escalar(float x, float y, float z);
	void multiplicacion(GLfloat *mtrz2, GLfloat *mtrz1);
	void Draw();
	void Update();
};