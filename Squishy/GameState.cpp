#include "GameState.h"
#include "main.h"
#include <GL/glut.h>

int lives;
int points;
GLuint lifeTexture;

GameState::GameState(void)
{
	lives = 3;
	points = 0;
	//lifeTexture  =  loadTexture("Squishy.png");
}


GameState::~GameState(void)
{

}

void GameState::Render()
{
	glBindTexture( GL_TEXTURE_2D, lifeTexture );

		glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, 800, 600, 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();        ----Not sure if I need this
	glLoadIdentity();
	glDisable(GL_CULL_FACE);

	glClear(GL_DEPTH_BUFFER_BIT);

	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0);
		glVertex2f(0.0, 0.0);
		glVertex2f(10.0, 0.0);
		glVertex2f(10.0, 10.0);
		glVertex2f(0.0, 100.0);
	glEnd();

	// Making sure we can render 3d again
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glutSwapBuffers();
}

void GameState::die()
	{
		lives--;
		if(lives >= 0)
		{
			//respawn
		}
		if(lives < 0)
		{
			//open game over screen
		}
	}

	void GameState::regen()
	{
		lives++;
	}

	void GameState::addPoint()
	{
		points++;
	}

	void GameState::addPoints(int number)
	{
		points += number;
	}

	int GameState::getPoints()
	{
		return points;
	}