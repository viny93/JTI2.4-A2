#include "JellyFish.h"
#include <GL/glut.h>
#include <GL/GL.h>
#include <windows.h>
#include "main.h"
#include "ObjModel.h"

CCamera jellycam; 
GLuint jellyTexture;
ObjModel* jellyModel = new ObjModel("kwalleke.obj");

JellyFish::JellyFish(void)
{
	jellyTexture = jellycam.loadTexture("jellyfishTexture.png");
}

JellyFish::~JellyFish(void)
{
	
}

//Functions as a sort of internal renderScene, add all drawing code for this object here
void JellyFish::Render()
{
	glPushMatrix();
	glScaled(0.3,0.3,0.3);
	glTranslated(0,3.5f,0);
	glBindTexture(GL_TEXTURE_2D, jellyTexture);
	glEnable (GL_BLEND);
	glBlendFunc (GL_ONE, GL_ONE);
	jellyModel->draw();
	glDisable(GL_BLEND);
	glPopMatrix();
}

//Derived classes all have this class, it functions as the method that allows you to implement logic
void JellyFish::Update()
{

}

//Using this method you can process normalkeys
void JellyFish::processNormalKeys(unsigned char key, int x, int y)
{

}

//Using this method you can process specialkeys
void JellyFish::processSpecialKeys(int key, int xx, int yy)
{

}