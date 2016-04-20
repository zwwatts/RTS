/*
 * Camera.cpp
 *
 *  Created on: Apr 15, 2016
 *      Author: sorianog, wattsz
 */

#include "Camera.h"
#include "GPIO.h"
#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <opencv2/opencv.hpp> // C++ OpenCV include file


using namespace cv;
using namespace std;
using namespace exploringBB;

/**
 * Constructor for Camera. Initialize variables for camera
 *
 * @param port - USB port for camera
 * @param pin - GPIO pin for LED
 * @param width - width for image
 * @param height - height for image
 */
Camera::Camera(int port, int pin, int width, int height) {
	// TODO Auto-generated constructor stub
	Camera::cameraLight = new GPIO(pin);
	Camera::cameraLight->setDirection(GPIO::OUTPUT);
	Camera::capture = new VideoCapture(port);
	capture->set(CV_CAP_PROP_FRAME_HEIGHT, height);
	capture->set(CV_CAP_PROP_FRAME_WIDTH, width);
	Camera::isThreadRunning = true;
}
/*Camera::Camera(Camera& c){

};*/
Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

/**
 * Keep grabbing frames from the camera while the thread is still running
 */
void Camera::run(){
	std::cout << "grabbing from camera..." << std::endl;
	while(isThreadRunning){
		cameraMutex.lock();
		capture->grab();
		cameraMutex.unlock();
	}
}

/**
 * Set the thread running flag to false and join the cameraThread
 */
void Camera::shutdown(){
	isThreadRunning = false;
	cameraThread.join();
	exit(0);
}
/**
 * Take a picture and save it.
 * Print out the name of the picture and the times it took to retrieve & save it.
 *
 * @param pictureType - format of picture (PNG, JPG)
 * @param number - id for picture
 */
void Camera::takePicture(int pictureType, int number){
	cameraMutex.lock();
	cameraLight->setValue(GPIO::HIGH);
	struct timespec grabstart, grabend, writeStart, writeEnd;
	clock_gettime( CLOCK_REALTIME, &grabstart );


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
	 cameraLight->setValue(GPIO::LOW);
	 if(pictureType){
		 imwrite("capture"+std::to_string(number)+".jpg", frame);
		 std::cout << "capture" << number << ".jpg" << std::endl;
	 }
	 else{
		 imwrite("capture"+std::to_string(number)+".png", frame);
		 std::cout << "capture" << number << ".png" << std::endl;
	 }
	 clock_gettime( CLOCK_REALTIME, &writeEnd);

	 difference = (writeEnd.tv_sec - writeStart.tv_sec) + (double)(writeEnd.tv_nsec - writeStart.tv_nsec)/1000000000.0d;
	 std::cout << "It took " << difference << " seconds to write" << std::endl;
	 cameraMutex.unlock();
}

/**
 * Create the thread that will execute the run method
 */
void Camera::start(){
        //pthread_t thread;
	cameraThread = std::thread(&Camera::run, this);
	//pthread_create(&thread, NULL, run, (void *)NULL);
}

