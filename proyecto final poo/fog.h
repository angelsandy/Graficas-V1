#pragma once 
class fog{
public:
	static bool gp;
	void usefog();
private:
	GLuint  filter;
	GLuint fogMode[3];
	GLuint  fogfilter;
	GLfloat fogColor[4];
	float densidad;
};