#include "World.h"
#include <opencv\cv.h>
#include <GL/glut.h>
#include <GL/GL.h>
#include "main.h"

cv::Point bottomleft;

World::World(void)
{
	//floorTexture  =  loadTexture("background.png");
	//floorTexture  =  loadTexture("grassTexture.png"); //testing only
	bottomleft.x = 30;
	bottomleft.y = 30;
}

World::~World(void)
{
}

//Functions as a sort of internal renderScene, add all drawing code for this object here
void World::Render()
{
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