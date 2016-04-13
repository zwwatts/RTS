/*
 * Player.cpp
 *
 *  Created on: Apr 8, 2016
 *      Author: se3910
 */

#include "Player.h"
#include "gpio/GPIO.h"
#include <unistd.h>
#include <sys/time.h>
#include <iostream>
#include <stdlib.h>

using namespace exploringBB;

Player::Player(int button, int light) {
	Player::button = new GPIO(button);
	Player::button->setDirection(GPIO::INPUT);
	Player::light = new GPIO(light);
	Player::light->setDirection(GPIO::OUTPUT);
	Player::elapsedTime = 0;
}
Player::~Player() {

}

long Player::getElapsedTime(){
	return Player::elapsedTime;
}
pthread_t Player::getThread(){
	return Player::thread;
}
void Player::playCycle(){
	int timesPressed = 0;
	timeval initialTime;
	timeval postTime;
	while(timesPressed < 10){
		initialTime.tv_usec = 0;
		postTime.tv_usec = 0;
		sleep((rand()%2+1));
		gettimeofday(&initialTime, NULL);
		light->setValue(GPIO::HIGH);
		button->setEdgeType(GPIO::RISING);
		button->waitForEdge();
		gettimeofday(&postTime, NULL);
		light->setValue(GPIO::LOW);
		Player::elapsedTime += ((postTime.tv_sec * 1000000 + postTime.tv_usec) - (initialTime.tv_sec * 1000000 + initialTime.tv_usec));
		std::cout << "Elapsed Time in ms: " << Player::elapsedTime << " initial time: " << initialTime.tv_usec << " post time: " << postTime.tv_usec << std::endl;
		timesPressed++;

	}
}
void run(void *arg){
	Player* playerToStart = static_cast<Player*>(arg);
	playerToStart->playCycle();
}
void* startPlayer(void *player){
	Player* playerToStart = static_cast<Player*>(player);
	playerToStart->playCycle();
}


void Player::start(){
	pthread_create(&thread, NULL, startPlayer, (void *)this);
}

