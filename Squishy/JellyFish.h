#pragma once
#include "renderobject.h"
class JellyFish :
	public RenderObject
{
public:
	JellyFish(void);
	~JellyFish(void);

	void Render();
	void Update();
	void processNormalKeys(unsigned char key, int x, int y);
	void processSpecialKeys(int key, int xx, int yy);
};

