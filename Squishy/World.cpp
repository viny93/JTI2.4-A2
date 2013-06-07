#include "World.h"
#include <GL/glut.h>
#include <GL/GL.h>
#include "main.h"

World::World(void)
{
	type = WORLD;
	//floorTexture  =  loadTexture("background.png");
	//floorTexture  =  loadTexture("grassTexture.png"); //testing only
}
CCamera world; 
GLuint floorTexture;
GLuint blendingTexture;

void createFloor()
{
	glBindTexture(GL_TEXTURE_2D, floorTexture);
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
	glBindTexture(GL_TEXTURE_2D, blendingTexture);
	glBegin( GL_QUADS );

	glTexCoord2f(0, 0);
	glVertex3f(-30, 0.1, -60);
	glTexCoord2f(0, 1);
	glVertex3f(30, 0.1, -60);
	glTexCoord2f(1, 1);
	glVertex3f(30, 0.1, 60);
	glTexCoord2f(1, 0);
	glVertex3f(-30, 0.1, 60);

	glEnd();
}

World::World(void)
{
	floorTexture = world.loadTexture("background.png");
	blendingTexture = world.loadTexture("caustics.jpg");
}

World::~World(void)
{
	
}

//Functions as a sort of internal renderScene, add all drawing code for this object here
void World::Render()
{
	createFloor();

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

