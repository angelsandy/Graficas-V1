#ifndef _Geom
#define _Geom
#define _USE_MATH_DEFINES
#include <math.h>
#include "Vectores.h"

struct Vertices{
	float Posx, Posy, Posz;
	float Normx, Normy, Normz;
	float u, v;
	float colorr, colorg, colorb, colora;
};

struct Maya{
	Vertices *maya;
	unsigned int *indices;
};




class Primitivos: public vectores
{
public:
	Primitivos() 
	{
	}

	Maya Esfera(int stacks, int slices, float radio, float inicio, float final)
	{
		Vertices *verticesxyzSD=new Vertices[stacks*slices*3];
		unsigned int *indices=new unsigned int[stacks*slices*6];
		Maya salida;
		for(int i=0;i<slices;i++)
		{
			for(int j=0;j<stacks;j++)
			{
				int indice = ( i * stacks + j );
				verticesxyzSD[indice].Posx=radio*cos(((double)j/(stacks-1))*(M_PI*(final-inicio))+ M_PI*inicio-M_PI/2.0)*
					cos(2.0*M_PI*(double)i/(slices-1));
				verticesxyzSD[indice].Posy=radio*sin(((double)j/(stacks-1))*(M_PI*(final-inicio))+ M_PI*inicio-M_PI/2.0);
				verticesxyzSD[indice].Posz=radio*cos(((double)j/(stacks-1))*(M_PI*(final-inicio))+ M_PI*inicio-M_PI/2.0)*
					sin(2.0*M_PI*(double)i/(slices-1));

				verticesxyzSD[indice].Normx=cos(((double)j/(stacks-1))*(M_PI*(final-inicio))+ M_PI*inicio-M_PI/2.0)*
					cos(2.0*M_PI*(double)i/(slices-1));
				verticesxyzSD[indice].Normy=sin(((double)j/(stacks-1))*(M_PI*(final-inicio))+ M_PI*inicio-M_PI/2.0);
				verticesxyzSD[indice].Normz=cos(((double)j/(stacks-1))*(M_PI*(final-inicio))+ M_PI*inicio-M_PI/2.0)*
					sin(2.0*M_PI*(double)i/(slices-1));

				verticesxyzSD[indice].u=(float)1*(1-(float)i/(stacks-1));
				verticesxyzSD[indice].v=(float)1*(1-(float)j/(slices-1));
			}
		}

		int indice=0;
		for(int i=0;i<slices-1;i++)
		{
			for(int j=0;j<stacks-1;j++)
			{				
				indices[indice++]=i * stacks + j;
				indices[indice++]=(i+1) * stacks + j+1;
				indices[indice++]=i * stacks + j+1;

				indices[indice++]=i * stacks + j;
				indices[indice++]=(i+1) * stacks + j;
				indices[indice++]=(i+1) * stacks + j+1;
			}
		}

		salida.maya=verticesxyzSD;
		salida.indices=indices;

		return salida;
	}

	Maya Plano(int vertx, int vertz, float anchof, float profz)
	{
		Vertices *verticesxyzSD=new Vertices[vertx*vertz*3];
		unsigned int *indices=new unsigned int[vertx*vertz*6];

		float deltax=anchof/(vertx-1);
		float deltaz=profz/(vertz-1);

		for (int z = 0; z < vertz; z++)
		{			
			for (int x = 0; x < vertx; x++)
			{									
				verticesxyzSD[z*vertx+x].Posx=(float)x*deltax;
				verticesxyzSD[z*vertx+x].Posy=0.0;
				verticesxyzSD[z*vertx+x].Posz=(float)z*deltaz;

				verticesxyzSD[z*vertx+x].Normx = 0.0;
				verticesxyzSD[z*vertx+x].Normy = 0.0;
				verticesxyzSD[z*vertx+x].Normz = 0.0;
			}			
		}

		for (int z = 0; z < vertz; z++)
		{			
			for (int x = 0; x < vertx; x++)
			{									
				verticesxyzSD[z*vertx+x].u=(float)x/(vertx-1);
				verticesxyzSD[z*vertx+x].v=(float)z/(vertz-1);			
			}			
		}

		vectores aux;
		for (int z = 0; z < (vertz - 1); z++)
		{			
			for (int x = 0; x < (vertx - 1); x++)
			{				
				aux = GeneraNormal(&verticesxyzSD[z*vertx+x].Posx, &verticesxyzSD[(z+1)*vertx+(x+1)].Posx,
					&verticesxyzSD[z*vertx+(x+1)].Posx);

				SumaNormal(&verticesxyzSD[z*vertx+x].Normx, &aux.x);				
				SumaNormal(&verticesxyzSD[(z+1)*vertx+(x+1)].Normx, &aux.x);				
				SumaNormal(&verticesxyzSD[z*vertx+(x+1)].Normx, &aux.x);
				
				aux = GeneraNormal(&verticesxyzSD[z*vertx+x].Posx, &verticesxyzSD[(z+1)*vertx+x].Posx,
					&verticesxyzSD[(z+1)*vertx+(x+1)].Posx);

				SumaNormal(&verticesxyzSD[z*vertx+x].Normx, &aux.x);				
				SumaNormal(&verticesxyzSD[(z+1)*vertx+x].Normx, &aux.x);				
				SumaNormal(&verticesxyzSD[(z+1)*vertx+(x+1)].Normx, &aux.x);				
			}			
		}

		for (int z = 0; z < vertz; z++)
		{			
			for (int x = 0; x < vertx; x++)
			{	
				Normalizacion(&verticesxyzSD[z*vertx+x].Normx);				
			}			
		}
		
		int indice=0;
		for(int i=0;i<vertz-1;i++)
		{
			for(int j=0;j<vertx-1;j++)
			{				
				indices[indice++]=i * vertz + j;
				indices[indice++]=(i+1) * vertz + j+1;
				indices[indice++]=i * vertz + j+1;

				indices[indice++]=i * vertz + j;
				indices[indice++]=(i+1) * vertz + j;
				indices[indice++]=(i+1) * vertz + j+1;
			}
		}


		Maya salida;

		salida.maya=verticesxyzSD;
		salida.indices=indices;

		return salida;
	}
	
	
	Maya Plano(int vertx, int vertz, float anchof, float profz, unsigned char *altura, float tile=1)
	{
		Vertices *verticesxyzSD=new Vertices[vertx*vertz*3];
		unsigned int *indices=new unsigned int[vertx*vertz*6];

		float deltax=anchof/(vertx-1);
		float deltaz=profz/(vertz-1);

		for (int z = 0; z < vertz; z++)
		{			
			for (int x = 0; x < vertx; x++)
			{									
				verticesxyzSD[z*vertx+x].Posx=(float)x*deltax - anchof/2.0;
				verticesxyzSD[z*vertx+x].Posy=(float)altura[z*vertx*4+x*4]/10.0;
				verticesxyzSD[z*vertx+x].Posz=(float)z*deltaz - profz/2.0;

				verticesxyzSD[z*vertx+x].Normx = 0.0;
				verticesxyzSD[z*vertx+x].Normy = 1.0;
				verticesxyzSD[z*vertx+x].Normz = 0.0;
			}			
		}

		for (int z = 0; z < vertz; z++)
		{			
			for (int x = 0; x < vertx; x++)
			{									
				verticesxyzSD[z*vertx+x].u=(float)(x*tile)/(vertx-1);
				verticesxyzSD[z*vertx+x].v=(float)(z*tile)/(vertz-1);			
			}			
		}

		vectores aux;
		for (int z = 0; z < (vertz - 1); z++)
		{			
			for (int x = 0; x < (vertx - 1); x++)
			{				
				aux = GeneraNormal(&verticesxyzSD[z*vertx+x].Posx, &verticesxyzSD[z*vertx+(x+1)].Posx,
					&verticesxyzSD[(z+1)*vertx+(x+1)].Posx);

				SumaNormal(&verticesxyzSD[z*vertx+x].Normx, &aux.x);				
				SumaNormal(&verticesxyzSD[(z+1)*vertx+(x+1)].Normx, &aux.x);				
				SumaNormal(&verticesxyzSD[z*vertx+(x+1)].Normx, &aux.x);
				
				aux = GeneraNormal(&verticesxyzSD[z*vertx+x].Posx, &verticesxyzSD[(z+1)*vertx+x+1].Posx,
					&verticesxyzSD[(z+1)*vertx+x].Posx);

				SumaNormal(&verticesxyzSD[z*vertx+x].Normx, &aux.x);				
				SumaNormal(&verticesxyzSD[(z+1)*vertx+x].Normx, &aux.x);				
				SumaNormal(&verticesxyzSD[(z+1)*vertx+(x+1)].Normx, &aux.x);				
			}			
		}

		for (int z = 0; z < vertz; z++)
		{			
			for (int x = 0; x < vertx; x++)
			{	
				Normalizacion(&verticesxyzSD[z*vertx+x].Normx);
				
			}			
		}


		int indice=0;
		for(int i=0;i<vertz-1;i++)
		{
			for(int j=0;j<vertx-1;j++)
			{				
				indices[indice++]=i * vertz + j;
				indices[indice++]=(i+1) * vertz + j+1;
				indices[indice++]=i * vertz + j+1;

				indices[indice++]=i * vertz + j;
				indices[indice++]=(i+1) * vertz + j;
				indices[indice++]=(i+1) * vertz + j+1;
			}
		}


		Maya salida;

		salida.maya=verticesxyzSD;
		salida.indices=indices;

		return salida;
	}

	Maya Plano3t(int vertx, int vertz, float anchof, float profz, unsigned char *altura, float tile, 
		float alt1, float alt2, float alt3)
	{
		Vertices *verticesxyzSD=new Vertices[vertx*vertz*3];
		unsigned int *indices=new unsigned int[vertx*vertz*6];

		float deltax=anchof/(vertx-1);
		float deltaz=profz/(vertz-1);

		for (int z = 0; z < vertz; z++)
		{			
			for (int x = 0; x < vertx; x++)
			{									
				verticesxyzSD[z*vertx+x].Posx=(float)x*deltax - anchof/2.0;
				verticesxyzSD[z*vertx+x].Posy=(float)altura[z*vertx*4+x*4]/10.0;
				verticesxyzSD[z*vertx+x].Posz=(float)z*deltaz - profz/2.0;

				verticesxyzSD[z*vertx+x].Normx = 0.0;
				verticesxyzSD[z*vertx+x].Normy = 1.0;
				verticesxyzSD[z*vertx+x].Normz = 0.0;

				int alturaTerr = altura[z*vertx*4+x*4];
				
				float valrelalt = (float)alturaTerr-alt1;
				verticesxyzSD[z*vertx+x].colorr=Clampea(1.0-abs(valrelalt)/86.0,0,1);
				verticesxyzSD[z*vertx+x].colorg=Clampea(1.0-abs((float)alturaTerr-alt2)/76.0,0,1);
				verticesxyzSD[z*vertx+x].colorb=Clampea(1.0-abs((float)alturaTerr-alt3)/76.0,0,1);

				float total =  verticesxyzSD[z*vertx+x].colorr;
                    total += verticesxyzSD[z*vertx+x].colorg;
                    total += verticesxyzSD[z*vertx+x].colorb;     

				verticesxyzSD[z*vertx+x].colorr/=total;
				verticesxyzSD[z*vertx+x].colorg/=total;
				verticesxyzSD[z*vertx+x].colorb/=total;

				if ((verticesxyzSD[z*vertx+x].colorr+verticesxyzSD[z*vertx+x].colorg+verticesxyzSD[z*vertx+x].colorb)<0.9)
				{
					float u=verticesxyzSD[z*vertx+x].colorr+verticesxyzSD[z*vertx+x].colorg+verticesxyzSD[z*vertx+x].colorb;
				int h=0;
				}
			}			
		}

		for (int z = 0; z < vertz; z++)
		{			
			for (int x = 0; x < vertx; x++)
			{									
				verticesxyzSD[z*vertx+x].u=(float)(x*tile)/(vertx-1);
				verticesxyzSD[z*vertx+x].v=(float)(z*tile)/(vertz-1);			
			}			
		}

		vectores aux;
		for (int z = 0; z < (vertz - 1); z++)
		{			
			for (int x = 0; x < (vertx - 1); x++)
			{				
				aux = GeneraNormal(&verticesxyzSD[z*vertx+x].Posx, &verticesxyzSD[z*vertx+(x+1)].Posx,
					&verticesxyzSD[(z+1)*vertx+(x+1)].Posx);

				SumaNormal(&verticesxyzSD[z*vertx+x].Normx, &aux.x);				
				SumaNormal(&verticesxyzSD[(z+1)*vertx+(x+1)].Normx, &aux.x);				
				SumaNormal(&verticesxyzSD[z*vertx+(x+1)].Normx, &aux.x);
				
				aux = GeneraNormal(&verticesxyzSD[z*vertx+x].Posx, &verticesxyzSD[(z+1)*vertx+x+1].Posx,
					&verticesxyzSD[(z+1)*vertx+x].Posx);

				SumaNormal(&verticesxyzSD[z*vertx+x].Normx, &aux.x);				
				SumaNormal(&verticesxyzSD[(z+1)*vertx+x].Normx, &aux.x);				
				SumaNormal(&verticesxyzSD[(z+1)*vertx+(x+1)].Normx, &aux.x);				
			}			
		}

		for (int z = 0; z < vertz; z++)
		{			
			for (int x = 0; x < vertx; x++)
			{	
				Normalizacion(&verticesxyzSD[z*vertx+x].Normx);
				
			}			
		}


		int indice=0;
		for(int i=0;i<vertz-1;i++)
		{
			for(int j=0;j<vertx-1;j++)
			{				
				indices[indice++]=i * vertz + j;
				indices[indice++]=(i+1) * vertz + j+1;
				indices[indice++]=i * vertz + j+1;

				indices[indice++]=i * vertz + j;
				indices[indice++]=(i+1) * vertz + j;
				indices[indice++]=(i+1) * vertz + j+1;
			}
		}


		Maya salida;

		salida.maya=verticesxyzSD;
		salida.indices=indices;

		return salida;
	}
};
#endif