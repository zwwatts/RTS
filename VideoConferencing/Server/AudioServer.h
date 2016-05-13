/*
* AudioServer.h
*
* Created: May 11, 2016
* Author: Se-3910
*/
#ifndef SRC_AUDIOSERVER_H_
#define SRC_AUDIOSERVER_H_
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

class AudioServer {
    public:
        AudioServer();
        virtual ~AudioServer();
        void error(char* msg);
        void startListening(int port);
    
    private:
    	int sockfd, newsockfd, client, n, index;
        struct sockaddr_in serv_addr;
        struct sockaddr_in cli_addr;
        char *bufferAudio;
        int port;
};

#endif /* SRC_AUDIOSERVER_H_*/
