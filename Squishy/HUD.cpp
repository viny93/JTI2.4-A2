#include "HUD.h"
#include <GL/glut.h>
#include <GL/GL.h>
#include <windows.h>
#include "main.h"
#include "ObjModel.h"
#include "GameState.h"

CCamera hudcam; 
GLuint heartTexture;

HUD::HUD(void)
{
	heartTexture = hudcam.loadTexture("heartTexture.png");
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
	glBindTexture( GL_TEXTURE_2D, heartTexture );
	glBegin(GL_QUADS);

	//Draw life icons here:
	for(int i = 0; i < lives; i++)
	{
		DrawLives(i);
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

//Derived classes all have this class, it functions as the method that allows you to implement logic
void HUD::Update()
{

}

//Using this method you can process normalkeys
void HUD::processNormalKeys(unsigned char key, int x, int y)
{
	////removes 1 life icon on the screen
	//switch (key) {
	//	case 32 :
	//		lives--;
	//		break;
	//	}
}

//Using this method you can process specialkeys
void HUD::processSpecialKeys(int key, int xx, int yy)
{

}