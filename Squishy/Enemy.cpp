#include "Enemy.h"
#include <GL/glut.h>
#include <GL/GL.h>
#include <windows.h>

Enemy::Enemy()
{
	type = ENEMY;
	RenderPositionX = 2.0f;
	RenderPositionY = 2.0f;
	RenderWidth = 1.0f;
	RenderDepth = 1.0f;
}

Enemy::~Enemy(void)
{
}

//Functions as a sort of internal renderScene, add all drawing code for this object here
void Enemy::Render()
{
	glPushMatrix();
	glTranslatef(RenderPositionX, 1.0f, RenderPositionY);
	glBegin(GL_TRIANGLES);				
	glColor3f(1.0f,0.0f,0.0f);				
	glVertex3f( 0.0f, 1.0f, 0.0f);			
	glVertex3f(-RenderWidth,-1.0f, RenderDepth);			
	glVertex3f( RenderWidth,-1.0f, RenderDepth);		
	glVertex3f( 0.0f, 1.0f, 0.0f);						
	glVertex3f( RenderWidth,-1.0f, RenderDepth);					
	glVertex3f( RenderWidth,-1.0f, -RenderDepth);					
	glVertex3f( 0.0f, 1.0f, 0.0f);					
	glVertex3f( RenderWidth,-1.0f, -RenderDepth);					
	glVertex3f(-RenderWidth,-1.0f, -RenderDepth);						
	glVertex3f( 0.0f, 1.0f, 0.0f);					
	glVertex3f(-RenderWidth,-1.0f,-RenderDepth);					
	glVertex3f(-RenderWidth,-1.0f, RenderDepth);			
	glEnd();
	glPopMatrix();
}

//Derived classes all have this class, it functions as the method that allows you to implement logic
void Enemy::Update()
{

}

//Using this method you can process normalkeys
void Enemy::processNormalKeys(unsigned char key, int x, int y)
{
}

//Using this method you can process specialkeys
void Enemy::processSpecialKeys(int key, int xx, int yy)
{

}