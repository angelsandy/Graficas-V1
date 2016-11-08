#include <Windows.h>
#include <math.h>
#include "TextureLoader.h"
#include "Dome.h"

#define PI 3.141516

Dome::Dome(char* pathTexture, float _radius, int _slides, int _slices)
{
	Dome::radius = _radius;
	Dome::slices = _slices;
	Dome::slides = _slides;
	Dome::texture = LoadTexture(pathTexture);
	LoadVertex();
}

Dome::~Dome()
{
	glDeleteTextures(1, &texture);
}

void Dome::LoadVertex()
{
	vertexArray = new CustomVertex[slides * slices];
	
	for(int x = 0; x < slides; x++)
	{
		for(int y = 0; y < slices; y++)
		{
				int arrayIndex = x * slides + y;
				vertexArray[arrayIndex].x = (float)(radius * cos(((float)x / (float)(slides - 1)) * PI / 2.0f)
					* cos(2.0f * PI * (float)y / (float)(slices - 1)));
				vertexArray[arrayIndex].y = (float)(radius * sin(((float)x / (float)(slides - 1)) * PI / 2.0f));
				vertexArray[arrayIndex].z = (float)(radius * cos(((float)x / (float)(slides - 1)) * PI / 2.0f)
					* sin(2.0f * PI * (float)y / (float)(slices - 1)));
				
				vertexArray[arrayIndex].u = (float)(((((float)slides - 1.0f - x) * 0.5f) / (float)slides) * sin((y * 360.0f / (float)slices) * PI / 180.0f)) + 0.5f;
				vertexArray[arrayIndex].v = (float)(((((float)slides - 1.0f - x) * 0.5f) / (float)slides) * cos((y * 360.0f / (float)slices) * PI / 180.0f)) + 0.5f;
		}
	}
}

void Dome::Draw()
{
	glPushMatrix();
	glTranslatef(-0.0f, 0.0f, -radius);

	glPushAttrib(GL_TEXTURE_BIT);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_TRIANGLE_STRIP);

		for ( USHORT y = 0; y < slides - 1; y++ )
		{
			for ( USHORT x = 0; x < slices - 1; x++ )
			{
				int lLeft =  x + y * slides;
				int lRight = (x + 1) + y * slides;
				int tLeft = x + (y + 1) * slices;
				int tRight = (x + 1) + (y + 1) * slices;

				glTexCoord2f(vertexArray[lLeft].u, vertexArray[lLeft].v); glVertex3f(vertexArray[lLeft].x, vertexArray[lLeft].y, vertexArray[lLeft].z);
				glTexCoord2f(vertexArray[lRight].u, vertexArray[lRight].v); glVertex3f(vertexArray[lRight].x, vertexArray[lRight].y, vertexArray[lRight].z);
				glTexCoord2f(vertexArray[tLeft].u, vertexArray[tLeft].v); glVertex3f(vertexArray[tLeft].x, vertexArray[tLeft].y, vertexArray[tLeft].z);

				glTexCoord2f(vertexArray[lRight].u, vertexArray[lRight].v); glVertex3f(vertexArray[lRight].x, vertexArray[lRight].y, vertexArray[lRight].z);
				glTexCoord2f(vertexArray[tRight].u, vertexArray[tRight].v); glVertex3f(vertexArray[tRight].x, vertexArray[tRight].y, vertexArray[tRight].z);
				glTexCoord2f(vertexArray[tLeft].u, vertexArray[tLeft].v); glVertex3f(vertexArray[tLeft].x, vertexArray[tLeft].y, vertexArray[tLeft].z);
			}
		}

		glEnd();
	glPopAttrib();
	glPopMatrix();
}