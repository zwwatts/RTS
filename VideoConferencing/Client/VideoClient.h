#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <iostream>
#include <opencv2/opencv.hpp> // C++ OpenCV include file


class VideoClient {
public:
	VideoClient(char* host);
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
