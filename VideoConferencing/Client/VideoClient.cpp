#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "AudioServer.h"
#include "AudioInterface.h"
#include <thread>
#include <string>
#include <opencv2/opencv.hpp> // C++ OpenCV include file


using namespace cv;

VideoClient::VideoClient(char* host, int cameraPort){
	int port = 1338;
	hostName = host;
	capture = new VideoCapture(cameraPort);
	capture->set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	capture->set(CV_CAP_PROP_FRAME_WIDTH, 640);
}

void VideoClient::startCapturing(int numSeconds){


	sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd < 0)
		{
			printf("ERROR opening socket\n");
			exit(-1);
		}
		server = gethostbyname(hostName);

		if (server == NULL) {
			fprintf(stderr,"ERROR, no such host\n");
			exit(0);
		}
		memset((void*)&serv_addr, 0, sizeof(serv_addr));
		// Set up the server address type.
		serv_addr.sin_family = AF_INET;
		// Copy the data.
		memcpy((void*)&serv_addr.sin_addr.s_addr,(void*)server->h_addr, server->h_length);
		serv_addr.sin_port = htons(port);
		// connect to the socket.
		if (connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
		{
			printf("ERROR connecting\n");
			exit(-1);
		}

		if(!capture->isOpened()){
		     std::cout << "Failed to connect to the camera." << std::endl;
		     exit(-1);
		    }
		 Mat frame, edges;
		 bool running = true;
		 while(running){
			 capture->retrieve(frame, 0);
			 frame = (frame.reshape(0,1)); // to make it continuous
			 int  imgSize = frame.total()*frame.elemSize();

			 // Send data here
			 bytes = send(clientSock, frame.data, imgSize, 0);
		 }

}
