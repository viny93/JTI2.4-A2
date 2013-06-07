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
	
	_movementX = 0.0f;
	_movementY = 60.0f;
	_variationX = 2.1f;
	_variationY = 0.0f;
	_count = 0; //Remove when using VSync
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
	//Remove if using VSync from here till....
	_count = (_count + 1) % 10;
	if(!_count == 10)
		return;
	//...here


	if(_variationX < 0)
	{
		_movementX++;
	}
	else
	{
		_movementX--;
	}

	if(_variationY < 0)
	{
		_movementY++;
	}
	else
	{
		_movementY--;
	}

	_variationX += _movementX / 1000;
	_variationY += _movementY / 1000;

	RenderPositionX += _variationX;
	RenderPositionY += _variationY;
}

//Using this method you can process normalkeys
void Enemy::processNormalKeys(unsigned char key, int x, int y)
{
}

//Using this method you can process specialkeys
void Enemy::processSpecialKeys(int key, int xx, int yy)
{

}