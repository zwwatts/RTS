/*
 * main.cpp
 *
 *  Created on: Apr 15, 2016
 *      Author: se3910
 */
#include "Camera.h"
#include "gpio/GPIO.h"
#include "pthread.h"
#include <iostream>
#include <mutex>
#include <opencv2/opencv.hpp> // C++ OpenCV include file

using namespace exploringBB;
Camera camera;
int numCaptures;

int main(char*  argv[], int argc){
	if(argc < 6 || argc > 6){
		std::cout << "selfie button1 button2 LED width height" << std::endl;
		exit(0);
	}
	numCaptures = 0;
	camera = new Camera(0, argv[3], argv[4], argv[5]);
	GPIO* button1 = new GPIO(argv[1]); //button 1 png
	button1->setDirection(GPIO::INPUT);
	button1->setEdgeType(GPIO::FALLING);
	button1->waitForEdge(button1Pressed);
	GPIO* button2 = new GPIO(argv[2]); //button 2 jpg
	button2->setDirection(GPIO::INPUT);
	button2->setEdgeType(GPIO::FALLING);
	button2->waitForEdge(button2Pressed);
	camera.start();
	bool running = true;
	while(running){
		std::string input;
		std::cin >> input;
		if(input == 'quit'){
			std::cout << "shutting camera down" << std::endl;
			camera.shutdown();
		}
	}

}
int button1Pressed(int var){
	camera.takePicture(0, numCaptures);
	numCaptures++;
	return 0;
}
int button2Pressed(int var){
	camera.takePicture(1, numCaptures);
	numCaptures++;
	return 0;
}

