#include <GL/glut.h>
#include <GL/GL.h>
#include<opencv\cv.h>
#include<opencv\highgui.h>
//#include<opencv\b>
#include <windows.h>
#include "math.h"
#include "stb_image.h"
#include <mmsystem.h>
#include <process.h>
#include "StartScreen.h"


int main(int argc, char **argv) 
{
	new StartScreen(argc, argv);
        return 1;
}