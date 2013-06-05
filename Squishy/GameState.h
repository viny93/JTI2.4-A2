#pragma once
class GameState
{
public:
	GameState(void);
	~GameState(void);
	void die();
	void regen();
	void addPoint();
	void addPoints(int);
	int getPoints();

};