#include "Enemy.h"
#include <GL/glut.h>
#include <GL/GL.h>
#include <windows.h>
#include <opencv\cv.h>
#include <iostream>
#include "ObjModel.h"
#include "main.h"

GLuint sharktexture;
ObjModel* sharkModel = new ObjModel("shark.obj");
CCamera sharkcam; 

Enemy::Enemy(cv::Point coordinates,cv::Point worldcoordinates)
{
	this->coordinates = coordinates;
	this->worldcoordinates = worldcoordinates;
	
	type = ENEMY;
	RenderPositionX = (float) coordinates.x;
	RenderPositionY = (float) coordinates.y;
	RenderWidth = 35.0f;
	RenderDepth = 5.0f;
	
	_movementX = 0.0f;
	_movementY = 60.0f;
	_variationX = 2.1f;
	_variationY = 0.0f;
	_count = 0; //Remove when using VSync
	sharktexture = sharkcam.loadTexture("sharktexture.png");
}

Enemy::~Enemy(void)
{

}

//Functions as a sort of internal renderScene, add all drawing code for this object here
void Enemy::Render()
{
	glPushMatrix();

	glTranslatef((RenderPositionY/(512/60) - worldcoordinates.x -1.5f)*0.9f,0,(RenderPositionX/(512/60) - worldcoordinates.y - 3.0f)*0.9f);
	glPushAttrib(GL_CURRENT_BIT);

	glTranslatef(0.0f, 0.5f, 0.0f);
	glScalef(0.10f, 0.10f, 0.10f);
	glBindTexture(GL_TEXTURE_2D, sharktexture);
	glBlendFunc (GL_SRC_COLOR, GL_ONE);
	sharkModel->draw();

	glPopAttrib();
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
		_movementX+=0.5;
	}
	else
	{
		_movementX-=0.5;
	}

	if(_variationY < 0)
	{
		_movementY+=0.5;
	}
	else
	{
		_movementY-=0.5;
	}

	_variationX += _movementX / 100;
	_variationY += _movementY / 100;

	RenderPositionX += _movementX*2 / 100;
	RenderPositionY += _movementY*2 / 100;
}

//Using this method you can process normalkeys
void Enemy::processNormalKeys(unsigned char key, int x, int y)
{
}

//Using this method you can process specialkeys
void Enemy::processSpecialKeys(int key, int xx, int yy)
{

}