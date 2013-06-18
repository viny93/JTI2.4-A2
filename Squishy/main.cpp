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
#include "HUD.h"
#include "stb_image.h"
#include "Detection.h"
#include "Trap.h"
#include <mmsystem.h>
#include <process.h>
#include "Screens.h"
#include "UnderwaterFilter.h"
#include "Enemy.h"

float red=1.0f, blue=1.0f, green=1.0f;
float lx=0.0f,lz=-1.0f;
float x=0.0f,z=2.5f;

float light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_position[] = { 0, 10, 0, 1.0 };
static float amb[] = {0.4, 0.4, 0.4, 0.0};
static float dif[] = {1.0, 1.0, 1.0, 0.0};

float FogCol[3]={0.0f,0.0f,0.1f};

static std::vector<RenderObject*> renderObjects;

GLuint introTexture;
int gamestate = 1;
LPCSTR soundToPlay;
CCamera tl;
GameState *state2;

Detection *detection;
World* world;

bool _invuln;
int _invulnCount;

cv::Mat makeHeightmap(int cam)
{
	cv::VideoCapture cap(cam);
	cv::Mat save_img;
	cv::Mat biggerImage;
	cv::Size size(128, 128);

	cap >> save_img;

	if(biggerImage.empty())
	{
		std::cerr << "Something is wrong with the webcam, could not get frame." << std::endl;
	}
	imwrite("heightmap.png", save_img); 

	return biggerImage;
}

void modMap()
{
	cv::Mat hsv;
	cv::Mat thresholded;
	cv::Mat eroded;
	cv::Mat closed;
	cv::Mat dilated;
	cv::Mat dst, detected_edges;
	cv::Mat src;
	int lowTreshold = 1;
	int ratio = 3;
	int kernel_size = 3;
	int top, bottom, left, right;

	cv::Mat image = cv::imread("heightmap.png");
	cvtColor(image,hsv,CV_BGR2HSV);
	cv::inRange(hsv,cv::Scalar(10,65,10),cv::Scalar(35,255,35),thresholded);
	cv::Mat closingmat(20,20,CV_8U,cv::Scalar(1));
	cv::morphologyEx(thresholded,closed,cv::MORPH_CLOSE,closingmat);
	cv::erode(closed,eroded,cv::Mat(),cv::Point(-1,-1),1);

	Canny(eroded,detected_edges,lowTreshold,lowTreshold*ratio, kernel_size);

	cv::dilate(detected_edges, dilated, cv::Mat());

	cv::rectangle(dilated, cv::Point(0,0), cv::Point(639,479), cv::Scalar(255,255,255), 1, 8, 0);

	if(dilated.empty())
	{
		std::cerr << "Something is wrong with the webcam, could not get frame." << std::endl;
	}
	imwrite("modMap.png", dilated); 
}

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
	cap.release();

	if(biggerImage.empty())
	{
		std::cerr << "Something is wrong with the webcam, could not get frame." << std::endl;
	}
	imwrite("background.png", biggerImage);

	return biggerImage;
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

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);

	if(gamestate == 1) //launch menu
	{
		gluLookAt( x, 1.0f, z,
			x+lx, 1.0f, z+lz,
			0.0f, 1.0f, 0.0f);
		startSound("trooper.wav", 100);
		glTranslatef(1.0f, 2.0f, 0.0f);
		gluLookAt( x, 1.0f, z,
			x+lx, 1.0f, z+lz,
			0.0f, 1.0f, 0.0f);

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
	//Extracts player related data
	RenderObject *_player = renderObjects[0];
	float PlayerX = _player->RenderPositionX;
	float PlayerY = _player->RenderPositionY;
	float PlayerWidth = _player->RenderWidth;
	float PlayerDepth = _player->RenderDepth;

	PlayerX += 30;
	PlayerY += 60;

	float correction = 512.0f / 60.0f;

	PlayerX = PlayerX * correction;
	PlayerY = PlayerY * correction;
	
	for(int i = 0; i < renderObjects.size(); i++)
	{
		renderObjects[i]->Update();
		if(!renderObjects[i]->isAlive())
		{
			delete renderObjects[i];
			renderObjects.erase(renderObjects.begin() + i);	
		}

		if(_invuln)
		{
			_invulnCount--;
			if(_invulnCount == 0)
			{
				_invuln = false;
			}
		}
		else
		{
			if(renderObjects[i]->type == RenderObject::ENEMY)
			{
				float deltaX = (PlayerX - renderObjects[i]->RenderPositionY - 8.0f);
				if(deltaX < 0)
					deltaX = -deltaX;

				float deltaDepth = (PlayerDepth + renderObjects[i]->RenderDepth);

				if(deltaX < deltaDepth)
				{
					float deltaY = (PlayerY - renderObjects[i]->RenderPositionX) - 35.0f;
					if(deltaY < 0)
						deltaY = -deltaY;

					float deltaWidth = (PlayerWidth + renderObjects[i]->RenderWidth);

					if(deltaY < deltaWidth)
					{
						state2->die();
						_invuln = true;
						_invulnCount = 150;
					}
				}
			}
		} 
	}
	renderScene();
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
	//texturizeBackground(2);
	//makeHeightmap(2);
	//modMap();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH),glutGet(GLUT_SCREEN_HEIGHT));
	glutCreateWindow("Squishy!?");
	glutFullScreen();

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(updateAll);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_FOG);
	glFogfv(GL_FOG_COLOR,FogCol);
	glFogi(GL_FOG_MODE, GL_EXP2);
	glFogf(GL_FOG_DENSITY, 0.125f);
	glHint(GL_FOG_HINT, GL_NICEST);

	glutKeyboardFunc(processNormalKeys);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);

	glutSetCursor(GLUT_CURSOR_NONE);

	renderObjects.push_back(new Player(state2));
	renderObjects.push_back(new World());

	detection = new Detection();

	std::vector<cv::Point> enemycoordinates = detection->detectEnemies();	
	std::vector<cv::Point> trapcoordinates = detection->detectTraps();	
	std::vector<cv::Point> startendcoordinates = detection->detectStartEnd();
	cv::Point worldcoordinate = world->getBottomLeft();

	if(enemycoordinates.size() > 0 )
	{
		for(int i = 0; i<enemycoordinates.size(); i++)
		{
			cv::Point coordinate = enemycoordinates.at(i);
			renderObjects.push_back(new Enemy(coordinate,worldcoordinate));
		}
	}

	if(trapcoordinates.size() > 0 )
	{
		for(int i = 0; i<trapcoordinates.size(); i++)
		{
			cv::Point coordinate = trapcoordinates.at(i);
			renderObjects.push_back(new Trap(coordinate,worldcoordinate));
		}
	}

	if(startendcoordinates.size() > 0 )
	{
		for(int i = 0; i< startendcoordinates.size(); i++)
		{
			cv::Point coordinate = startendcoordinates.at(i);
			//Start/einde toevoegen
		}
	}

	renderObjects.push_back(new UnderwaterFilter());

	renderObjects.push_back(new HUD(state2));

	introTexture = tl.loadTexture("Intro.png");

	_invuln = true;
	_invulnCount = 150;

	glutMainLoop();
}