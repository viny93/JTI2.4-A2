#pragma once
#include "renderobject.h"
#include <opencv\cv.h>

class World :
	public RenderObject
{
public:
	World(void);
	~World(void);

	void Render();
	void Update();
	void processNormalKeys(unsigned char key, int x, int y);
	void processSpecialKeys(int key, int xx, int yy);
	cv::Point getBottomLeft(void);
};

