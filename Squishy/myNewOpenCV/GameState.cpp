#include "GameState.h"

int lives;
int points;

GameState::GameState(void)
{
	lives = 3;
	points = 0;
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

	void GameState::addPoints(int number)
	{
		points += number;
	}

	int GameState::getPoints()
	{
		return points;
	}