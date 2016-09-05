#ifndef imageness
#define imageness

#include <gdiplus.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <exception>

using namespace Gdiplus;

class Imagenes{
public:

	HWND hWnd;

	Imagenes()
	{
	}

	~Imagenes()
	{
	}
private:
	unsigned char *dir_imagen, *primero;
	unsigned int ancho;
	unsigned int alto;

public:
	void Carga(WCHAR nombre[])
	{
	   GdiplusStartupInput gdiplusStartupInput;
	   ULONG_PTR     gdiplusToken;
       GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	   
	   Bitmap* bitmap = new Bitmap(nombre);
	   BitmapData* bitmapData = new BitmapData;

	   ancho = bitmap->GetWidth();
	   alto = bitmap->GetHeight();

	   Rect rect(0, 0, ancho, alto);

	   bitmap->LockBits(&rect, ImageLockModeRead, PixelFormat32bppARGB, bitmapData);

	   unsigned char* pixels = (unsigned char*)bitmapData->Scan0;

	   int tamaño;
	   tamaño = ancho*alto*4;
	   try
	   {
		   dir_imagen = new unsigned char [tamaño]; //[tamaño*1000000]; ponganle esto como prueba
		   primero=dir_imagen;
	   }
	   catch(std::exception& e)
	   {
		   int msgboxID = MessageBoxW(hWnd,L"Insuficiente memoria para contener la textura",
			   (LPCWSTR)L"Clase Imagenes", MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2);
		   switch (msgboxID)
			{
				case IDCANCEL:
					exit(0);
					break;
				case IDTRYAGAIN:
					try{
					dir_imagen = new unsigned char [tamaño];
					primero=dir_imagen;
					}
					catch(std::bad_alloc &e)
					{
					}
					break;
				case IDCONTINUE:
					dir_imagen=0;
					primero=0;
					break;
			}
		   
	   }

	   for(unsigned int i=0;i<(alto*ancho*4);i+=4)
	   {
			dir_imagen[i+2] = pixels[i];
			dir_imagen[i+1] = pixels[i+1];
			dir_imagen[i] = pixels[i+2];
			dir_imagen[i+3] = pixels[i+3];
	   }

	   bitmap->UnlockBits(bitmapData);

	   delete bitmapData;
	   delete bitmap;
	  
	   GdiplusShutdown(gdiplusToken);
	}

	void Descarga()
	{
		delete [] dir_imagen;
	}

     unsigned char *Dir_Imagen()
	{
		return primero;
	}

	unsigned int Ancho()
	{
		return ancho;
	}

	unsigned int Alto()
	{
		return alto;
	}
};
#endif