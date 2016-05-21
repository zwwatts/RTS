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
#include "audioserver.h"
#include "AudioInterface.h"


#define SAMPLING_RATE (22500)
#define NUMBER_OF_CHANNELS (2)
#define BYTES_PER_SAMPLE (2)

AudioServer::AudioServer() {
    port = 10000;
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
    serv_addr.sin_port = htons(port);

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
    printf("waiting for connection\n");
    newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, (socklen_t*)&client);
    if(newsockfd < 0) {
        error("Error on accept!\n");
    }
    printf("connection accepted\n");

    AudioInterface* ai;
    ai = new AudioInterface("plughw:0", SAMPLING_RATE, NUMBER_OF_CHANNELS, SND_PCM_STREAM_PLAYBACK);
    ai->open();
    printf("Interface accessed\n");
    int bufferSize = ai->getRequiredBufferSize() * 8;
    printf("preparing to malloc\n");

    bufferAudio = (char*)malloc(bufferSize);
    //Fill the buffer with all zeros
    printf("buffered initialized\n");
    memset(bufferAudio, 0, sizeof(bufferAudio));
    ai->write(bufferAudio, bufferSize);
    printf("filled with 0\n");
    n = read(newsockfd, bufferAudio, bufferSize);
    if(n < 0) {
                    error("Error reading from the socket!\n");
                }
    do{
        memset(bufferAudio, 0, bufferSize);
        n = read(newsockfd, bufferAudio, bufferSize);
        if(n < 0) {
                        error("Error reading from the socket!\n");
                    }
        ai->write(bufferAudio, bufferSize);
        //bytesToCapture -= bufferSize;
        printf("Wrote %d bytes\n", n);
    }while(n > 0);


}

void AudioServer::error(char* msg) {
    //Print the error using perror (See page 328)
    perror(msg);
    exit(-1);
}
