/*
* AudioServer.cpp
* 
* Created: May 11, 2016
* Author: Se-3910
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "AudioServer.h"

AudioServer::AudioServer() {
	port = 1337;
}

AudioServer::~AudioServer() {
	
}

void AudioServer::startListening(int port) {	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) {
		error("Error opening socket!\n");
	}
	
	//Initialize the buffer to all zeros
	memset((void*) &serv_addr, 0, sizeof(serv_addr));
	
	//Setup the server address structure
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	
	//Bind the socket appropriately
	if(bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
		error("Error on binding!\n");
	}
	
	//Listen on the socket for an incoming connection
	//The param is the number of connections that can be waiting/queued
	//Most systems allow a maximum of 5
	listen(sockfd, 5);
	client = sizeof(cli_addr);
	
	//Block until a client has connected to the server
	//This returns a fd for the connection
	newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, (socklen_t*)&client);
	if(newsockfd < 0) {
		error("Error on accept!\n");
	}
	
	//Fill the buffer with all zeros
	memset(&buffer[0], 0, sizeof(buffer));
	
	//Read from the buffer when data arrives
	//The max that can be read is 255
	n = read(newsockfd, buffer, sizeof(buffer) - 1);
	if(n < 0) {
		error("Error reading from the socket!\n");
	}
	
	//Print the message
	printf("Here is the message: %s\n", buffer);
}

void error(char* msg) {
	//Print the error using perror (See page 328)
	perror(msg);
	exit(-1);
}