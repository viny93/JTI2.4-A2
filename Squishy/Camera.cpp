#include "main.h"  
#include "stb_image.h"
#include "World.h"
#include <vector>
#include<opencv\cv.h>

#include <iostream>

bool CCamera::checkCollisionWithCubes(int x, int z)
{
	return true; //Comment this to activate collision

	std::vector<cv::Point> coordsListWallsForCamera;
	coordsListWallsForCamera = World::getListOfCubes();
	float steppedX, steppedZ, deltaX, deltaZ;
	cv::Point currentPoint;
	
	float correction = 512.0f / 60.0f;
	float correctedXView = (mView.x + 30.0f) * correction;
	float correctedZView = (mView.z + 60.0f) * correction;
	float correctedXMoved = (x + 30.0f) * correction;
	float correctedZMoved = (z + 60.0f) * correction;
	
	for(int i = 0; i < coordsListWallsForCamera.size(); i++)
	{
		currentPoint = coordsListWallsForCamera[i];
		deltaX = abs(correctedXMoved - currentPoint.x);
		deltaZ = abs(correctedZMoved - currentPoint.y);

		if(deltaX < 10.0f && deltaZ < 10.0f)
		{
			return false;
		}
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//										THE CCAMERA POSITION CAMERA
/////////////////////////////////////////////////////////////////////////////////////////////////
void CCamera::Position_Camera(float pos_x,  float pos_y,  float pos_z,
							  float view_x, float view_y, float view_z,
							  float up_x,   float up_y,   float up_z)
{
	mPos	= tVector3(pos_x,  pos_y,  pos_z ); // set position
	mView	= tVector3(view_x, view_y, view_z); // set view
	mUp		= tVector3(up_x,   up_y,   up_z  ); // set the up vector	
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//										THE CCAMERA MOVE CAMERA
/////////////////////////////////////////////////////////////////////////////////////////////////
void CCamera::Move_Camera(float speed)
{
	tVector3 vVector = mView - mPos;	// Get the view vector
	
	float moveX = mView.x + vVector.x * speed;
	float moveZ = mView.z + vVector.z * speed;
	if(checkCollisionWithCubes(moveX, moveZ))
	{
		mPos.x  = mPos.x  + vVector.x * speed;
		mPos.z  = mPos.z  + vVector.z * speed;
		mView.x = moveX;
		mView.z = moveZ;
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////
//										THE CCAMERA ROTATE VIEW
/////////////////////////////////////////////////////////////////////////////////////////////////
void CCamera::Rotate_View(float speed)
{
	tVector3 vVector = mView - mPos;	// Get the view vector

	mView.z = (float)(mPos.z + sin(speed)*vVector.x + cos(speed)*vVector.z);
	mView.x = (float)(mPos.x + cos(speed)*vVector.x - sin(speed)*vVector.z);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//										THE CCAMERA ROTATE POSITION
/////////////////////////////////////////////////////////////////////////////////////////////////
void CCamera::Rotate_Position(float speed)
{	
	tVector3 vVector = mPos - mView;

	mPos.z = (float)(mView.z + sin(speed)*vVector.x + cos(speed)*vVector.z);
	mPos.x = (float)(mView.x + cos(speed)*vVector.x - sin(speed)*vVector.z);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//										THE CCAMERA STRAFE CAMERA
/////////////////////////////////////////////////////////////////////////////////////////////////
void CCamera::Strafe_Camera(float speed)
{
	tVector3 vVector = mView - mPos;	// Get the view vector
	tVector3 vOrthoVector;              // Orthogonal vector for the view vector

	vOrthoVector.x = -vVector.z;
	vOrthoVector.z =  vVector.x;

	// left positive cameraspeed and right negative -cameraspeed.
	mPos.x  = mPos.x  + vOrthoVector.x * speed;
	mPos.z  = mPos.z  + vOrthoVector.z * speed;
	mView.x = mView.x + vOrthoVector.x * speed;
	mView.z = mView.z + vOrthoVector.z * speed;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//										THE CCAMERA MOUSE MOVE
/////////////////////////////////////////////////////////////////////////////////////////////////
void CCamera::Mouse_Move( int wndWidth, int wndHeight )
{
	POINT mousePos;	
	int mid_x = wndWidth  >> 1;	
	int mid_y = wndHeight >> 1;	
	float angle_y  = 0.0f;				
	float angle_z  = 0.0f;							
	
	GetCursorPos(&mousePos);	// Get the mouse cursor 2D x,y position					
	
	if( (mousePos.x == mid_x) && (mousePos.y == mid_y) ) return;

	SetCursorPos(mid_x, mid_y);	// Set the mouse cursor in the center of the window						

	// Get the direction from the mouse cursor, set a resonable maneuvering speed
	angle_y = (float)( (mid_x - mousePos.x) ) / 1000;		
	angle_z = (float)( (mid_y - mousePos.y) ) / 1000;

	// The higher the value is the faster the camera looks around.
	mView.y += angle_z * 2;

	// limit the rotation around the x-axis
	if(mView.y > 3.5f)		mView.y = 3.5f;
	if(mView.y < 0.4f)		mView.y = 0.4f;
	
	Rotate_Position(-angle_y);
}

GLuint CCamera::loadTexture(char *filename)
{
	int x, y, depth;
	unsigned char *data = stbi_load(filename, &x, &y, &depth, 4);

	GLuint textureId;
	glGenTextures( 1, &textureId );

	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x,y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);

	return textureId;
}

