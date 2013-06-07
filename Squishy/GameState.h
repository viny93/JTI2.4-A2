#pragma once
#include "RenderObject.h"
#include "main.h"

class GameState : RenderObject
{
public:
	GameState(void);
	~GameState(void);
	void Render();
	void die();
	void regen();
	void addPoint();
	void addPoints(int);
	int getPoints();
};