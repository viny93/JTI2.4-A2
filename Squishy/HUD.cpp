#include "HUD.h"
#include <GL/glut.h>
#include <GL/GL.h>
#include <windows.h>
#include "main.h"
#include "ObjModel.h"
#include "GameState.h"

CCamera hudcam; 
GLuint heartTexture;
GLuint GameOverScreenTexture;

HUD::HUD(void)
{
	heartTexture = hudcam.loadTexture("heartTexture.png");
	GameOverScreenTexture = hudcam.loadTexture("GameOverScreen.png");
	ratio = 1.0* glutGet(GLUT_SCREEN_WIDTH)/ glutGet(GLUT_SCREEN_HEIGHT);
}

HUD::~HUD(void)
{
	
}

//Functions as a sort of internal renderScene, add all drawing code for this object here
void HUD::Render()
{
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT), 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushAttrib( GL_CURRENT_BIT );
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	

	//Draw life icons here:
	if(lives > 0)
	{
		glBindTexture( GL_TEXTURE_2D, heartTexture );
		glBegin(GL_QUADS);
		for(int i = 0; i < lives; i++)
		{
			DrawLives(i);
		}
	}
	else
	{
		glBindTexture( GL_TEXTURE_2D, GameOverScreenTexture);
		glBegin(GL_QUADS);
		drawGameOverScreen();
	}
	glEnd();
	glPopAttrib();

	//end of drawing hud
	glPopMatrix();
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
	gluPerspective(90,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
}

void HUD::DrawLives(int i)
{
		glTexCoord2f(0, 1);
		glVertex2f(glutGet(GLUT_SCREEN_WIDTH) - (20 + 75*i), 72);
		glTexCoord2f(1, 1);
		glVertex2f(glutGet(GLUT_SCREEN_WIDTH) - (95 + 75*i), 72);
		glTexCoord2f(1, 0);
		glVertex2f(glutGet(GLUT_SCREEN_WIDTH) - (95 + 75*i), 20);
		glTexCoord2f(0, 0);
		glVertex2f(glutGet(GLUT_SCREEN_WIDTH) - (20 + 75*i), 20);
}

void HUD::drawGameOverScreen()
{
	glTexCoord2f(0, 1);
		glVertex2f(0,  glutGet(GLUT_SCREEN_HEIGHT));
		glTexCoord2f(1, 1);
		glVertex2f(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
		glTexCoord2f(1, 0);
		glVertex2f(glutGet(GLUT_SCREEN_WIDTH), 0);
		glTexCoord2f(0, 0);
		glVertex2f(0, 0);
}

//Derived classes all have this class, it functions as the method that allows you to implement logic
void HUD::Update()
{

}

//Using this method you can process normalkeys
void HUD::processNormalKeys(unsigned char key, int x, int y)
{
	//removes 1 life icon on the screen
	switch (key) {
		case 32 :
			lives--;
			break;
		}
}

//Using this method you can process specialkeys
void HUD::processSpecialKeys(int key, int xx, int yy)
{

}