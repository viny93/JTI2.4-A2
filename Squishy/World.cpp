#include "World.h"
#include <opencv\cv.h>
#include <GL/glut.h>
#include <GL/GL.h>
#include "main.h"
#include "ObjModel.h"
#include "stb_image.h"
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

unsigned char* heightmapData;
int heightmapWidth, heightmapHeight, heightmapDepth;

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
	#define heightmap(x,y) heightmapData[heightmapDepth*((x) + (y) * heightmapWidth)] * 0.01f - 0.2f
	glBindTexture(GL_TEXTURE, rockTexture);
	glBegin(GL_TRIANGLES);
	for(int x = 0; x < heightmapWidth-1; x++)
	{
		for(int y = 0; y < heightmapHeight-1; y++)
		{
			{
				Vec3 a((x-heightmapWidth/2)*0.2f, heightmap(x,y), (y-heightmapHeight/2) * 0.2f);
				Vec3 b((x+1-heightmapWidth/2)*0.2f, heightmap(x+1,y), (y-heightmapHeight/2) * 0.2f);
				Vec3 c((x+1-heightmapWidth/2)*0.2f, heightmap(x+1,y+1), (y+1-heightmapHeight/2) * 0.2f);
				Vec3 edge1 = c - b;
				Vec3 edge2 = a - b;

				Vec3 normal = edge2.cross(edge1);
				normal = normal / normal.length();

				glNormal3f(normal.x,normal.y,normal.z);
				glTexCoord2f(a.x * 0.1f, a.z * 0.1f); glVertex3f(a.x, a.y, a.z);
				glTexCoord2f(b.x * 0.1f, b.z * 0.1f); glVertex3f(b.x, b.y, b.z);
				glTexCoord2f(c.x * 0.1f, c.z * 0.1f); glVertex3f(c.x, c.y, c.z);
			}

			{
				Vec3 a((x-heightmapWidth/2)*0.2f, heightmap(x,y), (y-heightmapHeight/2) * 0.2f);
				Vec3 b((x+1-heightmapWidth/2)*0.2f, heightmap(x+1,y+1), (y+1-heightmapHeight/2) * 0.2f);
				Vec3 c((x-heightmapWidth/2)*0.2f, heightmap(x,y+1), (y+1-heightmapHeight/2) * 0.2f);
				Vec3 edge1 = c - b;
				Vec3 edge2 = a - b;

				Vec3 normal = edge2.cross(edge1);
				normal = normal / normal.length();

				glNormal3f(normal.x,normal.y,normal.z);
				glTexCoord2f(a.x * 0.1f, a.z * 0.1f); glVertex3f(a.x, a.y, a.z);
				glTexCoord2f(b.x * 0.1f, b.z * 0.1f); glVertex3f(b.x, b.y, b.z);
				glTexCoord2f(c.x * 0.1f, c.z * 0.1f); glVertex3f(c.x, c.y, c.z);
			}

		}
	}
	glEnd();
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
	rockTexture = world.loadTexture("rockTexture.jpg");
	floorTexture = world.loadTexture("background.png");
	blendingTexture = world.loadTexture("caustics.jpg");
	bottomleft.x = 30;
	bottomleft.y = 60;
	
	for(int i = 0; i < 99; i ++) 
			{
				random_x_array[i] = (rand() % levelSizeX); 
				random_z_array[i] = (rand() % levelSizeZ);
	}
	heightmapData = stbi_load("heightmap.png", &heightmapWidth, &heightmapHeight, &heightmapDepth, 4);
}

World::~World(void)
{
	
}

//Functions as a sort of internal renderScene, add all drawing code for this object here
void World::Render()
{
	createFloor();
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
	buildHeightmap();
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
