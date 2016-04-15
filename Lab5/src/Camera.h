/*
 * Camera.h
 *
 *  Created on: Apr 15, 2016
 *      Author: se3910
 */

#ifndef SRC_CAMERA_H_
#define SRC_CAMERA_H_
#include "../gpio/GPIO.h"
#include "pthread.h"
#include <iostream>
#include<opencv2/opencv.hpp> // C++ OpenCV include file
using namespace std;
using namespace cv;

class Camera {
public:
	Camera(Camera& c);
	Camera(int port, int pinNumber, int width, int height);
	virtual ~Camera();
	void run();
	void shutdown();
	void start();
	void takePicture(int pictureType, int number);
private:
	GPIO* cameraLight;
	std::mutex cameraMutex;
	VideoCapture* capture;
	int height;
	int width;
	bool isThreadRunning;
};

#endif /* SRC_CAMERA_H_ */