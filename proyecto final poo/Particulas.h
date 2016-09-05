#ifndef _party
#define _party
#include "Imagenes.h"
#include "Vectores.h"
#define GL_GLEXT_PROTOTYPES
#include "glext.h"
#include <math.h>
#include <gl\GL.h>
typedef struct						// Create A Structure For Particle
{
	bool	active;					// Active (Yes/No)
	float	life;					// Particle Life
	float	fade;					// Fade Speed
	float	r;						// Red Value
	float	g;						// Green Value
	float	b;						// Blue Value
	float	x;						// X Position
	float	y;						// Y Position
	float	z;						// Z Position
	float	xi;						// X Direction
	float	yi;						// Y Direction
	float	zi;						// Z Direction
	float	xg;						// X Gravity
	float	yg;						// Y Gravity
	float	zg;						// Z Gravity
}
particles;							// Particles Structure


class Particulas : public Imagenes, public vectores
{
public:

	float ancho, alto;
	unsigned int signoHUD;
	vectores Up, derecha, posc;
	float x, y, z;
	vectores hudlook;
	float	slowdown;
	particles particle[100];
	int loop;
	float	zoom ;
	Particulas(WCHAR texturaHUD[], float ancho, float alto, float x, float y, float z)
	{
		this->ancho = ancho;
		this->alto = alto;
		this->x = x;
		this->y = y;
		this->z = z;
		slowdown = 2.0f;
		zoom = -40.0f;
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
		for (loop = 0; loop < 100; loop++)					// Loop Through All The Particles
		{
			
			particle[loop].active = true;
			particle[loop].life = 1.0f;								// Give All The Particles Full Life
			particle[loop].fade = float(rand() % 100) / 1000.0f + 0.003f;	// Random Fade Speed
			particle[loop].r = 0.0f;	// Select Red Rainbow Color
			particle[loop].g = 0.0f;	// Select Red Rainbow Color
			particle[loop].b = 1.0f;	// Select Red Rainbow Color
			particle[loop].xi = float((rand() % 50) - 26.0f)*10.0f;		// Random Speed On X Axis
			particle[loop].yi = float((rand() % 50) - 25.0f)*10.0f;		// Random Speed On Y Axis
			particle[loop].zi = float((rand() % 50) - 25.0f)*10.0f;		// Random Speed On Z Axis
			particle[loop].xg = 0.0f;									// Set Horizontal Pull To Zero
			particle[loop].yg = -0.8f;								// Set Vertical Pull Downward
			particle[loop].zg = 0.0f;
		}
	}
	~Particulas()
	{
		glDeleteTextures(1, &signoHUD);
	}
	vectores getPosiciones(){
		return posc;
	}
	void Posiciones(vectores posc){
		this->posc = posc;
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
		for (loop = 0; loop < 100; loop++)					// Loop Through All The Particles
		{
			if (particle[loop].active)							// If The Particle Is Active
			{
				glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
				glBegin(GL_TRIANGLE_STRIP);
				glTexCoord2d(1, 1); glVertex3f(x + 0.5f, y + 0.5f, z); // Top Right
				glTexCoord2d(0, 1); glVertex3f(x - 0.5f, y + 0.5f, z); // Top Left
				glTexCoord2d(1, 0); glVertex3f(x + 0.5f, y - 0.5f, z); // Bottom Right
				glTexCoord2d(0, 0); glVertex3f(x - 0.5f, y - 0.5f, z); // Bottom Left
				glEnd();
				particle[loop].x += particle[loop].xi / (slowdown * 1000);// Move On The X Axis By X Speed
				particle[loop].y += particle[loop].yi / (slowdown * 1000);// Move On The Y Axis By Y Speed
				particle[loop].z += particle[loop].zi / (slowdown * 1000);// Move On The Z Axis By Z Speed

				particle[loop].xi += particle[loop].xg;			// Take Pull On X Axis Into Account
				particle[loop].yi += particle[loop].yg;			// Take Pull On Y Axis Into Account
				particle[loop].zi += particle[loop].zg;
			}
		}
		glDisable(GL_CULL_FACE);
		glDisable(GL_ALPHA);
		glDisable(GL_BLEND);
	}
};
#endif




