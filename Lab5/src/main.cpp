/*
 * main.cpp
 *
 *  Created on: Apr 15, 2016
 *      Author: sorianog, wattsz
 */
#include "Camera.h"
#include "gpio/GPIO.h"
#include "pthread.h"
#include <iostream>
#include <mutex>
#include <opencv2/opencv.hpp> // C++ OpenCV include file

using namespace exploringBB;
int numCaptures;

int button1Pressed(int var);
int button2Pressed(int var);
Camera camera;
int main(int argc, char*  argv[]){
	if(argc < 6 || argc > 6){
		std::cout << "selfie button1 button2 LED width height" << std::endl;
		exit(0);
	}
	numCaptures = 0;
	camera(0, (int)argv[3], (int)argv[4], (int)argv[5]);
	GPIO* button1 = new GPIO((int)argv[1]); //button 1 png
	button1->setDirection(GPIO::INPUT);
	button1->setEdgeType(GPIO::FALLING);
	button1->waitForEdge(button1Pressed);
	GPIO* button2 = new GPIO((int)argv[2]); //button 2 jpg
	button2->setDirection(GPIO::INPUT);
	button2->setEdgeType(GPIO::FALLING);
	button2->waitForEdge(button2Pressed);
	camera.start();
	bool running = true;
	while(running){
		std::string input;
		std::cin >> input;
		if(input == "quit"){
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

