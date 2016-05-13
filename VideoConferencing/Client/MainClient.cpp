/*
 * MainClient.cpp

 *
 *  Created on: May 6, 2016
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
#include "AudioClient.h"
#include "AudioServer.h"
#include <thread>
#include <iostream>
using namespace std;

//AudioClient audio();
int main(int argc, char* argv[]){

	AudioClient client;
	std::thread clientThread(startClient, client);

	AudioServer server;
	std::thread serverThread(startServer, server);
	return 0;
}
void startClient(AudioClient client){
	client.startSending(0);
}
void startServer(AudioServer server){

}


