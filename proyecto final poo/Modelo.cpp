#include "Modelo.h"
#include <math.h>
# define PI 3.141516
Modelo::~Modelo()
{
	glmDelete(model);
}

Modelo::Modelo(string Path, string Tpath)
{
	drawMode = GLM_SMOOTH;
	model = glmReadOBJ((char*)Path.c_str());
	glmFacetNormals(model);
	glmVertexNormals(model, 90);
	BMPError e = BMPLoad(Tpath, textur);
	if (e == BMPNOERROR)
	{
		drawMode |= GLM_TEXTURE;
		glGenTextures(1, &IdT);
		glBindTexture(GL_TEXTURE_2D, IdT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, textur.width, textur.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textur.bytes);
	}
}
void Modelo::Dibujar()
{
	if (drawMode & GLM_TEXTURE)
	{
		glBindTexture(GL_TEXTURE_2D, IdT);
	}
	glmDraw(model, drawMode);
	glBindTexture(GL_TEXTURE_2D, NULL);
}