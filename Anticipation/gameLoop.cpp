/*
 * gameLoop.cpp
 *
 *  Created on: Apr 8, 2016
 *      Author: se3910
 */

#include "Player.h"
#include "gpio/GPIO.h"
#include "pthread.h"
#include <iostream>
using namespace std;
int main(){
	Player player1(67, 66);
	Player player2(69, 68);
	player1.start();
	player2.start();

	pthread_join(player1.getThread(), NULL);
	pthread_join(player2.getThread(), NULL);

	std::cout << "Player 1 Time: " << player1.getElapsedTime() << " Player 2 Time: " << player2.getElapsedTime() << std::endl;
	if(player1.getElapsedTime() == player2.getElapsedTime()){
		std::cout << "Both Players WIN!" << std::endl;
	}
	else if(player1.getElapsedTime() < player2.getElapsedTime()){
		std::cout << "Player 1 Wins!" << std::endl;
	}
	else{
		std::cout << "Player 2 Wins!" << std::endl;
	}

	return 0;
}

