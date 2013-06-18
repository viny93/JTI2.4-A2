#include "Trap.h"
#include "RenderObject.h"
#include<opencv\cv.h>
#include <GL/glut.h>
#include <GL/GL.h>
#include "math.h"
#include "stb_image.h"

bool activated = false;

Trap::Trap(cv::Point coordinates,cv::Point worldcoordinates)
{
	this->coordinates = coordinates;
	this->worldcoordinates = worldcoordinates;

	type = ENEMY;
	RenderPositionX = worldcoordinates.x;
	RenderPositionY = worldcoordinates.y;
	RenderWidth = 1.0f;
	RenderDepth = 1.0f;
}

//Functions as a sort of internal renderScene, add all drawing code for this object here
void Trap::Render()
{
	glPushMatrix();
	
     glTranslatef((coordinates.y/(512/60) - worldcoordinates.x -1.5f)*0.85f,0,(coordinates.x/(512/60) - worldcoordinates.y - 3.0f)*0.85f);

	glPushAttrib(GL_CURRENT_BIT);

       glBegin(GL_QUADS);				  // Draw The Cube Using quads
    glColor3f(0.0f,1.0f,0.0f);		  // Color Blue
    glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Bottom Left Of The Quad (Top)
    glVertex3f( 1.0f, 1.0f, 1.0f);    // Bottom Right Of The Quad (Top)
    glColor3f(1.0f,0.5f,0.0f);		  // Color Orange
    glVertex3f( 1.0f,-1.0f, 1.0f);    // Top Right Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f, 1.0f);    // Top Left Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Bottom)
    glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Bottom)
    glColor3f(1.0f,0.0f,0.0f);		  // Color Red    
    glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Front)
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Front)
    glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Front)
    glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Front)
    glColor3f(1.0f,1.0f,0.0f);		  // Color Yellow
    glVertex3f( 1.0f,-1.0f,-1.0f);    // Top Right Of The Quad (Back)
    glVertex3f(-1.0f,-1.0f,-1.0f);    // Top Left Of The Quad (Back)
    glVertex3f(-1.0f, 1.0f,-1.0f);    // Bottom Left Of The Quad (Back)
    glVertex3f( 1.0f, 1.0f,-1.0f);    // Bottom Right Of The Quad (Back)
    glColor3f(0.0f,0.0f,1.0f);		  // Color Blue
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Left)
    glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Left)
    glColor3f(1.0f,0.0f,1.0f);		  // Color Violet
    glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Right)
    glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Right) 

	glEnd();
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







