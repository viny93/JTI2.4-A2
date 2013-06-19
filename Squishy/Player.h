#pragma once
#include<opencv\cv.h>
#include "renderobject.h"
#include "GameState.h"

class Player :
	public RenderObject
{
public:
	Player(GameState *state);
	~Player(void);

	void SetPosition(cv::Point coordinates,cv::Point worldcoordinates);
	void Render();
	void Update();
	void processNormalKeys(unsigned char key, int x, int y);
	void processSpecialKeys(int key, int xx, int yy);
};

