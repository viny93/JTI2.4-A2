#include <GL/glut.h>
#include <GL/GL.h>
#include<opencv\cv.h>
#include<opencv\highgui.h>
#include<BlobResult.h>
#include <windows.h>
#include "math.h"
#include "stb_image.h"
#include <mmsystem.h>
#include <process.h>     

// all variables initialized to 1.0, meaning
// the trihangle will initially be white
float red=1.0f, blue=1.0f, green=1.0f;
// hangle of rotation for the camera direction
float hangle=0.0;
float vangle=0.0;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f,z=2.5f;
//light variables
float light_diffuse[] = {1.0, 1.0, 1.0, 1.0}; 
float light_position[] = {x, 1.0, z, 0.0};
static float amb[] =  {0.4, 0.4, 0.4, 0.0};
static float dif[] =  {1.0, 1.0, 1.0, 0.0};

float FogCol[3]={0.0f,0.0f,0.0f};

GLuint floorTexture;
GLuint introTexture;
int gamestate = 1;
LPCSTR soundToPlay;
int soundLenght;

void playBackground(void *arg)
{
	PlaySound(soundToPlay, NULL, SND_LOOP);
}

void  startSound(LPCSTR pszSound, int soundLenght)
{
	soundToPlay = pszSound;
	_beginthread(playBackground, 0, (void*)12 );
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

void renderScene(void) 
{
    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();
    // Set the camera
    gluLookAt(      x, 1.0f, z,
                    x+lx, 1.0f,  z+lz,
                    0.0f, 1.0f,  0.0f);
    glRotatef(vangle, 1.0f, 0.0f, 0.0f);
    glRotatef(hangle, 0.0f, 1.0f, 0.0f);

	glEnable(GL_TEXTURE_2D);

	if(gamestate == 1) //launch menu
	{
		startSound("C:/kirby.wav", 100);
		glTranslatef(1.0f, 2.0f, 0.0f);
		gluLookAt(      x, 1.0f, z,
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
		gluLookAt(  x, 1.0f, z,
                    x+lx, 1.0f,  z+lz,
                    0.0f, 1.0f,  0.0f);
		glRotatef(vangle, 1.0f, 0.0f, 0.0f);
		glRotatef(hangle, 0.0f, 1.0f, 0.0f);

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
							//hangle -= 0.5f;
							lx = sin(hangle);
							lz = -cos(hangle);
							break;
					case GLUT_KEY_RIGHT :
							//hangle += 0.5f;
							lx = sin(hangle);
							lz = -cos(hangle);
							break;
					case GLUT_KEY_UP :
							//vangle -= 0.5f;
							x += lx * fraction;
							z += lz * fraction;
							break;
					case GLUT_KEY_DOWN :
							//vangle += 0.5f;
					        x -= lx * fraction;
							z -= lz * fraction;
							break;
			}
        }
}

int main(int argc, char **argv) 
{

        // init GLUT and create window
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
        glutInitWindowPosition(0,0);
        glutInitWindowSize(1920,1080);
        glutCreateWindow("Squishy!?");
		glutFullScreen();

        // register callbacks
        glutDisplayFunc(renderScene);
        glutReshapeFunc(changeSize);
        glutIdleFunc(renderScene);
        // OpenGL init
        glEnable(GL_DEPTH_TEST);

		glEnable(GL_FOG);
		glFogfv(GL_FOG_COLOR,FogCol);
		glFogi(GL_FOG_MODE, GL_EXP2);
		glFogf(GL_FOG_DENSITY, 0.02f);
		glHint(GL_FOG_HINT, GL_NICEST);

        glutKeyboardFunc(processNormalKeys);
        glutSpecialFunc(processSpecialKeys);

        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);

        glEnable(GL_COLOR_MATERIAL);
        
        //loading textures
    	texturizeBackground(2);
		floorTexture  =  loadTexture("background.png");
		introTexture  =  loadTexture("Intro.png");

        // enter GLUT event processing cycle
        glutMainLoop();

        return 1;
}