#ifndef _DOME_H_
#define _DOME_H_

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

class Dome
{
private:
	GLuint texture;
	//float *vertexArray;
	
	//float *uvArray;
	int slices;
	int slides;

	void LoadVertex();
public:
	struct CustomVertex{
		float x;
		float y;
		float z;
		float u;
		float v;
	};
	CustomVertex *vertexArray;
	float radius;

	Dome(char* pathTexture, float _radius, int slides, int slices);
	~Dome();

	void Draw();
	void Update();
};

#endif