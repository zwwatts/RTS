/*
 * Player.h
 *
 *  Created on: Apr 8, 2016
 *      Author: se3910
 */
#include "gpio/GPIO.h"
#ifndef PLAYER_H_
#define PLAYER_H_
using namespace exploringBB;
class Player {
public:
	Player(int button, int light);
	virtual ~Player();
	long getElapsedTime();
	pthread_t getThread();
	friend void* startPlayer(void *player);
	void playCycle();
	void start();
	void run();
private:
	GPIO* button;
	GPIO* light;
	long elapsedTime;
	pthread_t thread;

};

#endif /* PLAYER_H_ */
