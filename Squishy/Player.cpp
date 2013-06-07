#include "Player.h"
#include <GL/glut.h>
#include <GL/GL.h>
#include <windows.h>
#include "main.h"
#include "ObjModel.h"

CCamera objCam; 
GLuint SKYFRONT;
GLuint SKYBACK;
GLuint SKYLEFT;
GLuint SKYRIGHT;
GLuint SKYUP;
GLuint SKYDOWN;
float skybox = 0.0f;
bool moveBox;
ObjModel* squishy = new ObjModel("squishy1.obj");

Player::Player(void)
{
	objCam.Position_Camera(0, 1.5f, 4.0f,	0, 1.5f, 0,   0, 1.0f, 0);
	SKYUP = objCam.loadTexture("caustics.jpg");
	SKYFRONT = objCam.loadTexture("JellyfishSea.png");
	SKYBACK = SKYFRONT;
	SKYLEFT = SKYFRONT;
	SKYRIGHT = SKYFRONT;
}

Player::~Player(void)
{
}

void Draw_Skybox(float x, float y, float z, float width, float height, float length)
{
	// Center the Skybox around the given x,y,z position
	x = x - width  / 2;
	y = y - height / 2;
	z = z - length / 2;

	// Draw Front side
	glBindTexture(GL_TEXTURE_2D, SKYFRONT);
	glBegin(GL_QUADS);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y+height, z+length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y+height, z+length); 
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y,		z+length);
	glEnd();

	// Draw Back side
	glBindTexture(GL_TEXTURE_2D, SKYBACK);
	glBegin(GL_QUADS);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y,		z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height, z); 
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y+height,	z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y,		z);
	glEnd();

	// Draw Left side
	glBindTexture(GL_TEXTURE_2D, SKYLEFT);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y+height,	z);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y+height,	z+length); 
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y,		z);		
	glEnd();

	// Draw Right side
	glBindTexture(GL_TEXTURE_2D, SKYRIGHT);
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y,		z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y,		z+length);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height,	z+length); 
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y+height,	z);
	glEnd();

	// Draw Up side
	glBindTexture(GL_TEXTURE_2D, SKYUP);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height, z);
		glTexCoord2f(100.0f, 0.0f); glVertex3f(x+width, y+height, z+length); 
		glTexCoord2f(100.0f, 100.0f); glVertex3f(x,		  y+height,	z+length);
		glTexCoord2f(0.0f, 100.0f); glVertex3f(x,		  y+height,	z);
	glEnd();

	// Draw Down side
	glBindTexture(GL_TEXTURE_2D, SKYDOWN);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y,		z+length); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y,		z);
	glEnd();
}

//Functions as a sort of internal renderScene, add all drawing code for this object here
void Player::Render()
{
	gluLookAt(objCam.mPos.x,  objCam.mPos.y,  objCam.mPos.z,	
			  objCam.mView.x, objCam.mView.y, objCam.mView.z,	
			  objCam.mUp.x,   objCam.mUp.y,   objCam.mUp.z);	

	glPushMatrix();
	glTranslatef(objCam.mView.x,1.2f,objCam.mView.z);
	glScaled(0.3,0.3,0.3);
	squishy->draw();//*************************************************************************************************************FIX THIS*********************************
	glPopMatrix();

	glPushMatrix();
	glTranslated(objCam.mView.x, objCam.mView.y, objCam.mView.z);
	glTranslated(skybox, 0, skybox);
	Draw_Skybox(0,0,0,500, 15, 500);	
	glPopMatrix();
}

//Derived classes all have this class, it functions as the method that allows you to implement logic
void Player::Update()
{
	objCam.Mouse_Move(500, 500);

	if(skybox < 0)
	{
		moveBox = true;
	}
	else if(skybox > 0.2f)
	{
		moveBox = false;
	}

	if(moveBox)
	{
		skybox += 0.0008f;
	}
	else
	{
		skybox -= 0.0008f;
	}
}

//Using this method you can process normalkeys
void Player::processNormalKeys(unsigned char key, int x, int y)
{
	switch (key) {
	case 'f' :
		objCam.Strafe_Camera(-CAMERASPEED);
		break;
	case 'h' :
		objCam.Strafe_Camera(CAMERASPEED);
		break;
	case 't' :
		objCam.Move_Camera(CAMERASPEED);	
		break;
	case 'g' :
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