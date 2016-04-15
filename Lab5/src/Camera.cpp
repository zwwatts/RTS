/*
 * Camera.cpp
 *
 *  Created on: Apr 15, 2016
 *      Author: se3910
 */

#include "Camera.h"
#include "../gpio/GPIO.h"
#include "pthread.h"
#include <iostream>
#include <mutex>
#include <opencv2/opencv.hpp> // C++ OpenCV include file

using namespace std;
using namespace cv;
using namespace Camera;

Camera::Camera() {
	// TODO Auto-generated constructor stub
	Camera::light = new GPIO(68);
	light->setDirection(GPIO::OUTPUT);
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}
void run(){
	while(isThreadRunning){
		Camera::cameraMutex.lock()
		capture.grab();
		Camera::cameraMutex.unlock();
	}

}
void shutdown(){
	Camera::isThreadRunning = false;
	exit(0);
}
void takePicture(int pictureType, int number){
	Camera::cameraMutex.lock();
	Camera::cameraLight->setValue(GPIO::HIGH);
	struct timespec grabstart, grabend, writeStart, writeEnd;
	clock_gettime( CLOCK_REALTIME, &grabstart );
	VideoCapture capture(0);

	capture.set(CV_CAP_PROP_FRAME_WIDTH, width);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, height);

	if(!capture.isOpened()){
	     cout << "Failed to connect to the camera." << endl;
	     exit(-1);
	    }
	 Mat frame, edges;

	 capture.retrieve(frame, 0);
	 clock_gettime(CLOCK_REALTIME, &grabend);
	 double difference = (grabend.tv_sec - grabstart.tv_sec) + (double)(grabend.tv_nsec - grabstart.tv_nsec)/1000000000.0d;
	 cout << "It took " << difference << " seconds to capture" << endl;
	 clock_gettime( CLOCK_REALTIME, &writeStart);

	 if(pictureType){
		 imwrite("capture"+number+".jpg", frame);
		 std:cout << "capture" << number << ".jpg" << std::endl;
	 }
	 else{
		 imwrite("capture"+number+".png", frame);
		 std:cout << "capture" << number << ".png" << std::endl;
	 }
	 clock_gettime( CLOCK_REALTIME, &writeEnd);

	 difference = (writeEnd.tv_sec - writeStart.tv_sec) + (double)(writeEnd.tv_nsec - writeStart.tv_nsec)/1000000000.0d;
	 cout << "It took " << difference << " seconds to capture" << endl;
	 Camera::cameraMutex.unlock();
}
void start(){
	std::thread cameraThread (run);
}

