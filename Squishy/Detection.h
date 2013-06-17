#include<opencv\cv.h>

#pragma once
class Detection
{
public:
	Detection();
	std::vector<cv::Point> detectTraps(void);
	std::vector<cv::Point> detectEnemies(void);
	std::vector<cv::Point> detectStartEnd(void);

private:
	void storeCoords(IplImage,int);	
	
};