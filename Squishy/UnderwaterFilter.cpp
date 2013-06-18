#include "UnderwaterFilter.h"
#include <GL/glut.h>
#include <GL/GL.h>
#include "math.h"



UnderwaterFilter::UnderwaterFilter(void)
{
	ratio = 1.0* glutGet(GLUT_SCREEN_WIDTH) / glutGet(GLUT_SCREEN_HEIGHT);
}


UnderwaterFilter::~UnderwaterFilter(void)
{
}

//Functions as a sort of internal renderScene, add all drawing code for this object here
void UnderwaterFilter::Render()
{
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, glutGet(GLUT_SCREEN_WIDTH) , glutGet(GLUT_SCREEN_HEIGHT), 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushAttrib( GL_CURRENT_BIT | GL_DEPTH_BITS | GL_LIGHTING_BIT | GL_ENABLE_BIT);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	//Draw filter
	glColor4f(0.6f, 0.59, 1.0f, 0.1f);
	glBegin(GL_QUADS);
	glVertex2f(0.0, 0.0);
	glVertex2f(glutGet(GLUT_SCREEN_WIDTH), 0.0);
	glVertex2f(glutGet(GLUT_SCREEN_WIDTH) , glutGet(GLUT_SCREEN_HEIGHT) );
	glVertex2f(0.0, glutGet(GLUT_SCREEN_HEIGHT));
	glEnd();
	
	glPopAttrib();

	//end of drawing hud
	glPopMatrix();
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, glutGet(GLUT_SCREEN_WIDTH) , glutGet(GLUT_SCREEN_HEIGHT));
	gluPerspective(90,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);	

}

//Derived classes all have this class, it functions as the method that allows you to implement logic
void UnderwaterFilter::Update()
{

}