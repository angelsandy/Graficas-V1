
#pragma once
#include <string>
using namespace std;
#include "glm.h"
#include "BMPLoader.h"
#include "Vectores.h"

class Modelo : public vectores
{
public:
	Modelo(string modelPath,string textPath = "");
	virtual~Modelo();
	void Dibujar();

private:
	GLMmodel *model;
	BMPClass textur;
	unsigned int IdT;
	unsigned int drawMode;
	
	
	

};
