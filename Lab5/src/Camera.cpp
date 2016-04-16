/*
 * Camera.cpp
 *
 *  Created on: Apr 15, 2016
 *      Author: sorianog, wattsz
 */

#include "Camera.h"
#include "gpio/GPIO.h"
#include <iostream>
#include <mutex>
#include <thread>
#include <opencv2/opencv.hpp> // C++ OpenCV include file


using namespace cv;
using namespace std;
using namespace exploringBB;

Camera::Camera(int port, int pin, int width, int height) {
	// TODO Auto-generated constructor stub
	Camera::cameraLight = new GPIO(pin);
	Camera::cameraLight->setDirection(GPIO::OUTPUT);
	Camera::capture = VideoCapture(port);

}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}
void Camera::run(){

	while(isThreadRunning){
		Camera::cameraMutex.lock();
		capture.grab();
		cameraMutex.unlock();
	}

}
void Camera::shutdown(){
	isThreadRunning = false;
	exit(0);
}
void Camera::takePicture(int pictureType, int number){
	cameraMutex.lock();
	cameraLight->setValue(GPIO::HIGH);
	struct timespec grabstart, grabend, writeStart, writeEnd;
	clock_gettime( CLOCK_REALTIME, &grabstart );

	capture->set(CV_CAP_PROP_FRAME_WIDTH, width);
	capture->set(CV_CAP_PROP_FRAME_HEIGHT, height);

	if(!capture->isOpened()){
	     std::cout << "Failed to connect to the camera." << std::endl;
	     exit(-1);
	    }
	 Mat frame, edges;

	 capture->retrieve(frame, 0);
	 clock_gettime(CLOCK_REALTIME, &grabend);
	 double difference = (grabend.tv_sec - grabstart.tv_sec) + (double)(grabend.tv_nsec - grabstart.tv_nsec)/1000000000.0d;
	 std::cout << "It took " << difference << " seconds to capture" << std::endl;
	 clock_gettime( CLOCK_REALTIME, &writeStart);

	 if(pictureType){
		 imwrite("capture"+number+".jpg", frame);
		 std::cout << "capture" << number << ".jpg" << std::endl;
	 }
	 else{
		 imwrite("capture"+number+".png", frame);
		 std::cout << "capture" << number << ".png" << std::endl;
	 }
	 clock_gettime( CLOCK_REALTIME, &writeEnd);

	 difference = (writeEnd.tv_sec - writeStart.tv_sec) + (double)(writeEnd.tv_nsec - writeStart.tv_nsec)/1000000000.0d;
	 std::cout << "It took " << difference << " seconds to capture" << std::endl;
	 cameraMutex.unlock();
}
void Camera::start(){
	std::thread cameraThread (Camera::run);
}

