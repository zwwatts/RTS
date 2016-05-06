/*
 * AudioClient.cpp
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


AudioClient::AudioClient() {
	// TODO Auto-generated constructor stub
	port = 1337;
	hostName = "127.0.0.1";
}

AudioClient::~AudioClient() {
	// TODO Auto-generated destructor stub
}
void AudioClient::startSending(int numSeconds){
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
	memset((void*)&buffer[0], 0, sizeof(buffer));

	buffer[0] = 'a';
	int n = write(sockfd,buffer,strlen((const char*)&buffer[0]));


}

