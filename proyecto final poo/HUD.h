#ifndef _billb
#define _billb
#include "Imagenes.h"
#include "Vectores.h"
#define GL_GLEXT_PROTOTYPES
#include "glext.h"
#include <math.h>
#include <gl\GL.h>

class HUD : public Imagenes, public vectores
{
public:
	float ancho, alto;
	unsigned int signoHUD;
	vectores Up, derecha,posc;
	float x, y, z;
	vectores hudlook;

	HUD(WCHAR texturaHUD[], float ancho, float alto, float x, float y, float z)
	{
		this->ancho = ancho;
		this->alto = alto;
		this->x = x;
		this->y = y;
		this->z = z;
		Up = vectores(0, 1, 0);
		Carga(texturaHUD);
		glGenTextures(1, &signoHUD);
		glBindTexture(GL_TEXTURE_2D, signoHUD);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, Ancho(), Alto(), GL_RGBA, GL_UNSIGNED_BYTE, Dir_Imagen());
		Descarga();
	}
	~HUD()
	{
		glDeleteTextures(1, &signoHUD);
	}
	vectores getPosiciones(){
		vectores posc = { x , y, z };
		return posc;
	}

	 void Draw(vectores posc)
	 {
		 glEnable(GL_CULL_FACE);
		 glCullFace(GL_FRONT);
		 glEnable(GL_BLEND);
		 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		 glEnable(GL_ALPHA_TEST);
		 glAlphaFunc(GL_GREATER, 0);
		 glEnable(GL_TEXTURE_2D);

		 glActiveTexture(GL_TEXTURE0 + 0);
		 glBindTexture(GL_TEXTURE_2D, signoHUD);
		 glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		 glBindTexture(GL_TEXTURE_2D, signoHUD);
		 hudlook = vectores(posc.x - x, 5, posc.z - z);
		 derecha = Normalizacion(Cruz(Up, hudlook));
		 derecha.x *= ancho / 2.0;
		 derecha.z *= ancho / 2.0;
		 glBegin(GL_QUADS);
		 glTexCoord2f(0, 0);
		 glVertex3f(x - derecha.x, y + alto, z - derecha.z);

		 glTexCoord2f(1, 0);
		 glVertex3f(x + derecha.x, y + alto, z + derecha.z);

		 glTexCoord2f(1, 1);
		 glVertex3f(x + derecha.x, y, z + derecha.z);

		 glTexCoord2f(0, 1);
		 glVertex3f(x - derecha.x, y, z - derecha.z);
		
		glEnd();
		glDisable(GL_CULL_FACE);
		glDisable(GL_ALPHA);
		glDisable(GL_BLEND);
	}
};
#endif




