/*
 * AudioClient.h
 *
 *  Created on: May 6, 2016
 *      Author: se3910
 */

#ifndef SRC_AUDIOCLIENT_H_
#define SRC_AUDIOCLIENT_H_
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <iostream>


class AudioClient {
public:
	AudioClient();
	virtual ~AudioClient();
	void startSending(int numSeconds);

private:
	int port;
	int FRAME_SIZE = 512;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	int sockfd;
	int buffer[FRAME_SIZE];
	char* hostName;
};



#endif /* SRC_AUDIOCLIENT_H_ */
