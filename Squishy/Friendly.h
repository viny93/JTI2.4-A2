#include<opencv\cv.h>
#include "RenderObject.h"

#pragma once
class Friendly : public RenderObject
{
public:
	Friendly(cv::Point,cv::Point);
	void activate(void);
	void Render(void);
	void Update(void);

private:
	cv::Point coordinates;
	cv::Point worldcoordinates;
};