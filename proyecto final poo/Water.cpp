#include "Water.h"
#include "TextureLoader.h"


Water::Water(char *pathTexture) : Primitive()
{
	texture = LoadTexture(pathTexture);
	min = 0.0f;
	max = 200.0f; 
	
}


Water::~Water(void)
{
	
}

void Water::Draw()
{
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glPushAttrib(GL_CURRENT_BIT | GL_TEXTURE_BIT);
	glBindTexture(GL_TEXTURE_2D, texture);


	static float water_factor_min; 
	water_factor_min = min;
	static float water_factor_max;
	water_factor_max = max;
	static float water_size = 30;
	glBegin(GL_QUADS);
	glTexCoord2f(water_factor_min, water_factor_min);
	glColor4f(0.1f, 0.3f, 0.6f, 0.9f);
	glVertex3f(-water_size, 0.0f, water_size);
	
	glTexCoord2f(water_factor_max, water_factor_min);
	glColor4f(0.1f, 0.3f, 0.6f, 0.7f);
	glVertex3f(water_size, 0.0f, water_size);

	glTexCoord2f(water_factor_max, water_factor_max);
	glColor4f(0.1f, 0.3f, 0.6f, 0.7f);
	glVertex3f(water_size, 0.0f, -water_size);

	glTexCoord2f(water_factor_min, water_factor_max);
	glColor4f(0.1f, 0.3f, 0.6f, 0.7f);
	glVertex3f(-water_size, 0.0f, -water_size);
	glEnd();
	glPopAttrib();
}

void Water::Update(){
	if(max<40.0f){
		max+=.001f;
		min+=.001f;
	}
	else{
		max = 20.0f;
		min = 0.0f;
	}
}

void Water::multiplicacion(GLfloat *matriz2, GLfloat *matriz1)
{
	float temp [16];
	for (int i=0; i<16 ; i+=4)
	{
		temp[i]=matriz1[i]*matriz2[0] + matriz1[i+1]*matriz2[4] + matriz1[i+2]*matriz2[8] + matriz1[i+3]*matriz2[12];
		temp[i+1]=matriz1[i]*matriz2[1] + matriz1[i+1]*matriz2[5] + matriz1[i+2]*matriz2[9] + matriz1[i+3]*matriz2[13];
		temp[i+2]=matriz1[i]*matriz2[2] + matriz1[i+1]*matriz2[6] + matriz1[i+2]*matriz2[10] + matriz1[i+3]*matriz2[14];
		temp[i+3]=matriz1[i]*matriz2[3] + matriz1[i+1]*matriz2[7] + matriz1[i+2]*matriz2[11] + matriz1[i+3]*matriz2[15];
	}

	for (int i=0; i<16; i++)
	{
		matriz2[i] = temp[i];
	}
}

void Water::trasladar(float x, float y, float z)
{		 float matrix1[16]={
	1,   0,  0,  0,
	0,   1,  0,  0,
	0,   0,  1,  0,
	x,   y,  z,  1};

	float matrix2[16];

	glGetFloatv(GL_MODELVIEW_MATRIX, matrix2 ); 
	multiplicacion(matrix2,matrix1);
	glLoadMatrixf(matrix2);
}

void Water::escalar(float x, float y, float z)
{       float matrix1[16]={                   
	x,   0,  0,  0,
	0,   y,  0,  0,
	0,   0,  z,  0,
	0,   0,  0,  1};

	float matrix2[16];

	glGetFloatv(GL_MODELVIEW_MATRIX, matrix2 ); 
	multiplicacion(matrix2,matrix1);
	glLoadMatrixf(matrix2);
}