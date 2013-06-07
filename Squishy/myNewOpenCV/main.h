#ifndef _MAIN_H
#define _MAIN_H


#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#include <windows.h>					// Header File For Windows
#include <gl\gl.h>						// Header File For The OpenGL32 Library
#include <gl\glu.h>						// Header File For The GLU32 Library

#include <math.h>


#define CAMERASPEED	0.05f				// The Camera Speed

struct tVector3	// Extended 3D Vector Struct
{			
	tVector3() {} // Struct Constructor
	tVector3 (float new_x, float new_y, float new_z) // Init Constructor	 
	{ x = new_x; y = new_y; z = new_z; }
	// overload + operator
	tVector3 operator+(tVector3 vVector) {return tVector3(vVector.x+x, vVector.y+y, vVector.z+z);}
	// overload - operator
	tVector3 operator-(tVector3 vVector) {return tVector3(x-vVector.x, y-vVector.y, z-vVector.z);}
	// overload * operator
	tVector3 operator*(float number)	 {return tVector3(x*number, y*number, z*number);}
	// overload / operator
	tVector3 operator/(float number)	 {return tVector3(x/number, y/number, z/number);}
	
	float x, y, z;						// 3D vector coordinates
};

class CCamera 
{
	public:
		tVector3 mPos;							
		tVector3 mView;							
		tVector3 mUp;				

		void Strafe_Camera(float speed);

		void Rotate_Position(float speed);
		void Move_Camera(float speed);
		void Mouse_Move(int wndWidth, int wndHeight);
		void Rotate_View(float speed);
		void Position_Camera(float pos_x,  float pos_y,  float pos_z,
							 float view_x, float view_y, float view_z,
							 float up_x,   float up_y,   float up_z);
};

extern	HDC			hDC;				// Device context
extern	HGLRC		hRC;				// Permanent rendering context
extern	HWND		hWnd;				// Holds our window handle
extern	HINSTANCE	hInstance;			// Holds the instance of the application

void Keyboard_Input();
void Draw_Grid();

#endif