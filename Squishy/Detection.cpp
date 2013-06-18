#include"Detection.h"
#include<opencv\cv.h>
#include<opencv\highgui.h>
#include "BlobResult.h"

using namespace cv;

VideoCapture cap;
cv::Mat image;
CBlobResult blobs, whiteBlobs;
IplImage blobimage;
std::vector<cv::Point> enemycoords, trapcoords,startendcoords;

Detection::Detection()
{
	image = cv::imread("background.png");	
}

std::vector<cv::Point> Detection::detectEnemies()
{	
	cv::Mat hsv,eroded,thresholded,closed;

	//Omzetten naar HSV plaatje.
	cvtColor(image,hsv,CV_BGR2HSV);	
	//Threshold
	cv::inRange(hsv,cv::Scalar(0,173,250),cv::Scalar(19,255,255),thresholded);
	//Closing
	Mat closingmat(25,25,CV_8U,cv::Scalar(1));
	cv::morphologyEx(thresholded,closed,cv::MORPH_CLOSE,closingmat);
	//Erosion
	cv::erode(closed,eroded,cv::Mat(),cv::Point(-1,-1),1);	

	blobimage = eroded;
	storeCoords(blobimage,1);

	return enemycoords;
}

std::vector<cv::Point> Detection::detectTraps()
{
	cv::Mat hsv,eroded,thresholded,closed;

	//Omzetten naar HSV plaatje.
	cvtColor(image,hsv,CV_BGR2HSV);	
	//Threshold
	cv::inRange(hsv,cv::Scalar(100,10,161),cv::Scalar(145,159,225),thresholded);
	//Closing
	Mat closingmat(25,25,CV_8U,cv::Scalar(1));
	cv::morphologyEx(thresholded,closed,cv::MORPH_CLOSE,closingmat);
	//Erosion
	cv::erode(closed,eroded,cv::Mat(),cv::Point(-1,-1),1);	

	blobimage = eroded;
	storeCoords(blobimage,2);

	return trapcoords;
}

std::vector<cv::Point> Detection::detectStartEnd()
{
	cv::Mat hsv,eroded,thresholded,closed;

	//Omzetten naar HSV plaatje.
	cvtColor(image,hsv,CV_BGR2HSV);	
	//Threshold
	cv::inRange(hsv,cv::Scalar(25,160,235),cv::Scalar(40,255,255),thresholded);
	//Closing
	Mat closingmat(25,25,CV_8U,cv::Scalar(1));
	cv::morphologyEx(thresholded,closed,cv::MORPH_CLOSE,closingmat);
	//Erosion
	cv::erode(closed,eroded,cv::Mat(),cv::Point(-1,-1),1);	

	blobimage = eroded;
	storeCoords(blobimage,3);	

	return startendcoords;
}

/**
* Stores the middle coordinates of every object in the coordinates array.
* @param blobimage: The image with the blobs
blobtype: 1: Enemy, 2: Trap, 3: Start/End
* @author Ricardo de Klerk
**/
void Detection::storeCoords(IplImage blobimage,int blobtype)
{
	blobs = CBlobResult(new IplImage(blobimage), NULL, 0);	
	CBlob *currentBlob;
	cv::Point currentcoords;

	for (int i = 0; i < blobs.GetNumBlobs(); i++ )
	{
		currentBlob = blobs.GetBlob(i);
		currentcoords.x = (currentBlob->MaxX() + currentBlob->MinX())/2;
		currentcoords.y = (currentBlob->MaxY() + currentBlob->MinY())/2;

		if(blobtype == 1)
			enemycoords.push_back(currentcoords);
		if(blobtype == 2)
			trapcoords.push_back(currentcoords);
		if(blobtype == 3)
			startendcoords.push_back(currentcoords);
	}

}