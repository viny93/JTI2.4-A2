#pragma once
#include "renderobject.h"
class HUD :
	public RenderObject
{
public:
	HUD(void);
	~HUD(void);

	void Render();
	void Update();
	void processNormalKeys(unsigned char key, int x, int y);
	void processSpecialKeys(int key, int xx, int yy);
	void DrawLives(int i);
	void drawGameOverScreen();
private:
	float ratio;
};

