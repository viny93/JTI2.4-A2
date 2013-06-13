#include <GL/glut.h>
#include <GL/GL.h>
#include<opencv\cv.h>
#include<opencv\highgui.h>
#include<BlobResult.h>
#include <windows.h>
#include "math.h"
#include "main.h"
#include "Player.h"
#include "World.h"
#include "JellyFish.h"
#include "stb_image.h"
#include <mmsystem.h>
#include <process.h>     

float red=1.0f, blue=1.0f, green=1.0f;
float lx=0.0f,lz=-1.0f;
float x=0.0f,z=2.5f;

//light variables
float light_diffuse[] = {1.0, 1.0, 1.0, 1.0}; 
GLfloat light_position[] = { 0, 10, 0, 1.0 };
static float amb[] =  {0.4, 0.4, 0.4, 0.0};
static float dif[] =  {1.0, 1.0, 1.0, 0.0};

float FogCol[3]={0.0f,0.0f,0.0f};
 
static std::vector<RenderObject*> renderObjects;

GLuint introTexture;
int gamestate = 1;
LPCSTR soundToPlay;
CCamera tl;

void playBackground(void *arg)
{
	PlaySound(soundToPlay, NULL, SND_LOOP);
}

void startSound(LPCSTR pszSound, int soundLenght)
{
	soundToPlay = pszSound;
	_beginthread(playBackground, 0, (void*)12 );
}

cv::Mat texturizeBackground(int cam)
{
	cv::VideoCapture cap(cam);
	cv::Mat save_img;
	cv::Mat biggerImage;
	cv::Size size(1024, 512);

	cap >> save_img;
	cv::resize(save_img, biggerImage, size, 0, 0, 1);

	if(biggerImage.empty())
	{
		std::cerr << "Something is wrong with the webcam, could not get frame." << std::endl;
	}
	imwrite("background.png", biggerImage); 

	return biggerImage;
}

void renderScene(void) 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);

	if(gamestate == 1) //launch menu
	{
		gluLookAt(  x, 1.0f, z,
			x+lx, 1.0f,  z+lz,
			0.0f, 1.0f,  0.0f);
		startSound("C:/kirby.wav", 100);
		glTranslatef(1.0f, 2.0f, 0.0f);
		gluLookAt(  x, 1.0f, z,
			x+lx, 1.0f,  z+lz,
			0.0f, 1.0f,  0.0f);

		glBindTexture( GL_TEXTURE_2D, introTexture );

		glBegin( GL_QUADS );

		glTexCoord2f(0, 1);
		glVertex2f(-10,-5.0);
		glTexCoord2f(1, 1);
		glVertex2f(10,-5.0);
		glTexCoord2f(1, 0);
		glVertex2f(10.0, 5.0);
		glTexCoord2f(0, 0);
		glVertex2f(-10.0, 5.0);

		glEnd();
	}

	else //Render game
	{
		for(int i = 0; i < renderObjects.size(); i++)
		{
			renderObjects[i]->Render();
		}
	}
	glutSwapBuffers();
}

//Author: Zack
//runs the update method in all renderobjects
//also deletes objects that are no longer alive (alive = false, can be invoked with Kill())
void updateAll(void) 
{	
	for(int i = 0; i < renderObjects.size(); i++)
	{
		renderObjects[i]->Update();
		if(!renderObjects[i]->isAlive())
		{
			delete renderObjects[i];
			renderObjects.erase(renderObjects.begin() + i);	
		}
	}
	renderScene();
}

void changeSize(int w, int h) 
{
	if(h == 0)
		h = 1;
	float ratio = 1.0* w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(90,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
}

void processNormalKeys(unsigned char key, int x, int y) 
{
	if(gamestate == 1)
	{
		switch (key) {
		case 32 :
			gamestate = 0;
			break;
		}
	}
	else
	{
			if (key == 27)
				exit(0);

			for(int i = 0; i < renderObjects.size(); i++)
			{
				renderObjects[i]->processNormalKeys(key, x, y);
			}
		}
	}

	void processSpecialKeys(int key, int xx, int yy) 
	{
		for(int i = 0; i < renderObjects.size(); i++)
		{
			renderObjects[i]->processSpecialKeys(key, xx, yy);
		}
	}

	int main(int argc, char **argv) 
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowPosition(0,0);
		glutInitWindowSize(1920,1080);
		glutCreateWindow("Squishy!?");
		glutFullScreen();

		glutDisplayFunc(renderScene);
		glutReshapeFunc(changeSize);
		glutIdleFunc(updateAll);

		glEnable(GL_DEPTH_TEST);

		glEnable(GL_FOG);
		glFogfv(GL_FOG_COLOR,FogCol);
		glFogi(GL_FOG_MODE, GL_EXP2);
		glFogf(GL_FOG_DENSITY, 0.1f);
		glHint(GL_FOG_HINT, GL_NICEST);

		glutKeyboardFunc(processNormalKeys);

		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);

		glutSetCursor(GLUT_CURSOR_NONE); 

		renderObjects.push_back(new Player());
		renderObjects.push_back(new World());
		renderObjects.push_back(new JellyFish());

		texturizeBackground(2);
		introTexture  =  tl.loadTexture("Intro.png");

		glutMainLoop();
	}