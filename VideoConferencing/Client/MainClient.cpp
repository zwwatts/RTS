/*
 * MainClient.cpp
 *
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
#include "VideoClient.h"
#include <thread>
#include <iostream>
using namespace std;

void startClient(AudioClient client, int numSeconds);
void startVideo(VideoClient video, int numSeconds);
int main(int argc, char* argv[]){
	char* host = argv[1];
	int numSeconds = atoi(argv[2]);
	AudioClient client(host);
	std::thread clientThread(startClient, client, numSeconds);

	VideoClient video(host, 0);
	std::thread videoThread(startVideo, video, numSeconds);
	clientThread.join();
	return 0;
}
void startClient(AudioClient client, int numSeconds){
	client.startSending(numSeconds);
}
void startVideo(VideoClient video, int numSeconds){
	video.startCapturing(numSeconds);
}



