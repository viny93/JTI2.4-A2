#include "Trap.h"
#include "RenderObject.h"
#include<opencv\cv.h>
#include <GL/glut.h>
#include <GL/GL.h>
#include "math.h"
#include "stb_image.h"
#include "ObjModel.h"
#include "main.h"

bool activated = false;
CCamera jellycam; 
GLuint jellyTexture;
ObjModel* jellyModel = new ObjModel("kwalleke.obj");


Trap::Trap(cv::Point coordinates,cv::Point worldcoordinates)
{
	this->coordinates = coordinates;
	this->worldcoordinates = worldcoordinates;

	type = ENEMY;
	RenderPositionX = coordinates.x;
	RenderPositionY = coordinates.y;
	RenderWidth = 5.0f;
	RenderDepth = 5.0f;

	jellyTexture = jellycam.loadTexture("jellyfishTexture.png");
}

//Functions as a sort of internal renderScene, add all drawing code for this object here
void Trap::Render()
{
	glPushMatrix();
	
    glTranslatef((coordinates.y/(512/60) - worldcoordinates.x -1.5f)*0.9f,0,(coordinates.x/(512/60) - worldcoordinates.y - 3.0f)*0.9f);

	glPushAttrib(GL_CURRENT_BIT);
	glScalef(0.3f,0.3f,0.3f);
	glTranslated(0,3.0f,0);

	glBindTexture(GL_TEXTURE_2D, jellyTexture);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_COLOR, GL_ONE);
	jellyModel->draw();
	glDisable(GL_BLEND);

	glPopAttrib();
	glPopMatrix();
}

//Derived classes all have this class, it functions as the method that allows you to implement logic
void Trap::Update()
{
	if(activated)
	{
		//-99999999 lifes
	}
}







