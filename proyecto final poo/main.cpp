/////////////////////////////////////////////////////////////////////////
//Programa tutorial hecho por Rafael Rosas para los impresionantes LMADs
//en la busqueda de la clase mundial en el desarrollo de programadores
//de alto poder logico. 
//Version 3. 3 de Marzo de 2013
//
//Esta version solo muestra como se puede crear un programa medio
//que explica parametros del win32 para crear una ventana
////////////////////////////////////////////////////////////////////////

// es la cabecera basica para un programa de windows
#include <windows.h>
#include <windowsx.h>
#include "glew.h"
#include <gl\GLU.h>
#include <gl\GL.h>
BOOL teclas[256];
#pragma comment (lib, "glew32.lib") 
//Creamos una clase que administre por separado al OpenGL, fuera del loop de windows
#include "AdminGL.h"

#define Timer1 100
LRESULT CALLBACK WindowProc(HWND hWnd, 	UINT message, WPARAM wParam, LPARAM lParam);
void SetUpPixelFormat(HDC hDC);

//debemos declarar una variable global que maneje el acceso al dispositivo grafico
HDC gHDC;
//Declaramos al puntero del objeto 
OpenGLManager *OGLobj;
bool renderiza=false;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,  LPSTR lpCmdLine, int nCmdShow)
{  	   
	HWND hWnd;   
	
	WNDCLASSEX wc;    
	
	ZeroMemory(&wc, sizeof(WNDCLASSEX));    
	wc.cbSize = sizeof(WNDCLASSEX);  
	wc.style = CS_HREDRAW | CS_VREDRAW; 	
	wc.lpfnWndProc = WindowProc; 	
	wc.hInstance = hInstance;   	
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 	
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;	
	wc.lpszClassName = "EjemploLMAD"; 	
	RegisterClassEx(&wc);     
	RECT wr = {0, 0, 800, 600};    
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    
	fog *nieblausada = NULL;
	hWnd = CreateWindowEx(NULL, "EjemploLMAD", "Programa de win32 tutorial",             
		WS_OVERLAPPEDWINDOW,                            
		100,                     
		100,                     
		wr.right - wr.left,                        
		wr.bottom - wr.top,                   
		NULL,                     
		NULL,                
		hInstance,                        
		NULL);   	
	   
	ShowWindow(hWnd, nCmdShow);  
	
	//Creamos al objeto y se lo pasamos al puntero
	OGLobj = new OpenGLManager(hWnd);
	float densidad = 0.004;
	bool encendido = false;
	SetTimer(hWnd,Timer1,30,NULL);

	float theta = 0.0f;
	PlaySound("Sonido/08-vanilla-lake.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP | SND_NOSTOP);
	MSG msg = {0};      
	while(TRUE)   
	{      		
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))       
		{			    
			TranslateMessage(&msg); 		   
			DispatchMessage(&msg);           
			     
			if(msg.message == WM_QUIT)              
				break;        
		}        
		else       
		{
			bool velocidad = false;
			int t;
			if (renderiza)
			{ 
				
				if (GetKeyState('O') & 8000)
				{
					encendido = true;
					OGLobj->fogTouse = new fog(0, true, densidad += 0.001, 0);
				}
				if (GetKeyState('R') & 8000)
				{
					if (!activoRain){
						activoRain = true;
					}
					else{
						activoRain = false;
					}
				}
				if (GetKeyState('F') & 8000)
				{
					
					if (densidad<= 0.001)
					{
						densidad = 0.000;
						encendido = false;
						OGLobj->fogTouse = new fog(0, encendido, densidad, 0);
					}
					else{

						densidad -= 0.001;
						OGLobj->fogTouse = new fog(0, true,densidad, 0);
						
					}
				}
				if (GetKeyState('P') & 8000)
				{
					OGLobj->aumentoz =0;
					OGLobj->aumentoy = -1.5;
				}
				if (GetKeyState('T') & 8000)
				{
					OGLobj->aumentoz =10;

				}
				if (GetKeyState('W') & 8000)
				{
					if (velocidad){
						OGLobj->Traslaciondecamara(2);
						velocidad = false;
					}
					else{
						OGLobj->Traslaciondecamara(1);
					}
				}
					
				if (GetKeyState('S') & 8000)
				{
					if (velocidad){
						OGLobj->Traslaciondecamara(-2);
						velocidad = false;
					}
					else{
						OGLobj->Traslaciondecamara(-1);
					}
				}
				if (GetKeyState('D') & 8000)
				{
				   OGLobj->CamaraRotaY(1);
				}
					
				if (GetKeyState('A') & 8000)
				{
					OGLobj->CamaraRotaY(-1);
				}
					
				if (GetKeyState('N') & 8000)
				{
					OGLobj->CamaraRotaX(1);
				}
				if (GetKeyState('B') & 8000)
				{
					OGLobj->CamaraRotaX(-1);
				}

				if (GetKeyState('Z') & 8000){
					OGLobj->Dispara();
				}
				OGLobj->Draw(gHDC);    
				renderiza = false;
				if (GetKeyState('T') & 8000 && col){
					velocidad = true;

				}
			}
			
		} 
	}    
	
	return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{   
	static HGLRC hRC;
	static HDC hDC;
	int ancho, alto;
	 
	switch(message)    
	{    
		//este case se ejecuta cuando se crea la ventana, aqui asociamos al 
		//opengl con el dispositivo
	case WM_CREATE:
		hDC=GetDC(hWnd);
		gHDC=hDC;
		SetUpPixelFormat(hDC);
		hRC=wglCreateContext(hDC);
		wglMakeCurrent(hDC,hRC);
		break;
	case WM_COMMAND:
		{
		}
	case WM_TIMER:
		renderiza=true;
		break;
	case WM_DESTROY:           
		{  
			KillTimer(hWnd,Timer1);
			//en caos de salir desocpuar los recursos del opengl
			wglMakeCurrent(hDC,NULL);
			wglDeleteContext(hRC);
			PostQuitMessage(0);  
			return 0;            
		} break;   

	case WM_SIZE:
		{
			//esta opcion del switch se ejecuta una sola vez al arrancar y si se
			//afecta el tamaño de la misma se dispara de nuevo
			alto = HIWORD(lParam);
			ancho= LOWORD(lParam);
			if (alto==0)
				alto=1;
			glViewport(0,0,ancho,alto);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(45.0f, (GLfloat)ancho/(GLfloat)alto,0.5f,1000.0f);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		}
		break;
	} 

	return DefWindowProc (hWnd, message, wParam, lParam);
}

void SetUpPixelFormat(HDC hDC)
{
	int PixForm;

	static PIXELFORMATDESCRIPTOR pixfordes = {
		sizeof(PIXELFORMATDESCRIPTOR), //tamaño de la estructura
		1, //numero de version
		PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER, //soporta la ventana, el opengl y manejara doble buffer
		PFD_TYPE_RGBA, //formato de 32 bits rgba
		32, //tamaño del color en 32 bits
		0,0,0,0,0,0, //bits de color, no se usan
		0, //no hay buffer para el alfa
		0, //ignore el bit de corrimiento
		0, //no hay buffer de acumulacion
		0,0,0,0, //no hay bits de acumulacion
		16, //tamaño del flotante para el buffer z
		0, //no hay buffers de stencil
		0, //no hay buffers auxiliares
		PFD_MAIN_PLANE, //plano principal para dibujo
		0, //reservado
		0,0,0 //mascaras de capas ignoradas
	};

	PixForm=ChoosePixelFormat(hDC, &pixfordes);
	SetPixelFormat(hDC, PixForm, &pixfordes);
}