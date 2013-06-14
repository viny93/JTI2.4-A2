#include<opencv\cv.h>

#pragma once
class Detection
{
public:
	Detection();
	cv::Point* detectTraps(void);
	cv::Point* detectEnemies(void);
	cv::Point* detectStartEnd(void);

private:
	void storeCoords(IplImage,int);	
	
};