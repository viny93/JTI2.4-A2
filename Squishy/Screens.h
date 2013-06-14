#include "RenderObject.h"
#include "GameState.h"
#pragma once

class Screens :
	public RenderObject
{
public:
	Screens(void);
	~Screens(void);
	void writeString(char* string, int x, int y, void* font);
	void setOrthographicProjection();
	void resetPerspectiveProjection();
	void Render();
	void Update();
	void DrawStartScreen();
	void DrawGameOverScreen();
	void DrawYayScreen();
};

