#include "World.h"
#include <opencv\cv.h>
#include <GL/glut.h>
#include <GL/GL.h>
#include "main.h"
#include "ObjModel.h"
#include "stb_image.h"
#include<opencv\highgui.h> 
#include <opencv2\core\types_c.h>
#include "Vec3.h"

CCamera world; 
GLuint floorTexture;
GLuint blendingTexture;
GLuint rockTexture;

int levelSizeX = 120;
int levelSizeZ = 60;

float caustics = 0.0f;
bool movecaustics;

cv::Point bottomleft;
float random_x_array[100];
float random_z_array[100];
ObjModel* seaweed = new ObjModel("seaweed.obj");

cv::Mat heightMapImage;

void createFloor()
{
	glBindTexture(GL_TEXTURE_2D, floorTexture);
	glBegin( GL_QUADS );

	glTexCoord2f(0, 0);
	glVertex3f(-bottomleft.x, 0, -bottomleft.y);
	glTexCoord2f(0, 1);
	glVertex3f(bottomleft.x, 0, -bottomleft.y);
	glTexCoord2f(1, 1);
	glVertex3f(bottomleft.x, 0, bottomleft.y);
	glTexCoord2f(1, 0);
	glVertex3f(-bottomleft.x, 0, bottomleft.y);
	glVertex3f(-levelSizeZ/2, 0, -levelSizeX/2);
	glTexCoord2f(0, 1);
	glVertex3f(levelSizeZ/2, 0, -levelSizeX/2);
	glTexCoord2f(1, 1);
	glVertex3f(levelSizeZ/2, 0, levelSizeX/2);
	glTexCoord2f(1, 0);
	glVertex3f(-levelSizeZ/2, 0, levelSizeX/2);

	glEnd();
}

void buildHeightmap()
{
	glPushMatrix();
	glScalef(0.1f, 1, 0.1f);

	glTranslatef(-heightMapImage.cols/2.13, 0, -heightMapImage.rows*1.252);
	glScalef(1.25f,1,1.88f);
	glBegin(GL_QUADS);
	for(int x = 0; x < heightMapImage.cols; x++)
	{
		for(int y = 0; y < heightMapImage.rows; y++)
		{
			if (heightMapImage.at<UCHAR>(y,x*3) == 0)
			{
				for(int xx = -1; xx <= 1; xx++)
				{
					for(int yy = -1; yy <= 1; yy++)
					{
						if(x+xx < 0 || x+xx >= heightMapImage.cols || y+yy < 0 || y+yy >= heightMapImage.rows)
							continue;
						if(abs(xx) + abs(yy) != 1)
							continue;
						if(heightMapImage.at<UCHAR>(y+yy,(x+xx)*3) != 0)
						{
							if(xx == 0)
							{
								glVertex3f(y+0.5f*yy,0,x+0.5f);
								glVertex3f(y+0.5f*yy,10,x+0.5f);
								glVertex3f(y+0.5f*yy,10,x-0.5f);
								glVertex3f(y+0.5f*yy,0,x-0.5f);
							}
							if(yy == 0)
							{
								glVertex3f(y+0.5f,0,x+0.5f*xx);
								glVertex3f(y+0.5f,10,x+0.5f*xx);
								glVertex3f(y-0.5f,10,x+0.5f*xx);
								glVertex3f(y-0.5f,0,x+0.5f*xx);
							}
						}
					}
				}

			}

		}
	}
	glEnd();
	glPopMatrix();
}

void createCausticFloor()
{
	glPushMatrix();
	glTranslated(caustics, 0, caustics);
	glBindTexture(GL_TEXTURE_2D, blendingTexture);
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
	rockTexture = world.loadTexture("rockTexture.png");
	floorTexture = world.loadTexture("background.png");
	blendingTexture = world.loadTexture("caustics.jpg");
	bottomleft.x = 30;
	bottomleft.y = 60;
	heightMapImage = cv::imread("modMap.png");
	for(int i = 0; i < 99; i ++) 
	{
		random_x_array[i] = (rand() % levelSizeX); 
		random_z_array[i] = (rand() % levelSizeZ);
	}
}

World::~World(void)
{

}

//Functions as a sort of internal renderScene, add all drawing code for this object here
void World::Render()
{
	//glScalef(0.1f,0.1f,0.1f);
	createFloor();
	glBindTexture(GL_TEXTURE, rockTexture);
	buildHeightmap();
	glEnable (GL_BLEND);
	glBlendFunc (GL_DST_COLOR, GL_ONE);
	createCausticFloor();
	glDisable(GL_BLEND);

	for(int i = 0; i < 50; i ++) 
	{
		glPushMatrix();
		glTranslatef(random_z_array[i] - levelSizeZ/2, 0, random_x_array[i] - levelSizeX/2);
		glPushAttrib( GL_CURRENT_BIT );
		glScalef(0.05f,0.03f,0.05f);
		glColor3f(0.1f,1.0f,0.1f);
		seaweed->draw();
		glPopAttrib();
		glPopMatrix();
	}
	//glTranslated(0,-2.0f,0);
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
