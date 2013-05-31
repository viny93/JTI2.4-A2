//Example class to follow when implementing new renderObjects
#include "Pyramid.h"
#include <GL/glut.h>
#include <GL/GL.h>
#include "math.h"
#include "stb_image.h"

GLuint pyramidtexture;

// hangle of rotation for the camera direction
float hangle=0.0;
float vangle=0.0;

// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f,z=5.0f;

Pyramid::Pyramid(void)
{
	//loading texture
    //pyramidtexture  =	loadTexture("C:\\Users\\Zack\\Documents\\Visual Studio 2010\\Projects\\cgr homework\\Debug\\pyramidtexture.png");
}


Pyramid::~Pyramid(void)
{
}

void Pyramid::Update(){
	//implement update code
}

void Pyramid::Render(){
	
	// Set the camera
	gluLookAt(	x, 1.0f, z,
			x+lx, 1.0f,  z+lz,
			0.0f, 1.0f,  0.0f);
	glRotatef(vangle, 1.0f, 0.0f, 0.0f);
	glRotatef(hangle, 0.0f, 1.0f, 0.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, pyramidtexture );

	glBegin(GL_TRIANGLES);
	glNormal3f(1,0,1); 
	// first triangle
	glTexCoord2f(1, 0);				
	glVertex3f(1,0,1);		
	glNormal3f(0,2,0); 
	glTexCoord2f(0.5, 1.0);	
	glVertex3f(0,2,0);		
	glNormal3f(-1,0,1); 
	glTexCoord2f(0, 0);				
	glVertex3f(-1,0,1);		
	glNormal3f(-1,0,1); 
	// second triangle
	glTexCoord2f(1, 0);
	glVertex3f(-1,0,1); 
	glNormal3f(0,2,0); 
	glTexCoord2f(0.5, 1.0);
	glVertex3f(0,2,0); 
	glNormal3f(-1,0,-1); 
	glTexCoord2f(0, 0);
	glVertex3f(-1,0,-1); 
	glNormal3f(-1,0,-1); 
	// third triangle
	glTexCoord2f(1, 0);
	glVertex3f(-1,0,-1); 
	glNormal3f(0,2,0); 
	glTexCoord2f(0.5, 1.0);
	glVertex3f(0,2,0); 
	glNormal3f(1,0,-1); 
	glTexCoord2f(0, 0);
	glVertex3f(1,0,-1); 
	glNormal3f(1,0,-1); 
	// last triangle
	glTexCoord2f(1, 0);
	glVertex3f(1,0,-1); 
	glNormal3f(0,2,0); 
	glTexCoord2f(0.5, 1.0);
	glVertex3f(0,2,0); 
	glNormal3f(1,0,1); 
	glTexCoord2f(0, 0);
	glVertex3f(1,0,1); 
	glEnd();
	glBegin(GL_TRIANGLES);
	glNormal3f(-1,0,1);
	glVertex3f(-1,0,1);
	glNormal3f(-1,0,-1);
	glVertex3f(-1,0,-1);
	glNormal3f(1,0,1);
	glVertex3f(1,0,1);
	glNormal3f(1,0,1);
	glVertex3f(1,0,1);
	glNormal3f(-1,0,-1);
	glVertex3f(-1,0,-1);
	glNormal3f(1,0,-1);
	glVertex3f(1,0,-1);
	glEnd();

	glBegin(GL_LINES);
	for (GLfloat i = -2.5; i <= 2.5; i += 0.25) {
		glVertex3f(i, 0, 2.5); glVertex3f(i, 0, -2.5);
		glVertex3f(2.5, 0, i); glVertex3f(-2.5, 0, i);
	}
	glEnd();
}

void Pyramid::processNormalKeys(unsigned char key, int x, int y)
{

}

void Pyramid::processSpecialKeys(int key, int xx, int yy)
{
	float fraction = 0.1f;

	switch (key) {
		case GLUT_KEY_LEFT :
			hangle -= 0.5f;/*
			lx = sin(hangle);
			lz = -cos(hangle);*/
			break;
		case GLUT_KEY_RIGHT :
			hangle += 0.5f;/*
			lx = sin(hangle);
			lz = -cos(hangle);*/
			break;
		case GLUT_KEY_UP :
			vangle -= 0.5f;
			//x += lx * fraction;
			//z += lz * fraction;
			break;
		case GLUT_KEY_DOWN :
			vangle += 0.5f;
		/*	x -= lx * fraction;
			z -= lz * fraction;*/
			break;
	}
}
