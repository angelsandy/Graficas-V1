#ifndef _OPENGL_MANAGER_H
#define _OPENGL_MANAGER_H
#define	MAX_PARTICLES	1000
#include <windows.h>
#include <windowsx.h>
#include <gl\GLU.h>
#include <gl\GL.h>
#include "glext.h"
#include <iostream>
#include "camara.h"
#include "textureLoader.h"
#include "Imagenes.h"
#include "Terreno.h"
#include "Vectores.h"
#include "HUD.h"
#include "Skybox.h"  
#include "Modelo.h"
#include "Water.h"
#define MAX_PARTICLES 1500
#define RAIN	0
HUD *GUI[3];
float slowdown = 0.1;
float movmx, movmy, movmz;
float movchainy, movchainz;
float limitchainz, limitchainy;
float velocity = 1.0;
float zoom = -10.0;
float pan = 0.0;
float tilt = 0.0;
float hailsize = 0.1;
int loop;
float pataizmov,patadermov;
bool pataim;
bool col;
int fall, ja[20] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
bool activoRain = false;
float movxb = 0;
//floor colors
float r = 0.0;
float g = 1.0;
float b = 0.0;
float ground_points[21][21][3];
float ground_colors[21][21][4];
float accum = -10.0;
float coinR = 10.0f;
float movy = 6.0f;
float movky = 8.0f;
bool movkyb = false;
GLuint	texture[1];
GLuint  demo1;
Modelo *tree,*casita,*casa,*nave, *jugador2, *jugador3, *jugador4, *pastel, *enemigo1,*water,*cesped,*porta,*skyguy,*banzaibill,*koffing,*coin[100],*bomb,*bombatras,*pataiz,*patader,*mushroom,*bird;
Water *aguita;
float movbomb;
bool bombali=false;
skybox *cielo;
float control_densidad,densidad_niebla;
GLfloat LightAmb2[] = { 1, 1, 1, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLuint textures[5];
GLMmodel *demo;
vectores posicionHud,*posicionMonedas;
int coins = 0;
Camera *camaraprincipal;
bool colisionJugador, colisioncoin[55];
float grados = 80;
float aumentoJugadoresx, aumentoJugadoresy, aumentoJugadoresz;
int cuadrado = 0;
typedef struct {
	// Life
	bool alive;	// is the particle alive?
	float life;	// particle lifespan
	float fade; // decay
	// color
	float red;
	float green;
	float blue;
	// Position/direction
	float xpos;
	float ypos;
	float zpos;
	// Velocity/Direction, only goes down in y dir
	float vel;
	// Gravity
	float gravity;
}particles;						// Particles Structure

particles par_sys[MAX_PARTICLES];	// Particle Array (Room For Particle Info)
static GLfloat colors[12][3] =		// Rainbow Of Colors
{
	{ 0.05f, 0.82f, 0.93 }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }, { 0.05f, 0.82f, 0.93 },
	{ 0.05f, 0.82f, 0.93 }, { 0.0f, 0.0f, 1.0f }, { 0.05f, 0.82f, 0.93 }, { 0.0f, 0.0f, 1.0f },
	{ 0.0f, 0.0f, 1.0f }, { 0.05f, 0.82f, 0.93 }, { 0.0f, 0.0f, 1.0f }, { 0.05f, 0.82f, 0.93 }
};
//----------------Camera--------------//
class Camara: public vectores
{
public:

	vectores posicion, direccion,personajeprincipalvector,diferencia;	
	float aumentox, aumentoy, aumentoz,distancia,distanciafinal;
	Camara(){
	}
	void Actualizacion(){
		gluLookAt(posicion.x, posicion.y, posicion.z , posicion.x + direccion.x, posicion.y + direccion.y, posicion.z + direccion.z, 0, 1, 0);
	}
	void Traslaciondecamara(float vel){

		posicion.x = posicion.x + direccion.x * vel; // posicion en x es igual a la poscion que tiene x mas a donde se va a  trasladar por la velocidad
		posicion.y = posicion.y + direccion.y * vel;
		posicion.z = posicion.z + direccion.z * vel;
		gluLookAt(posicion.x, posicion.y,posicion.z , direccion.x + direccion.x, posicion.y,direccion.z+direccion.z, 0, 1, 0);
	}
	void CamaraRotaY(float grado){
		Rotar(direccion, grado, Ejes::Y);
	}
	void CamaraRotaX(float grado){
		Rotar(direccion, grado, Ejes::X);

	}
	void CamaraRotaZ(float grado){
		Rotar(direccion, grado, Ejes::Z);
	}
};

class fog{
public:
	bool gp;
	void usefog(){

		if (gp == false)
		{
			glClearColor(.13, .41, .55, 0);
			densidad_niebla = 1.0;
			glFogf(GL_FOG_DENSITY, densidad_niebla + densidad);
			glDisable(GL_FOG);
		}
		if (gp==true)
		{
			glClearColor(.5, .5, .5, 0);
			densidad_niebla = .3;
			glFogf(GL_FOG_DENSITY, densidad_niebla + densidad);
			if (densidad < -.3)
				densidad = -.3;
			if (densidad > .7)
				densidad = .7;
			glEnable(GL_FOG);
		}
	}
private:
	 GLuint  filter;
	 GLuint fogMode[3];
	 GLuint  fogfilter;
	 GLfloat fogColor[4];
	 float densidad;
	fog(GLuint filter, bool gp, float densidad, GLuint fogfilter){
		this->gp = gp;
		this->filter = filter;
		this->fogColor[0] = 0.5f;
		this->fogColor[1] = 0.5f;
		this->fogColor[2] = 0.5f;
		this->fogColor[3] = 1.0f;
		this->densidad = densidad;
	}
	bool getgp()
	{
		return gp;
	}
	fog(){}
	~fog(){}
	friend class OpenGLManager;
	friend int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
};
//-------------------Variables escenario--------------//
Terreno *terrenito;
	void initparticulas(int i){
		par_sys[i].alive = true;
		par_sys[i].life = 1.0;
		par_sys[i].fade = float(rand() % 100) / 1000.0f + 0.003f;

		par_sys[i].xpos = (float)(rand() % 300) + 1;
		par_sys[i].ypos = 100.0;
		par_sys[i].zpos = (float)(rand() % 300) + 1;

		par_sys[i].red = 0.0;
		par_sys[i].green = 0.0;
		par_sys[i].blue = 1.0;

		par_sys[i].vel = velocity;
		par_sys[i].gravity = -0.8;

	}
class OpenGLManager:public Camara,private fog{
public:
		fog *fogTouse;
		HUD *hud[21];
		OpenGLManager(HWND hWnd) {
			posicion = vectores(0, 4, 0);
			//posicion = vectores(-120, 5, -110);
			direccion = vectores(0, 0, -1);
			aumentox = 0; aumentoy = -2; aumentoz = 10;
			aumentoJugadoresx = 0; aumentoJugadoresy = 23; aumentoJugadoresz = -10;
			personajeprincipalvector = vectores(aumentox, aumentoy, aumentoz);
			diferencia = vectores((posicion.x - personajeprincipalvector.x), (posicion.y - personajeprincipalvector.y), (posicion.z - personajeprincipalvector.z));
			distanciafinal = sqrt(pow(diferencia.x, 2) + pow(diferencia.y, 2) + pow(diferencia.z, 2));
			control_densidad = 0;
			glShadeModel(GL_SMOOTH);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_LIGHTING);
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.0f);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_NORMALIZE);
			glEnable(GL_LIGHT0);
			glEnable(GL_COLOR_MATERIAL);
			glEnable(GL_NORMALIZE);
			glFogfv(GL_FOG_COLOR, fogColor);
			glFogf(GL_FOG_DENSITY, densidad_niebla + control_densidad);
			glHint(GL_FOG_HINT, GL_DONT_CARE);
			glFogf(GL_FOG_START, 1.1f);
			glFogf(GL_FOG_END, 200.0f);
			glPopMatrix();
			glDisable(GL_BLEND);
			glEnable(GL_DEPTH_TEST);
			movchainy = 10;
			movchainz = -40;
			//----------------Escenario--------------------------//
			aguita = new Water("Texturas/water.bmp");
			int x, z;
			for (z = 0; z < 21; z++) {
				for (x = 0; x < 21; x++) {
					ground_points[x][z][0] = x - 10.0;
					ground_points[x][z][1] = 0;
					ground_points[x][z][2] = z - 10.0;

					ground_colors[z][x][0] = r; // red value
					ground_colors[z][x][1] = g; // green value
					ground_colors[z][x][2] = b; // blue value
					ground_colors[z][x][3] = 0.0; // acummulation factor
				}
			}

			// Initialize particles
			for (loop = 0; loop < MAX_PARTICLES; loop++) {
				initparticulas(loop);
			}
			nave = new Modelo("modelos/F-35_Lightning_II.obj", "Texturas/textura.bmp");
			enemigo1 = new Modelo("modelos/chainchompcap.obj", "Texturas/t0156_0.bmp");
			pastel = new Modelo("modelos/bowserkite.obj", "Texturas/wing_kpa_alb.bmp");
			banzaibill = new Modelo("modelos/banzaibill.obj", "Texturas/model2.bmp");
			koffing = new Modelo("modelos/koffing.obj", "Texturas/model0.bmp");
			bomb = new Modelo("modelos/bomb.obj", "Texturas/enemy_xx01_BombHei_dif.bmp");
			bombatras = new Modelo("modelos/parteatras.obj","Texturas/enemy_xx01_BombHei_dif.bmp");
			demo1 = LoadTexture("Texuras/Wall.bmp");
			cesped = new Modelo("modelos/bushboard.obj", "Texturas/bushboard_alb.bmp");
			patader = new Modelo("modelos/patader.obj", "Texturas/enemy_xx01_BombHei_dif.bmp");
			pataiz = new Modelo("modelos/patas.obj", "Texturas/enemy_xx01_BombHei_dif.bmp");
			movbomb = 5.0f;
			//tree = new Modelo("modelos/DeadTree21_LOD.obj", "Texturas/tree.bmp");

			for (int i = 0; i <55; i++)
			{
				coin[i] = new Modelo("modelos/coin.obj", "Texturas/coin.bmp");
			}
			textures[0] = LoadTexture("Texturas/miramar_up.bmp");
			textures[1] = LoadTexture("Texturas/miramar_lf.bmp");
			textures[2] = LoadTexture("Texturas/miramar_rt.bmp");
			textures[3] = LoadTexture("Texturas/miramar_ft.bmp");
			textures[4] = LoadTexture("Texturas/miramar_bk.bmp");
			terrenito = new Terreno(hWnd, 400, 400, L"Texturas/heightmap.jpg", L"Texturas/dn.png", L"Texturas/dn.png", L"Texturas/sn_moutain01_alb.png");
			float altura = terrenito->Superficie(30, 16);
			fogTouse = new fog(0, false, 0.0, 0);
			water = new Modelo("modelos/agua.obj", "Texturas/ef_waterline_alb.bmp");
			skyguy = new Modelo("modelos/shyguykart.obj", "Texturas/model171.bmp");
			hud[0] = new HUD(L"Texturas/Item_Box.png", 5, 5, 0, altura + 1, -60);
			hud[1] = new HUD(L"Texturas/Item_Box.png", 5, 5, 90, altura + 1, 16);
			hud[2] = new HUD(L"Texturas/Item_Box.png", 5, 5, 80, altura + 1, -56);
			hud[3] = new HUD(L"Texturas/Item_Box.png", 5, 5, 30, altura + 1, 30);
			hud[4] = new HUD(L"Texturas/Item_Box.png", 5, 5, 100, altura + 1, 100);
			hud[5] = new HUD(L"Texturas/Item_Box.png", 5, 5, 0, altura + 1, 0);
			hud[6] = new HUD(L"Texturas/Item_Box.png", 5, 5, 40, altura + 1, -80);
			hud[7] = new HUD(L"Texturas/Item_Box.png", 5, 5, 80, altura + 1, -50);
			hud[8] = new HUD(L"Texturas/Item_Box.png", 5, 5, -20, altura + 1, 20);
			hud[9] = new HUD(L"Texturas/Item_Box.png", 5, 5, 120, altura + 1, 50);
			hud[10] = new HUD(L"Texturas/Item_Box.png", 5, 5, 100, altura + 1, -66);
			movmx = 7;
			movmy =12;
			movmz = 3;
			posicionMonedas = ( 0, 2, 0 );
			pataizmov = 0.1f;
			patadermov = 0.1f;
	     
	}
	
	
		void Draw(HDC hDC){
			int i, j;
			float x, y, z;
			//------------------Colisiones escenario---------------//
			if (movy < terrenito->Superficie(movxb, movbomb)){
				movy = terrenito->Superficie(movxb, movbomb);
			}
			if (movmy < terrenito->Superficie(movmx, movmz)){
				movmy = terrenito->Superficie(movmx, movmz);
			}
			if (posicion.y < terrenito->Superficie(posicion.x, posicion.z) + 3){
				posicion.y = terrenito->Superficie(posicion.x, posicion.z) + 3;
			}
			if (movbomb >= 170){
				bombali = true;
			}
			if (movbomb <= -170.0){
				bombali = false;
			}
			if (posicion.y >= 200)
			{
				posicion.y = 200;
			}
			if (posicion.z <= -170.0)
			{
				posicion.z = -170.0;
			}
			if (posicion.z >= 170)
			{
				posicion.z = 170;
			}

			if (posicion.x <= -190)
			{
				posicion.x = -190;
			}
			if (posicion.x >= 170)
			{
				posicion.x = 170;
			}
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glFogi(GL_FOG_MODE, GL_LINEAR);

			glLoadIdentity();
			drawPrincipal();

			Actualizacion();
			drawRain();
			GLfloat LightAmb2[] = { 1, 1, 1, 1.0 };
			glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmb2);
			glFogf(GL_FOG_END, 800.0f);
			for (i = -10; i + 1 < 11; i++) {
				// along x - y const
				for (j = -10; j + 1 < 11; j++) {
					glColor3fv(ground_colors[i + 10][j + 10]);
					glVertex3f(ground_points[j + 10][i + 10][0],
						ground_points[j + 10][i + 10][1],
						ground_points[j + 10][i + 10][2] + zoom);
					glColor3fv(ground_colors[i + 10][j + 1 + 10]);
					glVertex3f(ground_points[j + 1 + 10][i + 10][0],
						ground_points[j + 1 + 10][i + 10][1],
						ground_points[j + 1 + 10][i + 10][2] + zoom);
					glColor3fv(ground_colors[i + 1 + 10][j + 1 + 10]);
					glVertex3f(ground_points[j + 1 + 10][i + 1 + 10][0],
						ground_points[j + 1 + 10][i + 1 + 10][1],
						ground_points[j + 1 + 10][i + 1 + 10][2] + zoom);
					glColor3fv(ground_colors[i + 1 + 10][j + 10]);
					glVertex3f(ground_points[j + 10][i + 1 + 10][0],
						ground_points[j + 10][i + 1 + 10][1],
						ground_points[j + 10][i + 1 + 10][2] + zoom);
				}

			}
			glEnd();
			drawRain();
			sky();
			glFogf(GL_FOG_END, 200.0f);
			fogTouse->usefog();
			LightAmb2[0] = 0.2; LightAmb2[1] = 0.2; LightAmb2[2] = 0.2; LightAmb2[3] = 0.0;
			glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmb2);
			GLfloat LightPos[] = { 40.0, 50.0, 10.0, 1.0 };
			glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
			terrenito->Draw();
			drawwater();
			drawaguita();// Reset The Projection Matrix

			LightAmb2[0] = 0.2; LightAmb2[1] = 0.2; LightAmb2[2] = 0.2; LightAmb2[3] = 0.0;
			glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmb2);
			GLfloat LightPos2[] = { 40.0, 50.0, 10.0, 1.0 };
			glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
			vectores null = { 0, -54, 0 };
			if (billCOl(posicion, hud[0]->getPosiciones(), i))
			{
				col = true;
				hud[0]->y = -40.0;
			}
			else if (!billCOl(posicion, hud[0]->getPosiciones(), i)){
				hud[0]->Draw(posicion);
				col = false;
			}
			if (billCOl(posicion, hud[1]->getPosiciones(), i))
			{
				col = true;
				hud[1]->y = -40.0;
			}
			else if (!billCOl(posicion, hud[1]->getPosiciones(), i)){
				hud[1]->Draw(posicion);
				col = false;
			}
			if (billCOl(posicion, hud[2]->getPosiciones(), i))
			{
				col = true;
				hud[2]->y = -40.2;
			}
			else if (!billCOl(posicion, hud[2]->getPosiciones(), i)){
				hud[2]->Draw(posicion);
				col = false;
			}
			if (billCOl(posicion, hud[3]->getPosiciones(), i))
			{
				col = true;
				hud[3]->y = -40.0;
			}
			else if (!billCOl(posicion, hud[3]->getPosiciones(), i)){
				hud[3]->Draw(posicion);
				col = false;
			}
			if (billCOl(posicion, hud[4]->getPosiciones(), i))
			{
				col = true;
				hud[4]->y = -40.0;
			}
			else if (!billCOl(posicion, hud[4]->getPosiciones(), i)){
				hud[4]->Draw(posicion);
				col = false;
			}
			if (billCOl(posicion, hud[5]->getPosiciones(), i))
			{
				col = true;
				hud[5]->y = -40.0;
			}
			else if (!billCOl(posicion, hud[5]->getPosiciones(), i)){
				hud[5]->Draw(posicion);
				col = false;
			}
			if (billCOl(posicion, hud[6]->getPosiciones(), i))
			{
				col = true;
				hud[6]->y = -40.0;
			}
			else if (!billCOl(posicion, hud[6]->getPosiciones(), i)){
				hud[6]->Draw(posicion);
				col = false;
			}
			if (billCOl(posicion, hud[7]->getPosiciones(), i))
			{
				col = true;
				hud[7]->y = -40.0;
			}
			else if (!billCOl(posicion, hud[7]->getPosiciones(), i)){
				hud[7]->Draw(posicion);
				col = false;
			}
			if (billCOl(posicion, hud[8]->getPosiciones(), i))
			{
				col = true;
				hud[8]->y = -40.0;
			}
			else if (!billCOl(posicion, hud[8]->getPosiciones(), i)){
				hud[8]->Draw(posicion);
				col = false;
			}
			if (billCOl(posicion, hud[9]->getPosiciones(), i))
			{
				col = true;
				hud[9]->y = -40.0;
			}
			else if (!billCOl(posicion, hud[9]->getPosiciones(), i)){
				hud[9]->Draw(posicion);
				col = false;
			}
			if (billCOl(posicion, hud[10]->getPosiciones(), i))
			{
				col = true;
				hud[10]->y = -40.0;
			}
			else if (!billCOl(posicion, hud[10]->getPosiciones(), i)){
				hud[10]->Draw(posicion);
				col = false;
			}
			if (pataim){
				pataizmov += 0.3f;
				patadermov -= 0.3f;
			}
			else
			{
				pataizmov -= 0.3f;
				patadermov += 0.3f;
			}
			if (pataizmov >= 5.0f){
				pataim = false;

			}
			else if (pataizmov <= -5.0f){
				pataim = true;

			}
			if (movmx >= -50){
				movmx -= 0.3;
			}
			if (movmx <= 50){
				movmx += 0.3;
			}
			if (bombali){
				movbomb -= 0.3;
				movy = 6.0f;
			}
			else{
				movbomb += 0.3;
			}
			drawcesped();
			drawcake();
			enemigo();
			drawskyguy();
			drawenemigo4();
			drawcesped2();
			drawenemigo3();
			drawenemigo5();
			drawenemigo6();
			aguita->Update();
			drawbomb();
			drawpatitas();
			drawbombatras();
			drawpatitader();
			if (moneda(posicion, 40, 2, 5, 1) && ja == 0){
				ja[0] = 1;

				drawcoindes(1, 40, 20, 5);
				coins++;

			}
			else if (!moneda(posicion, 40, 2, 5, 1)){
				if (ja[0] == 0){
					drawcoindes(1, 40, 2, 5);
				}
				else
				{
				}
			}

			if (moneda(posicion, 2, 2, -50, 2) && ja == 0){
				ja[1] = 1;
				coins++;
				drawcoindes(2, 2, 10, -50);

			}
			else if (!moneda(posicion, 40, 2, 5, 1) && ja == 0){
				if (ja[1] == 0){
					drawcoin(2, 2, 2, -50);
				}
				else
				{

				}
			}
			if (moneda(posicion, 50, 2, -100, 3) && ja == 0){
				ja[2] = 1;
				drawcoindes(3, 50, 10, -100);
				coins++;

			}
			else if (!moneda(posicion, 50, 2, -100, 3)){
				if (ja[2] == 0){
					drawcoin(3, 50, 2, -100);
				}
				else
				{

				}
			}
			if (moneda(posicion, -20, 2, 60, 4) && ja == 0){
				ja[3] = 1;
				coins++;
				drawcoindes(4, -20, 10, 60);

			}
			else if (!moneda(posicion, -20, 2, 60, 4)){
				if (ja[3] == 0){
					drawcoin(4, -20, 2, 60);
				}
				else
				{

				}
			}
			if (moneda(posicion, 95, 2, 40, 5) && ja == 0){
				ja[4] = 1;
				coins++;
				drawcoindes(5, 95, 10, 40);

			}
			else if (!moneda(posicion, 95, 2, 40, 5)){
				if (ja[4] == 0){
					drawcoin(5, 95, 2, 40);
				}
				else
				{

				}
			}
			if (moneda(posicion, -130, 2, -10, 6) && ja == 0){
				ja[5] = 1;
				drawcoindes(6, -130, 10, -10);
				coins++;

			}
			else if (!moneda(posicion, -130, 2, -10, 6)){
				if (ja[5] == 0){
					drawcoindes(6, -130, 2, -10);
				}
				else
				{

				}
			}
			if (moneda(posicion, -89, 2, 110, 7) && ja == 0){
				ja[6] = 1;
				coins++;
				drawcoindes(6, -130, 10, -10);

			}
			else if (!moneda(posicion, -89, 2, 110, 7)){
				if (ja[6] == 0){
					drawcoin(6, -130, 2, -10);
				}
				else
				{

				}
			}
			if (moneda(posicion, -89, 2, 110, 7) && ja == 0){
				ja[7] = 1;
				coins++;
				drawcoindes(7, -89, 10, 110);

			}
			else if (!moneda(posicion, -89, 2, 110, 7)){
				if (ja[7] == 0){
					drawcoin(7, -89, 2, 110);
				}
				else
				{

				}
			}
			if (moneda(posicion, 109, 2, -200, 8) && ja == 0){
				ja[8] = 1;
				coins++;
				drawcoindes(8, 109, 10, -200);
			}
			else if (!moneda(posicion, 109, 2, -200, 8) && ja == 0){
				if (ja[8] == 0){
					drawcoin(8, 109, 2, -200);
				}
				else
				{

				}
			}
			if (moneda(posicion, -140, 2, 15, 9) && ja == 0){
				ja[9] = 1;
				coins++;
				drawcoindes(9, -140, 10, 15);
			}
			else if (!moneda(posicion, -140, 2, 15, 9)){
				if (ja[9] == 0){
					drawcoin(9, -140, 2, 15);
				}
				else
				{

				}
			}
			if (moneda(posicion, 30, 2, 20, 10) && ja == 0){
				ja[10] = 1;
				drawcoindes(10, 30, 10, 20);
				coins++;

			}
			else if (!moneda(posicion, 30, 2, 20, 10) && ja == 0){
				if (ja[10] == 0){
					drawcoin(10, 30, 2, 20);
				}
				else
				{

				}
			}
			if (moneda(posicion, -9, 2, 100, 11) && ja == 0){
				ja[11] = 1;
				coins++;
				drawcoindes(11, -9, 10, 100);
			}
			else if (!moneda(posicion, -9, 2, 100, 11)){
				if (ja[11] == 0){
					drawcoin(11, -9, 2, 100);
				}
				else
				{

				}
			}
			if (moneda(posicion, 106, 2, -209, 12) && ja == 0){
				ja[12] = 1;
				drawcoindes(12, 106, 10, -209);
				coins++;

			}
			else if (!moneda(posicion, 106, 2, -209, 12)){
				if (ja[12] == 0){
					drawcoin(12, 106, 2, -209);
				}
				else
				{

				}
			}
			if (moneda(posicion, 99, 2, -70, 13) && ja == 0){
				ja[13] = 1;
				coins++;
				drawcoindes(13, 99, 10, -70);
			}
			else if (!moneda(posicion, 99, 2, -70, 13)){
				if (ja[13] == 0){
					drawcoin(13, 99, 2, -70);
				}
				else
				{

				}
			}
			if (moneda(posicion, 177, 2, -55, 14) && ja == 0){
				ja[14] = 1;
				drawcoindes(14, 177, 10, -55);
				coins++;

			}
			else if (!moneda(posicion, 177, 2, -55, 14)){
				if (ja[14] == 0){
					drawcoin(14, 177, 2, -55);
				}
				else
				{

				}
			}
			if (moneda(posicion, -1, 2, -150, 15) && ja == 0){
				ja[15] = 1;
				drawcoindes(15, -1, 10, -150);
				coins++;

			}
			else if (!moneda(posicion, -1, 2, -150, 15)){
				if (ja[15] == 0){
					drawcoin(15, -1, 2, -150);
				}
				else
				{


				}
			}
			if (moneda(posicion, -60, 2, 9, 16) && ja == 0){
				ja[16] = 1;
				drawcoindes(16, -60, 10, 9);
				coins++;

			}
			else if (!moneda(posicion, -60, 2, 9, 16)){
				if (ja[16] == 0){
					drawcoin(16, -60, 2, 9);
				}
				else
				{

				}
			}
			if (moneda(posicion, 88, 2, 88, 17) && ja == 0
				){
				ja[17] = 1;
				drawcoindes(17, 88, 10, 88);
				coins++;

			}
			else if (!moneda(posicion, 88, 2, 88, 17)
				){
				if (ja[17] == 0){
					drawcoin(17, 88, 2, 88);
				}
				else
				{

				}
			}
			if (moneda(posicion, -88, 2, -88, 18) && ja == 0){

				ja[18] = 1;
				coins++;
				drawcoindes(18, -88, 10, -88);
			}
			else if (!moneda(posicion, -88, 2, -88, 18)
				){
				if (ja[18] == 0){
					drawcoin(18, -88, 2, -88);
				}
				else
				{

				}
			}
			if (moneda(posicion, -102, 2, 98, 19) && ja == 0
				){
				ja[19] = 1;
				drawcoindes(19, -102, 10, 98);
				coins++;

			}
			else if (!moneda(posicion, -102, 2, 98, 19)
				){
				if (ja[19] == 0){
					drawcoin(19, -102, 2, 98);
				}
				else
				{

				}
			}
			if (moneda(posicion, -48, 2, 37, 20) && ja == 0
				){
				ja[20] = 1;
				drawcoindes(20, -48, 10, 37);
				coins++;

			}
			else if (!moneda(posicion, -48, 2, 37, 20) && ja == 0
				){
				if (ja[20] == 0){
					drawcoin(20, -48, 2, 37);
				}
				else
				{

				}
			}
			if (bSphereTest(posicion, 0, movky, 100)){
				for (i = movky; i < 100; i++){
					movky += 0.3f;
					drawenemigo6();

				}
				//movky = 500;
			}

			glPushMatrix();
			glPopMatrix();
			SwapBuffers(hDC);
			if (aumentoJugadoresz <= -20 || aumentoJugadoresz >= 20){

				aumentoJugadoresz = aumentoJugadoresz;
			}
			if (aumentoJugadoresz >= 100){
				aumentoJugadoresz -= 0.6;
			}
			if (aumentoJugadoresz <= -100)
			{
				aumentoJugadoresz += 0.6;
			}
			grados += 3;
			colisionBala();
			bSphereTest(posicion, -20, 0, 50);
			coinR += 0.9f;
			if (movkyb)
			{
				movky += 0.3f;
			}
			else{
				movky -= 0.3f;
			}
			if (movky <= 1.0f){
				movkyb = true;
			}
			if (movky >= 8.0f){
				movkyb = false;
			}
			movmx += 0.2;
			if (movchainy <= 5.0f){
				limitchainy = true;
			}
			if (movchainz >= 13.0f){
				limitchainz = false;
			}
			if (limitchainy){
				movchainy += 0.2f;
			}
			else{
				movchainy -= 0.2f;
			}
			if (movchainz >= 30.0f)
			{
				limitchainz = true;
			}
			if (movchainz <= -20.f)
			{
				limitchainz = false;
			}
			if (limitchainz){
				movchainz -= 0.2f;
			}
			else{
				movchainz += 0.2f;
			}
	}

	~OpenGLManager(){
	    delete cielo;
		delete nave;
		delete terrenito;
		delete water;
		delete mushroom;
		delete jugador2;
		delete jugador3;
		delete jugador4;
		delete bomb;
		delete bombatras;
		delete patader;
		delete pataiz;
	}
	void drawPrincipal(){
		glPushMatrix();
		nave->RotarY(180);
		nave->Trasladar(aumentox, aumentoy,aumentoz);
		nave->Escalar(2.0, 2.0, 2.0);
		nave->Dibujar();
		glPopMatrix();
	}

	void drawJugador2(){
		glPushMatrix();
		jugador2->Trasladar(aumentoJugadoresx, 5, aumentoJugadoresz);
		jugador2->RotarY(180);
		jugador2->Dibujar();
		glPopMatrix();
	}

	void drawJugador3(){
		glPushMatrix();
		jugador3->RotarY(180);
		jugador3->Trasladar(0,5, -10);
		jugador3->Escalar(1.0, 1.0, 1.0);
		jugador3->Dibujar();
		glPopMatrix();
	}

	void drawJugador4(){

		glPushMatrix();
		jugador4->RotarY(180);
		jugador4->Trasladar(0,5,-10);

		//jugador4->rotarX(aumentoJugadoresz);
		jugador4->Dibujar();
		glPopMatrix();
	}

	void enemigo(){
		glPushMatrix();
		enemigo1->RotarY(360);
		enemigo1->Trasladar(-300,movchainy,movchainz);
		enemigo1->Escalar(0.5,0.5,0.5);
		enemigo1->Dibujar();
		glPopMatrix();
	}

	void drawenemigo4(){
		glPushMatrix();
		enemigo1->RotarY(180);
		enemigo1->Trasladar(100, movchainy, movchainz-40);
		enemigo1->Escalar(0.5,0.5, 0.5);
		enemigo1->Dibujar();
		glPopMatrix();
	}

	void drawskyguy(){
		glPushMatrix();
		skyguy->RotarY(360);
		skyguy->Trasladar(100,0.5,100);
		skyguy->Escalar(0.5,0.5,0.5);
		skyguy->Dibujar();
		glPopMatrix();
	}
	void drawenemigo3(){
		glPushMatrix();
		skyguy->RotarY(180);
		skyguy->Trasladar(-100,0.5, 134);
		skyguy->Escalar(0.5, 0.5, 0.5);
		skyguy->Dibujar();
		glPopMatrix();
	}
	void drawcoindes(int i, float x, float y, float z){
		glPushMatrix();
		coin[i]->RotarY(180);
		coin[i]->Trasladar(x, 300, z);
		coin[i]->Escalar(0.6, 0.6, 0.6);
		coin[i]->Trasladar(x, y, z);
		coin[i]->Dibujar();
		glPopMatrix();
	}
	void drawenemigo5(){
		glPushMatrix();
		banzaibill->RotarY(180);
		banzaibill->Trasladar(-150,15,movbomb);
		banzaibill->Escalar(0.2, 0.2, 0.2);
		banzaibill->rotarZ(coinR);
		banzaibill->Dibujar();

		glPopMatrix();
	}
	void drawenemigo6(){
		glPushMatrix();
		koffing->RotarY(180);
		koffing->Trasladar(0,movky,100);
		koffing->Escalar(0.2, 0.2, 0.2);
		koffing->Dibujar();
		glPopMatrix();
	}
	void drawcake(){
		glPushMatrix();
		pastel->RotarY(180);
		pastel->Trasladar(0,50, -20);
		pastel->Escalar(0.2,0.2,0.2);
		pastel->Dibujar();
		glPopMatrix();
	}
	void drawwater(){
			glPushMatrix();
			glDisable(GL_DEPTH_TEST);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			glEnable(GL_BLEND);
			water->Trasladar(-1524,-3524,-3264);
			water->Escalar(1.5,1.5,1.5);
			water->Dibujar();
			glPopMatrix();
			glDisable(GL_BLEND);
			glEnable(GL_DEPTH_TEST);
	}

		void drawcesped(){
			glPushMatrix();
			cesped->RotarY(180);
			cesped->Trasladar(-20,0,-20);
			cesped->Escalar(0.2, 0.2, 0.2);
			cesped->Dibujar();
			glPopMatrix();
		}
		void drawbomb(){
			glPushMatrix();
			bomb->RotarY(180);
			bomb->Trasladar(movxb,movy,movbomb);
			Escalar(.1, .1, .1);
			bomb->Dibujar();
			glPopMatrix();
		}

		void drawcesped2(){
			glPushMatrix();
			cesped->RotarY(360);
			cesped->Trasladar(80,2,-10);
			cesped->Escalar(0.2, 0.2, 0.2);
			cesped->Dibujar();
			glPopMatrix();
		}
		void moneadadesaparece(int i ){
			glPushMatrix();
			glPopMatrix();
		}


		void drawcoin(int i,float x,float y, float z){
				glPushMatrix();
				coin[i]->RotarY(0);
				coin[i]->Trasladar(x, y,z);
				coin[i]->Escalar(0.2, 0.2, 0.2);
				coin[i]->rotarY(coinR);
				coin[i]->Dibujar();
				glPopMatrix();
			}

	   void sky(){
		glPushMatrix();
		Trasladar(-500, 100.0,-500);
		cielo->CreateSkyBox(textures,500, 0, 500, 400, 200, 400);
		glPopMatrix();
	   }

	   BOOL billCOl(vectores obj1, vectores obj2, int i)
	   {
		   int r0sqr = 6 * 6;
		   int r1sqr = 4 * 4;

		   int distX = posicion.x - obj2.x;
		   int distY = posicion.y - obj2.y;
		   int distZ = posicion.z  - obj2.z;

		   // Since we already need to square these, we won't need to take the absolute value
		   // to accurately compare them to the radii
		   distX = distX * distX;
		   distY = distY * distY;
		   distZ = distZ * distZ;
		   float sqrDist = (distX + distY + distZ);
		   float radio = r0sqr + r1sqr;
		   if (radio >= sqrDist){
			   
			   
			   return true;
		   }
		   return false;
	   }
	   void drawbombatras(){
		   glPushMatrix();
		   bombatras->RotarY(180);
		   bombatras->Trasladar(movxb,movy+3, movbomb-3);
		   bombatras->Escalar(.1, .1, .1);
		   bombatras->rotarZ(coinR);
		   bombatras->Dibujar();
		   glPopMatrix();
	   }
	   void drawpatitas(){
		   glPushMatrix();
		   patader->RotarY(180);
		   patader->Trasladar(movxb-1,movy,movbomb);
		   patader->Escalar(.1, .1, .1);
		   patader->rotarX(pataizmov);
		   patader->Dibujar();
		   glPopMatrix();
	   }
	   void drawpatitader(){
		   glPushMatrix();
		   patader->RotarY(180);
		   patader->Trasladar(movxb+1,movy,movbomb);
		   patader->Escalar(.1, .1, .1);
		   patader->rotarX(patadermov);
		   patader->Dibujar();
		   glPopMatrix();
	   }
	   BOOL bSphereTest(vectores obj1,float x, float y, float z)
	   {
		   int r0sqr = 8 * 8;
		   int r1sqr = 10*10;

		   int distX = (posicion.x) - x;
		   int distY = (posicion.y) - y;
		   int distZ = (aumentox -posicion.z) - z;

		   // Since we already need to square these, we won't need to take the absolute value
		   // to accurately compare them to the radii
		   distX = distX * distX;
		   distY = distY * distY;
		   distZ = distZ * distZ;
		   float sqrDist = (distX + distY + distZ);
		   float radio = r0sqr + r1sqr;
		   if (radio > sqrDist){
			   return true;
		   }
		   return false;
	   }

	   bool moneda(vectores obj1, float x, float y, float z,int i )
	   {
		   int r0sqr =10*10;
		   int r1sqr = 8*8;

		   int distX = (aumentox +posicion.x) - x;
		   int distY = (aumentoy + posicion.y) - y;
		   int distZ = (aumentoz + posicion.z) - z;
		   distX = distX * distX;
		   distY = distY * distY;
		   distZ = distZ * distZ;
		   float sqrDist = (distX + distY + distZ);
		   float radio = r0sqr + r1sqr;
		   if (radio > sqrDist){
			   colisioncoin[i] = true;
			   return true;
		   }
		   colisioncoin[i] = false;
		   return false;
	   }

	   void colisionBala(){
		   float radColCam = 1;
		   float radColGem = 1;
		   float distanciaJ1,distanciaPrincipal,distanciaJ2,distanciaBala,distanciaJ3;
		   distanciaJ1 = sqrt((pow(aumentoJugadoresx - aumentoJugadoresx, 2)) + (pow(10-aumentoJugadoresy, 2)) + (pow(aumentoJugadoresz - aumentoJugadoresz, 2)));
		   distanciaPrincipal = sqrt((pow(0 - posicion.x, 2)) + (pow(10 - posicion.y, 2)) + (pow(-10 - aumentoz, 2)));
		   if (distanciaJ1 <= (radColCam + radColGem)){
			   aumentoJugadoresx +=2;
			   aumentoJugadoresz += 2;
			   aumentoJugadoresy += 2;
		   }
		   if (distanciaPrincipal <= (radColCam + radColGem)){
			   posicion.y = 23;
		   }

	   }
	 /*  void drawCasa(){
		   glPushMatrix();
		   casa->RotarY(180);
		   casa->Trasladar(-130,3, 200);
		   casa->Escalar(1.0, 1.0, 1.0);
		   casa->Dibujar();
		   glPopMatrix();
	   }*/
	   // For Rain
	   void drawRain() {
		   float x, y, z;

		   for (loop = 0; loop < MAX_PARTICLES; loop = loop + 2) {
			   if (par_sys[loop].alive == true) {
				   x = par_sys[loop].xpos;
				   y = par_sys[loop].ypos;
				   z = par_sys[loop].zpos + 10;
				   
				   // Draw particles
				   glColor3f(0.5, 0.5, 1.0);
				   glBegin(GL_LINES);
				   glVertex3f(x, y+0.5, z);
				   glVertex3f(x, y, z);
				   glEnd();

				   // Update values
				   //Move
				   // Adjust slowdown for speed!
				   par_sys[loop].ypos += par_sys[loop].vel / (slowdown * 1000);
				   par_sys[loop].vel += par_sys[loop].gravity;
				   // Decay
				   par_sys[loop].life -= par_sys[loop].fade;

				   if (par_sys[loop].ypos <= -10) {
					   par_sys[loop].life = -1.0;
				   }
				   //Revive
				   if (par_sys[loop].life < 0.0) {
					   initparticulas(loop);
				   }
			   }
		   }
	   }
	  void drawaguita(){
		  glPushMatrix();
		  aguita->trasladar(100, 1,100);
		  aguita->escalar(1.0, 1.0, 1.0);
		  aguita->Draw();
		  glPopMatrix();
	   }

};

#endif 