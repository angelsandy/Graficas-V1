#ifndef _vect
#define _vect
#include <math.h>
#define PI 3.141516
enum Ejes{ X, Y, Z };
class vectores{
public:

	float x=0;
	float y=0;
	float z=0;
	//Transformaciones para camara
	vectores()
	{ 
		x = 0;
		y = 0;
		z = 0;
	}
	vectores(float vx, float vy, float vz)
	{
		x = vx;
		y = vy;
		z = vz;

	}
	void LlenaIdentidad(float Mat[4][4]) //llena toda la matriz 
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Mat[i][j] = 0;
				if (i == j)
					Mat[i][j] = 1;
			}
		}
	}

	void Rotar(vectores &vec, float grados, int eje = 0)
	{
		float Matriz[4][4]; //crea la matriz 
			float grado1 = grados * 3.141516 / 180; //es el grado en que queremos rotar 
			LlenaIdentidad(Matriz);
			if (eje == Ejes::X) //si el eje que es 0 es igual a X
			{ 
				Matriz[1][1] = cos(grado1);
				Matriz[2][1] = sin(grado1);
				Matriz[1][2] = -sin(grado1);
				Matriz[2][2] = Matriz[1][1]; 
			}
			if (eje == Ejes::Y)
			{
				Matriz[0][0] = cos(grado1);
				Matriz[2][0] = sin(grado1);
				Matriz[0][2] = -sin(grado1); 
				Matriz[2][2] = Matriz[0][0];

			}
			if (eje == Ejes::Z)
			{
				Matriz[0][0] = cos(grado1);
				Matriz[0][1] = -sin(grados);
				Matriz[1][0] = sin(grado1);
				Matriz[1][1] = Matriz[0][0];

			}
			vectores aux; 
			aux.x = vec.x * Matriz[0][0] + vec.y * Matriz[0][1] + vec.z * Matriz[0][2];
			aux.y = vec.y * Matriz[1][0] + vec.y * Matriz[1][1] + vec.z * Matriz[1][2]; 
			aux.z = vec.y * Matriz[2][0] + vec.y * Matriz[2][1] + vec.z * Matriz[2][2];
			vec = aux;
	}
	//Transformaciones para modelos
	void rotarX(float angulo){
		float grados = angulo*PI / 180;
		float matrix2[16];

		float matrix1[16] = {
			1, 0, 0, 0,
			0, cos(grados), sin(grados), 0,
			0, -sin(grados), cos(grados), 0,
			0, 0, 0, 1 };

		glGetFloatv(GL_MODELVIEW_MATRIX, matrix2);
		Multiplicar(matrix2, matrix1);
		glLoadMatrixf(matrix2);
	}

	void rotarY(float angulo){
		float grados = angulo*PI / 180;
		float matrix2[16];

		float matrix1[16] = {
			cos(grados), 0, -sin(grados), 0,
			0, 1, 0, 0,
			sin(grados), 0, cos(grados), 0,
			0, 0, 0, 1 };

		glGetFloatv(GL_MODELVIEW_MATRIX, matrix2);
		Multiplicar(matrix2, matrix1);
		glLoadMatrixf(matrix2);
	}

	void rotarZ(float angulo){
		float grados = angulo*PI / 180;
		float matrix2[16];

		float matrix1[16] = {
			cos(grados), sin(grados), 0, 0,
			-sin(grados), cos(grados), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1 };

		glGetFloatv(GL_MODELVIEW_MATRIX, matrix2);
		Multiplicar(matrix2, matrix1);
		glLoadMatrixf(matrix2);
	}
	void Multiplicar(GLfloat *matriz2, GLfloat *matriz1)
	{
		float temp[16]; // hace la multiplicacion de matriz 4 x 4
		for (int i = 0; i < 16; i += 4)
		{
			temp[i] = matriz1[i] * matriz2[0] + matriz1[i + 1] * matriz2[4] + matriz1[i + 2] * matriz2[8] + matriz1[i + 3] * matriz2[12];
			temp[i + 1] = matriz1[i] * matriz2[1] + matriz1[i + 1] * matriz2[5] + matriz1[i + 2] * matriz2[9] + matriz1[i + 3] * matriz2[13];
			temp[i + 2] = matriz1[i] * matriz2[2] + matriz1[i + 1] * matriz2[6] + matriz1[i + 2] * matriz2[10] + matriz1[i + 3] * matriz2[14];
			temp[i + 3] = matriz1[i] * matriz2[3] + matriz1[i + 1] * matriz2[7] + matriz1[i + 2] * matriz2[11] + matriz1[i + 3] * matriz2[15];
		}
		for (int i = 0; i < 16; i ++)
		{
			matriz2[i] = temp[i];
		}
	}
	void Trasladar(float x,float y,float z)
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
	void Escalar(float x, float y, float z)
	{
		float matrize[16] =
		{
			x, 0, 0, 0,
			0, y, 0, 0,
			0, 0, z, 0,
			0, 0, 0, 1
		};
		float matrize2[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, matrize2);
		Multiplicar(matrize2, matrize);
		glLoadMatrixf(matrize2);
	}
	void RotarY(float angulo)
	{
		float grados = angulo*PI / 180;
		float matriz2[16];
		float matrizr[16]=
		{
			cos(grados), 0, -sin(grados),0,
			0,1,0,0,
			sin(grados), 0, cos(grados),0,
			0,0,0,1
		};
		glGetFloatv(GL_MODELVIEW_MATRIX, matriz2);
		Multiplicar(matriz2, matrizr);
		glLoadMatrixf(matriz2);
	}
	vectores Normalizacion(vectores v1)
	{
		float magnitud = sqrt(v1.x*v1.x + v1.y*v1.y + v1.z*v1.z);
		v1.x /= magnitud;
		v1.y /= magnitud;
		v1.z /= magnitud;
		return v1;
	}
	void Normalizacion(float *v1)
	{
		float magnitud = sqrt((*v1)*(*v1) + (*(v1 + 1))*(*(v1 + 1)) + (*(v1 + 2))*(*(v1 + 2)));
		*v1 /= magnitud;
		*(v1 + 1) /= magnitud;
		*(v1 + 2) /= magnitud;
	}
	vectores Cruz(vectores v1, vectores v2)
	{
		vectores vr;
		vr.x = v1.y *v2.z - v1.z*v2.y;
		vr.y = v1.z *v2.x - v1.x*v2.z;
		vr.z = v1.x *v2.y - v1.y - v2.x;
		return vr;
	}
	float Clampea(float valor, float min, float max)
	{
		if (valor < min)
		{
			valor = min;
		}
		else
		{
			if (valor>max)
			{
				valor = max;
			}
		}
		return valor;
	}
	vectores GeneraNormal(float *v1, float *v2, float *v3)
	{
		vectores ve1, ve2;
		ve1.x = *v2 - *v1;
		ve1.y = *(v2 + 1) - *(v1 + 1);
		ve1.z = *(v2 + 2) - *(v1 + 2);
		ve1.x = *v3 - *v1;
		ve1.y = *(v3 + 1) - *(v1 + 1);
		ve1.z = *(v3 + 2) - *(v1 + 2);
		return Cruz(ve1, ve2);
	}
	void SumaNormal(float *v1, float *v2)
	{
		*v1 += *v2;
		*(v1 + 1) += *(v2 + 1);
		*(v1 + 2) += *(v2 + 2);
	}
};
#endif