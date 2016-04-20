/*
 * main.cpp
 *
 *  Created on: Apr 15, 2016
 *      Author: sorianog, wattsz
 */
#include "Camera.h"
#include "GPIO.h"
#include "pthread.h"
#include <iostream>
#include <mutex>
#include <opencv2/opencv.hpp> // C++ OpenCV include file

using namespace exploringBB;
int numCaptures;
Camera* camera = NULL;
int button1Pressed(int var);
int button2Pressed(int var);

int main(int argc, char *argv[]){
	if(argc < 6 || argc > 6){
		std::cout << "selfie button1 button2 LED width height" << std::endl;
		exit(0);
	}
	numCaptures = 0;
	camera = new Camera(0, std::atoi(argv[3]), std::atoi(argv[4]), std::atoi(argv[5]));
	int btn1 = std::atoi(argv[1]);
	std::cout << "button 1 is: " << btn1 << std::endl;
	GPIO* button1 = new GPIO(btn1); //button 1 png
	button1->setDirection(GPIO::INPUT);
	button1->setEdgeType(GPIO::RISING);
	button1->waitForEdge(button1Pressed);
	int btn2 = std::atoi(argv[2]);
	GPIO* button2 = new GPIO(btn2); //button 2 jpg
	button2->setDirection(GPIO::INPUT);
	button2->setEdgeType(GPIO::RISING);
	button2->waitForEdge(button2Pressed);
	camera->start();
	bool running = true;
	while(running){
		std::string input;
		std::cin >> input;
		if(input == "quit"){
			std::cout << "shutting camera down" << std::endl;
			camera->shutdown();
		}
	}

}
int button1Pressed(int var){
	std::cout << "button1 Pressed" << std::endl;
	camera->takePicture(0, numCaptures);
	numCaptures++;
	return 0;
}
int button2Pressed(int var){
	std::cout << "button2 Pressed" << std::endl;
	camera->takePicture(1, numCaptures);
	numCaptures++;
	return 0;
}

