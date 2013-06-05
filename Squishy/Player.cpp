#include "Player.h"
#include <GL/glut.h>
#include <GL/GL.h>
#include <windows.h>
#include "main.h"

CCamera objCam;

Player::Player(void)
{
	objCam.Position_Camera(0, 1.5f, 4.0f,	0, 1.5f, 0,   0, 1.0f, 0);

	//Alter these values to change the bounding box for the player
	RenderWidth = .3f;
	RenderDepth = .3f;

	type = PLAYER;
}

Player::~Player(void)
{
}

//Functions as a sort of internal renderScene, add all drawing code for this object here
void Player::Render()
{
	gluLookAt(objCam.mPos.x,  objCam.mPos.y,  objCam.mPos.z,	
			  objCam.mView.x, objCam.mView.y, objCam.mView.z,	
			  objCam.mUp.x,   objCam.mUp.y,   objCam.mUp.z);	

	glPushMatrix();
	glTranslatef(objCam.mView.x,0.0f,objCam.mView.z);
	glScalef(0.3f,1.0f,0.3f);
	glTranslatef(0,1.0f,0);
	glBegin(GL_TRIANGLES);				
	glColor3f(1.0f,0.0f,0.0f);				
	glVertex3f( 0.0f, 1.0f, 0.0f);			
	glVertex3f(-1.0f,-1.0f, 1.0f);			
	glVertex3f( 1.0f,-1.0f, 1.0f);		
	glVertex3f( 0.0f, 1.0f, 0.0f);						
	glVertex3f( 1.0f,-1.0f, 1.0f);					
	glVertex3f( 1.0f,-1.0f, -1.0f);					
	glVertex3f( 0.0f, 1.0f, 0.0f);					
	glVertex3f( 1.0f,-1.0f, -1.0f);					
	glVertex3f(-1.0f,-1.0f, -1.0f);						
	glVertex3f( 0.0f, 1.0f, 0.0f);					
	glVertex3f(-1.0f,-1.0f,-1.0f);					
	glVertex3f(-1.0f,-1.0f, 1.0f);			
	glEnd();
	glPopMatrix();
}

//Derived classes all have this class, it functions as the method that allows you to implement logic
void Player::Update()
{
	objCam.Mouse_Move(500, 500);
	RenderPositionX = objCam.mView.x;
	RenderPositionY = objCam.mView.z;
}

//Using this method you can process normalkeys
void Player::processNormalKeys(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a' :
		objCam.Strafe_Camera(-CAMERASPEED);
		break;
	case 'd' :
		objCam.Strafe_Camera(CAMERASPEED);
		break;
	case 'w' :
		objCam.Move_Camera(CAMERASPEED);	
		break;
	case 's' :
		objCam.Move_Camera(-CAMERASPEED);	
		break;
	case 'z': 
		glutDestroyWindow(0);
		exit (0);
		break;
	}
}

//Using this method you can process specialkeys
void Player::processSpecialKeys(int key, int xx, int yy)
{

}