#pragma once
#include "renderobject.h"
class Pyramid :
	public RenderObject
{
public:
	Pyramid(void);
	~Pyramid(void);

	void Render();
	void Update();
	void processNormalKeys(unsigned char key, int x, int y);
	void processSpecialKeys(int key, int xx, int yy);
};

