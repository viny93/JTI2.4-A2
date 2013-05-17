/* "Hello World" met OpenCV.
	Preconditie: Er is tenminste 1 camera geinstalleerd en actief.
	Dit programma toont real-time de beelden van camera 0.
*/


#include<opencv\cv.h>
#include<opencv\highgui.h>

using namespace cv;

int main() {
	// create matrix to store image
	Mat image;

	// initialize capture
	VideoCapture cap;
	cap.open(0);

	// create window to show image
	namedWindow("window",1);
	while(1) {

		// cop webcam stream to image
		cap >> image;

		// print image to screen
		imshow("window",image);

		// delay 33 ms
		waitKey(33);
	}
	return 0;
}