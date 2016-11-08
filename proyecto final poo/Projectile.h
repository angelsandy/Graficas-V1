#ifndef _projec
#define _projec

#include "Vectores.h"
#include "Modelo.h"

class Proyectil: public vectores {
public:
	vectores posicion, direccion, posicionIni;
	float velocidad;
	Modelo *bala;

	Proyectil(vectores posicionOr, vectores direccionOr){
		this->posicion = posicionOr;
		this->direccion = direccionOr;
		this->posicionIni = posicionOr;
		this->velocidad = 5;
		bala = new Modelo("modelos/Meat.obj", "Texturas/meat.bmp");
	}

	void Actualizar(){
		posicion.x = posicion.x + direccion.x * velocidad; // posicion en x es igual a la poscion que tiene x mas a donde se va a  trasladar por la velocidad
		posicion.y = posicion.y + direccion.y * velocidad;
		posicion.z = posicion.z + direccion.z * velocidad;
		modeloActual();
		return ;
	}

	bool limite(){
		float xfin, yfin, zfin;

		xfin = posicion.x - posicionIni.x;
		yfin = posicion.y - posicionIni.y;
		zfin = posicion.z - posicionIni.z;

		if (abs(xfin) > 200 || abs(zfin) > 200){
			return true;
		}

		return false;
	}
	
	float getPosicionX(){
		return posicion.x;
	}

	float getPosicionY(){
		return posicion.y;
	}

	float getPosicionZ(){
		return posicion.z;
	}
private:

	void modeloActual(){
		glPushMatrix();
		bala->Trasladar(posicion.x ,posicion.y , posicion.z);
		bala->Escalar(1.0, 1.0, 1.0);
		bala->Dibujar();
		glPopMatrix();
	}
};
#endif