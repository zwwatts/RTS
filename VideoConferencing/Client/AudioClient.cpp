/*
 * AudioClient.cpp
 * Audio device should be on plughw:1
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
#include <math.h>

#define SAMPLING_RATE (22050)
#define NUMBER_OF_CHANNELS (2)
#define BYTES_PER_SAMPLE (2)

/*
 * ctor - Initialize host & port for socket connection 
 */
AudioClient::AudioClient(char* host) {
	port = 10000;
	hostName = host;
}

AudioClient::~AudioClient() {
       
}

/*
 * Capture audio data from sound device and send it to the server 
 */
void AudioClient::startSending(int numSeconds){
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		printf("ERROR opening socket\n");
		exit(-1);
	}
	printf("%s\n",hostName);
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
	printf("%d\n", port);
	// connect to the socket.
	if (connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
	{
		printf("ERROR connecting\n");
		exit(-1);
	}

	AudioInterface *ai;
	char *bufferAudio;
	int bufferSize;

	ai = new AudioInterface("plughw:1", SAMPLING_RATE, NUMBER_OF_CHANNELS, SND_PCM_STREAM_CAPTURE);
	ai->open();
	bufferSize = ai->getRequiredBufferSize();
	bufferAudio = (char*)malloc(bufferSize);

	// Determine how many bytes need to be captured.
	int bytesToCapture = SAMPLING_RATE * numSeconds * NUMBER_OF_CHANNELS * BYTES_PER_SAMPLE;

	do {
		// Fill the buffer with all zeros.
		memset(bufferAudio, 0, bufferSize);

		// Capture from the soundcard
		ai->read(bufferAudio);
		if (atoi(bufferAudio) > 0) {
    			//printf("Avg amplitude/sec: %d\n", calcAmp(bufferAudio));
		}
		// Write to the socket buffer.
		write(sockfd, bufferAudio, bufferSize);

		bytesToCapture-=bufferSize;

	} while ((bytesToCapture > 0));


	ai->close();
}

/*
 * Calculate the average amplitude per second for a sample of audio data
 */
int AudioClient::calcAmp(char *sample){
	long scale = atoi(sample) / 32768;
	return long(20 * log10(scale));
}
