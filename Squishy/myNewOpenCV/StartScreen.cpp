#include "StartScreen.h"
#include <GL/glut.h>
#include <GL/GL.h>
#include<opencv\cv.h>
#include<opencv\highgui.h>
//#include<BlobResult.h>
#include <windows.h>
#include "math.h"
#include "Camera.h"
#include "stb_image.h"
#include <mmsystem.h>
#include <process.h>   

float red=1.0f, blue=1.0f, green=1.0f;
float lx=0.0f,lz=-1.0f;
float x=0.0f,z=2.5f;

//light variables
float light_diffuse[] = {1.0, 1.0, 1.0, 1.0}; 
float light_position[] = {x, 1.0, z, 0.0};
static float amb[] =  {0.4, 0.4, 0.4, 0.0};
static float dif[] =  {1.0, 1.0, 1.0, 0.0};

float FogCol[3]={0.0f,0.0f,0.0f};

CCamera objCamera; 

GLuint floorTexture;
GLuint introTexture;
int gamestate = 1;
LPCSTR soundToPlay;

void playBackground(void *arg)
{
	PlaySound(soundToPlay, NULL, SND_LOOP);
}

void startSound(LPCSTR pszSound, int soundLenght)
{
	soundToPlay = pszSound;
	_beginthread(playBackground, 0, (void*)12 );
}

void Draw_Character() 
{
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
}

void Draw_World()
{
		glBindTexture( GL_TEXTURE_2D, floorTexture );
		glBegin( GL_QUADS );
	
		glVertex3f(-100, 0, -200.0);
		glTexCoord2f(0, 0);
		glVertex3f(100, 0, -200.0);
		glTexCoord2f(0, 1);
		glVertex3f(100.0, 0, 200.0);
		glTexCoord2f(1, 1);
		glVertex3f(-100.0, 0, 200.0);
		glTexCoord2f(1, 0);

		glEnd();
}

cv::Mat texturizeBackground(int cam)
{
	cv::VideoCapture cap(cam);
	cv::Mat save_img;
	cv::Mat biggerImage;
	cv::Size size(1024, 512);
	
	cap >> save_img;
	cv::resize(save_img, biggerImage, size, 0, 0,1);

	if(biggerImage.empty())
	{
	 std::cerr << "Something is wrong with the webcam, could not get frame." << std::endl;
	}
	imwrite("background.png", biggerImage); 

	return biggerImage;
}

GLuint loadTexture(char *filename)
{
        int x, y, depth;
        unsigned char *data = stbi_load(filename, &x, &y, &depth, 4);

        GLuint textureId;
        // allocate a texture name
        glGenTextures( 1, &textureId );
         
        glBindTexture(GL_TEXTURE_2D, textureId);

        glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

        // the texture wraps over at the edges (repeat)
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x,y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);

        return textureId;
}

void Render()
{
	objCamera.Mouse_Move(500, 500);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	glEnable(GL_TEXTURE_2D);

	if(gamestate == 1) //launch menu
	{
		gluLookAt(  x, 1.0f, z,
                    x+lx, 1.0f,  z+lz,
                    0.0f, 1.0f,  0.0f);
		startSound("C:/kirby.wav", 100);
		glTranslatef(1.0f, 2.0f, 0.0f);
		gluLookAt(  x, 1.0f, z,
                    x+lx, 1.0f,  z+lz,
                    0.0f, 1.0f,  0.0f);

		glBindTexture( GL_TEXTURE_2D, introTexture );

		glBegin( GL_QUADS );
	
		glVertex2f(-10,-5.0);
		glTexCoord2f(1, 1);
		glVertex2f(10,-5.0);
		glTexCoord2f(1, 0);
		glVertex2f(10.0, 5.0);
		glTexCoord2f(0, 0);
		glVertex2f(-10.0, 5.0);
		glTexCoord2f(0, 1);

		glEnd();
	}

	else //Render game
	{
		gluLookAt(objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,	
			  objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,	
			  objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);	

		glPushMatrix();

		glTranslatef(objCamera.mView.x,0.0f,objCamera.mView.z);
		Draw_Character();
		glPopMatrix();

		glPushMatrix();
		Draw_Grid(); //testing only
		Draw_World();
		glPopMatrix();
	}

	glutSwapBuffers();
}

void changeSize(int w, int h) 
{
        // Prevent a divide by zero, when window is too short
        // (you cant make a window of zero width).
        if(h == 0)
                h = 1;
        float ratio = 1.0* w / h;

        // Use the Projection Matrix
        glMatrixMode(GL_PROJECTION);

        // Reset Matrix
        glLoadIdentity();

        // Set the viewport to be the entire window
        glViewport(0, 0, w, h);

        // Set the correct perspective.
        gluPerspective(90,ratio,1,1000);

        // Get Back to the Modelview
        glMatrixMode(GL_MODELVIEW);
}

void processNormalKeys(unsigned char key, int x, int y) 
{
	if(gamestate == 1)
	{
        switch (key) {
					case 32 :
						gamestate = 0;
						break;
		}
	}
}

void processSpecialKeys(int key, int xx, int yy) 
{

        float fraction = 0.1f;
		if(gamestate == 1)
		{
			//Menu behaviour
		}
		else
		{
			switch (key) {
					case GLUT_KEY_LEFT :
							objCamera.Strafe_Camera(-CAMERASPEED);
							break;
					case GLUT_KEY_RIGHT :
							objCamera.Strafe_Camera(CAMERASPEED);
							break;
					case GLUT_KEY_UP :
							objCamera.Move_Camera(CAMERASPEED);	
							break;
					case GLUT_KEY_DOWN :
							objCamera.Move_Camera(-CAMERASPEED);	
							break;
			}
        }
}

void Draw_Grid()
{																	

	for(float i = -500; i <= 500; i += 5)
	{
		glBegin(GL_LINES);
			glColor3ub(150, 190, 150);							
			glVertex3f(-500, 0, i);									
			glVertex3f(500, 0, i);

			glVertex3f(i, 0, -500);								
			glVertex3f(i, 0, 500);
		glEnd();
	}
}

StartScreen::StartScreen(int argc, char **argv) 
{
		objCamera.Position_Camera(0, 1.5f, 4.0f,	0, 1.5f, 0,   0, 1.0f, 0);

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
        glutInitWindowPosition(0,0);
        glutInitWindowSize(1920,1080);
        glutCreateWindow("Squishy!?");
		glutFullScreen();

        // register callbacks
        glutDisplayFunc(Render);
        glutReshapeFunc(changeSize);
        glutIdleFunc(Render);

        glEnable(GL_DEPTH_TEST);

		glEnable(GL_FOG);
		glFogfv(GL_FOG_COLOR,FogCol);
		glFogi(GL_FOG_MODE, GL_EXP2);
		glFogf(GL_FOG_DENSITY, 0.02f);
		glHint(GL_FOG_HINT, GL_NICEST);

        glutKeyboardFunc(processNormalKeys);

        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);

        glEnable(GL_COLOR_MATERIAL);
		glutSetCursor(GLUT_CURSOR_NONE); 
        
        //loading textures
    	texturizeBackground(0);
		floorTexture  =  loadTexture("background.png");
		//floorTexture  =  loadTexture("grassTexture.png"); //testing only
		introTexture  =  loadTexture("Intro.png");

        glutMainLoop();
}

StartScreen::~StartScreen(void)
{
}