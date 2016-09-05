#include "Vectores.h"
class skybox:vectores
{
public:
void CreateSkyBox(GLuint textures[5],float x, float y, float z, float width, float height, float length)
{
    
        glBindTexture(GL_TEXTURE_2D, textures[4]);
 
        // Center the skybox
        x = x - width  / 2;
        y = y - height / 2;
        z = z - length / 2;
        glBegin(GL_QUADS);             
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,z);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x,y + height, z);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(x,y,z);
               
        glEnd();
        glBindTexture(GL_TEXTURE_2D, textures[3]);
        glBegin(GL_QUADS);     
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x,y,z + length);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x,y + height, z + length);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,                      z + length);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glBegin(GL_QUADS);             
               glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z + length); 
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,	y + height,	z + length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,	y + height,	z);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, textures[1]);
        glBegin(GL_QUADS);             
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x,                 y + height,     z);    
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x,                 y + height,     z + length);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(x,                 y,                      z + length);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x,                 y,                      z);            
               
        glEnd();
        glBindTexture(GL_TEXTURE_2D, textures[2]);
        glBegin(GL_QUADS);     
                glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,z + length);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height,z);
        glEnd();
}
void Trasladar(float x, float y, float z)
{
	float matrizt[16] =
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		x, y, z, 1
	};
	float matrizt2[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, matrizt2);
	Multiplicar(matrizt2, matrizt);
	glLoadMatrixf(matrizt2);

}
};