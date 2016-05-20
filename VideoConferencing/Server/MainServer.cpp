/*
 * MainServer.cpp
 *
 *  Created on: May 13, 2016
 *      Author: se3910
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include "AudioServer.h"
#include <thread>
#include <iostream>
using namespace std;

void startServer(AudioServer server, int numSeconds);
//AudioClient audio();
int main(int argc, char* argv[]){

	AudioServer server;
	int numSeconds = atoi(argv[1]);
	std::thread serverThread(startServer, server, numSeconds);
	serverThread.join();
	return 0;
}
void startServer(AudioServer server, int numSeconds){
	server.startListening(10000, numSeconds);
}




