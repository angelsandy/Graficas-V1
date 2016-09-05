#ifndef TERRENOH
#define TERRENOH
#include "Geometrias.h"
#include "Imagenes.h"
#include "ShaderDemo.h"
#define GL_GLEXT_PROTOTYPES
#include "glext.h"
#include <gl\GL.h>
class Terreno:public Primitivos,public Imagenes
{
private:
	float ancho, profundidad;
	unsigned int anchoimagen, altoimagen;
	float deltax, deltaz;
	ShaderDemo *gpuDemo;
public:
	Maya terreno;
	int verx, verz;
	unsigned int textura1, textura2,textura3;


	Terreno(HWND ventana, float ancho, float profundidad, WCHAR height_map_texture_path[], WCHAR texture_path[], WCHAR texture_path2[], WCHAR texture_path3[])
{
	this->ancho = ancho;
	this->profundidad = profundidad;
	Carga(height_map_texture_path);
	terreno = Plano3t(Ancho(),Alto(), ancho, profundidad,Dir_Imagen(),3,0.0,30.0,180.0);
	deltax = this->ancho / Ancho();
	deltaz = this-> profundidad / Alto();
	verx = Ancho();
	verz = Alto();
	Descarga();
    
	Carga(texture_path);
	glGenTextures(1, &textura1);
	glBindTexture(GL_TEXTURE_2D, textura1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, Ancho(), Alto(), GL_RGBA, GL_UNSIGNED_BYTE, Dir_Imagen());
	Descarga();

	Carga(texture_path2);
	glGenTextures(1, &textura2);
	glBindTexture(GL_TEXTURE_2D, textura2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, Ancho(), Alto(), GL_RGBA, GL_UNSIGNED_BYTE, Dir_Imagen());
	Descarga();
	Carga(texture_path3);
	glGenTextures(1, &textura3);
	glBindTexture(GL_TEXTURE_2D, textura3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, Ancho(), Alto(), GL_RGBA, GL_UNSIGNED_BYTE, Dir_Imagen());
	Descarga();
    gpuDemo = new ShaderDemo("basic.vert", "basic.frag");
    gpuDemo->ligador(gpuDemo->vertShader, gpuDemo->fragShader);
	}

void Draw()
{
	int ind = 0;
	int indice;
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	gpuDemo->use();
	glBindTexture(GL_TEXTURE_2D, textura1);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertices), &terreno.maya[0].Posx);
	glNormalPointer(GL_FLOAT, sizeof(Vertices), &terreno.maya[0].Posy);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertices), &terreno.maya[0].u);
	glColorPointer(4, GL_FLOAT, sizeof(Vertices), &terreno.maya[0].colorr);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textura1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textura2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, textura3);
	gpuDemo->PonValorTex("text1", 0);
	gpuDemo->PonValorTex("text2", 1);
	gpuDemo->PonValorTex("text3", 2);

	glDrawElements(GL_TRIANGLES, (verx - 1)*(verz - 1) * 6, GL_UNSIGNED_INT, terreno.indices);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisable(GL_CULL_FACE);
	gpuDemo->desuse();
}
float Superficie(float x, float z)
{
	float indicefx = (x + this->ancho / 2) / deltax;
	float indicefz = (z + this->profundidad / 2) / deltaz;
	int indiceix = (int)indicefx;
	int indiceiz = (int)indicefz;
	float difx = indicefx - indiceix;
	float difz = indicefz - indiceiz;
	float altura;
	float D;

	if (difx > difz)
	{
		vectores v1(terreno.maya[indiceix + 1 + (indiceiz + 1) * verx].Posx - terreno.maya[indiceix + indiceiz * verx].Posx,
			terreno.maya[indiceix + 1 + (indiceiz + 1) * verx].Posy - terreno.maya[indiceix + indiceiz * verx].Posy,
			terreno.maya[indiceix + 1 + (indiceiz + 1) * verx].Posz - terreno.maya[indiceix + indiceiz * verx].Posz);
		vectores v2(terreno.maya[indiceix + 1 + indiceiz * verx].Posx - terreno.maya[indiceix + indiceiz * verx].Posx,
			terreno.maya[indiceix + 1 + indiceiz * verx].Posy - terreno.maya[indiceix + indiceiz * verx].Posy,
			terreno.maya[indiceix + 1 + indiceiz * verx].Posz - terreno.maya[indiceix + indiceiz * verx].Posz);

		vectores normalPlano = Cruz(v1, v2);
		D = -1 * (normalPlano.x * terreno.maya[indiceix + indiceiz * verx].Posx +
			normalPlano.y * terreno.maya[indiceix + indiceiz * verx].Posy +
			normalPlano.z * terreno.maya[indiceix + indiceiz * verx].Posz);
		altura = ((-normalPlano.x * x - normalPlano.z * z - D) / normalPlano.y);
	}
	else
	{
		vectores v1(terreno.maya[indiceix + (indiceiz + 1) * verx].Posx - terreno.maya[indiceix + indiceiz * verx].Posx,
			terreno.maya[indiceix + (indiceiz + 1) * verx].Posy - terreno.maya[indiceix + indiceiz * verx].Posy,
			terreno.maya[indiceix + (indiceiz + 1) * verx].Posz - terreno.maya[indiceix + indiceiz * verx].Posz);

		vectores v2(terreno.maya[indiceix + 1 + (indiceiz + 1) * verx].Posx - terreno.maya[indiceix + indiceiz * verx].Posx,
			terreno.maya[indiceix + 1 + (indiceiz + 1)* verx].Posy - terreno.maya[indiceix + indiceiz * verx].Posy,
			terreno.maya[indiceix + 1 + (indiceiz + 1)* verx].Posz - terreno.maya[indiceix + indiceiz * verx].Posz);


		vectores normalPlano = Cruz(v1, v2);

		D = -1 * (normalPlano.x * terreno.maya[indiceix + indiceiz * verx].Posx +
			normalPlano.y * terreno.maya[indiceix + indiceiz * verx].Posy +
			normalPlano.z * terreno.maya[indiceix + indiceiz * verx].Posz);

		altura = ((-normalPlano.x * x - normalPlano.z * z - D) / normalPlano.y);
	}

	return altura;

}
~Terreno()
{
	delete terreno.maya;
	delete terreno.indices;
	glDeleteTextures(1,&textura1);
}
};
#endif