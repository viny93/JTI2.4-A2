#include "Screens.h"
#include "main.h"
#include <GL/glut.h>


Screens::Screens(void)
{
}


Screens::~Screens(void)
{
}

void Screens::writeString(char* string, int x, int y, void* font)
{
	glRasterPos2i(x, y);
    int len = strlen(string);
    for (int i=0; i < len; i++)
    {
        glutBitmapCharacter(font, string[i]);
    }
}

void Screens::setOrthographicProjection()
{
	glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 640);
    glScalef(1, -1, 1);
    glTranslatef(0, -640, 0);
    glMatrixMode(GL_MODELVIEW);
}

void Screens::resetPerspectiveProjection()
{
	glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void Screens::Render()
{
	setOrthographicProjection();
	glColor3f (1.0, 1.0, 1.0);
	writeString("lives remaining: ", 100, 100, GLUT_BITMAP_TIMES_ROMAN_24);
	resetPerspectiveProjection();
}

void Screens::Update()
{

}