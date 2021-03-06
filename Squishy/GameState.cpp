#include "GameState.h"
#include "main.h"
#include <GL/glut.h>

int points;
bool win;
int lives = 3;
//int gamestate;
GLuint lifeTexture;

GameState::GameState(void)
{
	lives = 3;
	points = 0;
	win = false;
	//lifeTexture  =  loadTexture("Squishy.png");
}


GameState::~GameState(void)
{

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
	
	void GameState::winGame()
	{
		win = true;
	}

	void GameState::addPoints(int number)
	{
		points += number;
	}

	int GameState::getPoints()
	{
		return points;
	}

	int GameState::getLives()
	{
		return lives;
	}

	bool GameState::getWin()
	{
		return win;
	}