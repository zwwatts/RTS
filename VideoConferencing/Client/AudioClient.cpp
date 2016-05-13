/*
 * AudioClient.cpp
 *
 *  Created on: May 6, 2016
 *      Author: sorianog, wattsz
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
#include "AudioInterface.h"

#define SAMPLING_RATE (22500)
#define NUMBER_OF_CHANNELS (2)
#define BYTES_PER_SAMPLE (2)

AudioClient::AudioClient(char* host) {
	// TODO Auto-generated constructor stub
	port = 1337;
	hostName = host;
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


	buffer[0] = 'a';
	int n = write(sockfd,buffer,strlen((const char*)&buffer[0]));

	AudioInterface *ai;
	char *bufferAudio;
	int bufferSize;

	//TODO: un-hardcode the audio port/device name
	ai = new AudioInterface("plughw:0", SAMPLING_RATE, NUMBER_OF_CHANNELS, SND_PCM_STREAM_CAPTURE);
	bufferSize = ai->getRequiredBufferSize();
	bufferAudio = (char*)malloc(bufferSize);

	// Determine how many bytes need to be captured.
	int bytesToCapture = SAMPLING_RATE * numSeconds * NUMBER_OF_CHANNELS * BYTES_PER_SAMPLE;

	do {
		// Fill the buffer with all zeros.
		memset(bufferAudio, 0, bufferSize);

		// Capture from the soundcard
		ai->read(bufferAudio);

		// Write to the socket buffer.
		write(sockfd, bufferAudio, bufferSize);

		bytesToCapture-=bufferSize;

	} while ((bytesToCapture > 0));


	ai->close();
}

