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

void startServer(AudioServer server);
//AudioClient audio();
int main(int argc, char* argv[]){

	AudioServer server;
	std::thread serverThread(startServer, server);
	serverThread.join();
	return 0;
}
void startServer(AudioServer server){
	server.startListening(1337);
}




