#pragma once
#include "RenderObject.h"
#include "main.h"



class GameState
{
public:
	GameState(void);
	~GameState(void);
	void die();
	void regen();
	void addPoint();
	void winGame();
	void addPoints(int);
	int getPoints();
	int getLives();
	bool getWin();
};