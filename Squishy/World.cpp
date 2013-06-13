#include "World.h"
#include <opencv\cv.h>
#include <GL/glut.h>
#include <GL/GL.h>
#include "main.h"

CCamera world; 
GLuint worldFloorTexture;
GLuint worldBlendingTexture;

float caustics = 0.0f;
bool movecaustics;

cv::Point bottomleft;

void createFloor()
{
	glBindTexture(GL_TEXTURE_2D, worldFloorTexture);
	glBegin( GL_QUADS );

	glTexCoord2f(0, 0);
	glVertex3f(-30, 0, -60);
	glTexCoord2f(0, 1);
	glVertex3f(30, 0, -60);
	glTexCoord2f(1, 1);
	glVertex3f(30, 0, 60);
	glTexCoord2f(1, 0);
	glVertex3f(-30, 0, 60);

	glEnd();
}

void createCausticFloor()
{
	glPushMatrix();
	glTranslated(caustics, 0, caustics);
	glBindTexture(GL_TEXTURE_2D, worldBlendingTexture);
	glBegin( GL_QUADS );
	glTexCoord2f(0, 0);
	glVertex3f(-250, 0.1, -250);
	glTexCoord2f(0, 100);
	glVertex3f(250, 0.1, -250);
	glTexCoord2f(100, 100);
	glVertex3f(250, 0.1, 250);
	glTexCoord2f(100, 0);
	glVertex3f(-250, 0.1, 250);
	glEnd();
	glPopMatrix();
}

World::World(void)
{
	worldFloorTexture = world.loadTexture("background.png");
	worldBlendingTexture = world.loadTexture("caustics.jpg");
	bottomleft.x = 30;
	bottomleft.y = 30;
}

World::~World(void)
{
	
}

//Functions as a sort of internal renderScene, add all drawing code for this object here
void World::Render()
{
	createFloor();
	glEnable (GL_BLEND);
	glBlendFunc (GL_ONE, GL_ONE);
	createCausticFloor();
	glDisable(GL_BLEND);

	//Code from Ricardo - placeholder?
	//glBindTexture(GL_TEXTURE_2D, floorTexture);
	glBegin( GL_QUADS );

    glTexCoord2f(0, 0);
    glVertex3f(-bottomleft.x, 0, -bottomleft.y);
    glTexCoord2f(0, 1);
    glVertex3f(bottomleft.x, 0, -bottomleft.y);
    glTexCoord2f(1, 1);
    glVertex3f(bottomleft.x,0, bottomleft.y);
    glTexCoord2f(1, 0);
    glVertex3f(-bottomleft.x, 0, bottomleft.y);
	
	glEnd();
}

//Derived classes all have this class, it functions as the method that allows you to implement logic
void World::Update()
{
	if(caustics < 0)
	{
		movecaustics = true;
	}
	else if(caustics > 0.2f)
	{
		movecaustics = false;
	}

	if(movecaustics)
	{
		caustics += 0.001f;
	}
	else
	{
		caustics -= 0.001f;
	}
}

//Using this method you can process normalkeys
void World::processNormalKeys(unsigned char key, int x, int y)
{

}

//Using this method you can process specialkeys
void World::processSpecialKeys(int key, int xx, int yy)
{

}

cv::Point World::getBottomLeft()
{
	return bottomleft;
}

