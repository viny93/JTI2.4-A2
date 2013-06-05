#pragma once
#include "renderobject.h"

class Enemy : public RenderObject
{
public:
	Enemy(void);
	~Enemy(void);

	void Render();
	void Update();
	void processNormalKeys(unsigned char key, int x, int y);
	void processSpecialKeys(int key, int xx, int yy);
};

