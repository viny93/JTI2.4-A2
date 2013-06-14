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
GLuint squishyTexture;
GLuint ironTexture;
GLuint currentTexture;
bool ink = false;
bool iron = false;
float inkDis;
float angle = -90.0f;

Player::Player(void)
{
	objCam.Position_Camera(0, 1.5f, 4.0f,	0, 1.5f, 0,   0, 1.0f, 0);
	SKYUP = objCam.loadTexture("caustics.jpg");
	SKYFRONT = objCam.loadTexture("JellyfishSea.png");
	SKYBACK = SKYFRONT;
	SKYLEFT = SKYFRONT;
	SKYRIGHT = SKYFRONT;
	ironTexture = objCam.loadTexture("ironTexture.png");
	squishyTexture = objCam.loadTexture("squishyTexture.png");
	currentTexture = objCam.loadTexture("squishyTexture.png");

}

Player::~Player(void)
{
}

void inkUpdate()
{
	if(ink)
	{
		if(inkDis >= 5.0f)
		{
			ink = false;
			inkDis = 0.0f;
		}
		else
		{
		inkDis += 0.1f;
		}
	}
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
		glTranslatef(objCam.mView.x,0.85f,objCam.mView.z);
		glRotatef(angle,0,1,0); //  rotate around center
		glTranslatef(-objCam.mView.x, 0, -objCam.mView.z); //move object to center
		glTranslatef(objCam.mView.x,0,objCam.mView.z);
		glScaled(0.3,0.3,0.3);
		glBindTexture(GL_TEXTURE_2D, currentTexture);
		squishy->draw();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(objCam.mView.x,0.50f,objCam.mView.z);
		glRotatef(angle-165.0f,0,1,0); 
		glTranslatef(inkDis*2, 0.0f, inkDis);
		glPushAttrib( GL_CURRENT_BIT );
		glColor4f(0,0,0,0.9f);
		glutSolidSphere(0.2f, 15,15);
		glPopAttrib();
	glPopMatrix();

	glPushMatrix();
		glTranslated(skybox, 0, skybox);
		Draw_Skybox(0,0,0,500, 15, 500);	
	glPopMatrix();
}

//Derived classes all have this class, it functions as the method that allows you to implement logic
void Player::Update()
{ 
	objCam.Mouse_Move(500, 500);
	inkUpdate();

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
		skybox += 0.001f;
	}
	else
	{
		skybox -= 0.001f;
	}
}

//Using this method you can process normalkeys
void Player::processNormalKeys(unsigned char key, int x, int y)
{
	switch (key) {
	case 'f' : //left
		objCam.Strafe_Camera(-CAMERASPEED);
		break;
	case 'h' : //right
		objCam.Strafe_Camera(CAMERASPEED);
		break;		
	case 't' : //up
		objCam.Move_Camera(CAMERASPEED);	
		break;
	case 'g' : //down
		objCam.Move_Camera(-CAMERASPEED);
		break;
	case 'r' : //rotate left
			angle+=5.0f;
		break;
	case 'y' : //rotate left
			angle-=5.0f;
		break;
	case 'q' : //shoot
			ink = true;
		break;
	case 'i' : //iron mode
		if (iron == false)
		{
			iron = true;
			currentTexture = ironTexture;
		}
		else if (iron == true)
		{
			iron = false;
			currentTexture = squishyTexture;
		}
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