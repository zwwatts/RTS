/*
 * VideoClient.h
 *
 *
 *  Created on: May 20, 2016
 *      Author: wattsz
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <iostream>
#include <opencv2/opencv.hpp> // C++ OpenCV include file

using namespace cv;

class VideoClient {
public:
	VideoClient(char* host, int cameraPort);
	virtual ~VideoClient();
	void startCapturing(int numSeconds);

private:
	int port;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	int sockfd;
	int buffer[512];
	char* hostName;
	VideoCapture* capture;
};
