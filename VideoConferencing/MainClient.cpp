/*
 * MainClient.cpp

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

//AudioClient audio();
int main(int argc, char* argv[]){

	AudioClient audio;
	audio.startSending(0);

	return 0;
}



