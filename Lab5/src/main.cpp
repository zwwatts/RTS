/*
 * main.cpp
 *
 *  Created on: Apr 15, 2016
 *      Author: se3910
 */

Camera camera;
int numCaptures;

int main(char*  argv[], int argc){
	if(argc < 6 || argc > 6){
		std::cout << "selfie button1 button2 LED heigh width" << std::endl;
		exit(0);
	}
	numCaptures = 0;
	camera = new Camera(argv[3], argv[4], argv[5]);
	GPIO button1 = new GPIO(argv[1]); //button 1 png
	button1->setDirection(GPIO::INPUT);
	button1->setEdgeType(GPIO::FALLING);
	button1->waitForEdge(button1Pressed);
	GPIO button2 = new GPIO(argv[2]); //button 2 jpg
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
void button1Pressed(int var){
	camera.takePicture(0, numCaptures);
	numCaptures++;
}
void button2Pressed(int var){
	camera.takePicture(1, numCaptures);
	numCaptures++;
}

