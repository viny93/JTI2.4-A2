#include "RenderObject.h"
#include <GL/glut.h>
#include <GL/GL.h>
#include "math.h"
#include "stb_image.h"

//Author: Zack
//RenderObject is he base for all renderobjects
RenderObject::RenderObject(void)
{
	//alive is true so the object is drawn
	alive = true;
}

RenderObject::~RenderObject(void)
{
}

//Functions as a sort of internal renderScene, add all drawing code for this object here
void RenderObject::Render()
{

}

//Derived classes all have this class, it functions as the method that allows you to implement logic
void RenderObject::Update()
{

}

//Using this method you can process normalkeys
void RenderObject::processNormalKeys(unsigned char key, int x, int y)
{

}

//Using this method you can process specialkeys
void RenderObject::processSpecialKeys(int key, int xx, int yy)
{

}

//This method sets alive to false
//which will delete it from the vector with the renderobjects and will no longer render or update the method
void RenderObject::Kill()
{
	alive = false;
}

//An accessor that returns whether this object is still alive
bool RenderObject::isAlive()
{
	return alive;
}
