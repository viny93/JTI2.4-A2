#include<opencv\cv.h>
#include<opencv\highgui.h>
#include<opencv\BlobResult.h>

using namespace cv;

Mat image,hsv,inverted,thresholded,eroded,closed;
CBlobResult blobs, whiteBlobs;
CBlob *currentBlob;
Point currentcoords;
Point coordinates[10];


/**
* Detects the colored objects in image.
* @author Ricardo de Klerk
**/
void detectObjects()
{					
		//Omzetten naar HSV plaatje.
		cvtColor(image,hsv,CV_BGR2HSV);			
		//Threshold
		cv::inRange(hsv,cv::Scalar(30,80,110),cv::Scalar(120,255,255),thresholded); 
		//Closing
		Mat closingmat(25,25,CV_8U,cv::Scalar(1));
		cv::morphologyEx(thresholded,closed,cv::MORPH_CLOSE,closingmat);
		//Erosion
		cv::erode(closed,eroded,cv::Mat(),cv::Point(-1,-1),1);	
}

/**
* Stores the middle coordinates of every object in the coordinates array.
* @author Ricardo de Klerk
**/
void storeCoords()
{
	blobs = CBlobResult(new IplImage(eroded), NULL, 0);	

	for (int i = 0; i < blobs.GetNumBlobs(); i++ )
	{
        currentBlob = blobs.GetBlob(i);
        currentcoords.x = (currentBlob->MaxX() + currentBlob->MinX())/2;
		currentcoords.y = (currentBlob->MaxY() + currentBlob->MinY())/2;
		coordinates[i] = currentcoords;
	}
}

int main() {	
	// initialize capture
	VideoCapture cap;	
	cap.open(0);

	// create window to show image
	namedWindow("window",1);
	while(1) {		
		// cop webcam stream to image
		cap >> image;
		detectObjects();
		storeCoords();
		// print image to screen
		imshow("window",eroded);
		
		waitKey(33);
	}

	return 0;
}