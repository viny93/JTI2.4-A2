#include<opencv\cv.h>
#include "RenderObject.h"

#pragma once
class Trap : public RenderObject
{
public:
	Trap(cv::Point,cv::Point);
	void activate(void);
	void Render(void);
	void Update(void);

private:
	cv::Point coordinates;
	cv::Point worldcoordinates;
};