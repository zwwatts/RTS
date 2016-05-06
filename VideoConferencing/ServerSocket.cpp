/*
* A simple server in the internet domain using TCP
* Usage -> PROGRAM_NAME PORT_NUMBER
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

/*
* This method will print an error
* char* msg -> This is the prelude to the error
*/
void error(char* msg) {
	//Print the error to tferr using perror (See page 328)
	perror(msg);
	//Exit with a negative 1 indicating error
	exit(-1);
}

/*
* This is the main method for the client
* There are two parameters (argc must be 2)
* argv[0] -> Name of the program
* argv[1] -> Port number
*/
int main(int argc, char* argv[]) {
	int sockfd, newsockfd, portno, client, n, index;
	struct sockaddr_in, serv_addr, cli_addr;
	char buffer[256];
	
	//If there are not the right number of params abort
	if(argc != 2) {
		fprintf(stderr, "Usage: PROGRAM_NAME PORT_NUMBER\n");
		exit(-1);
	}
	
	//Create a socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	//If the retval is less than 0, the socket failed to be created
	if(sockfd < 0) {
		error("Error opening socket!\n");
	}
	
	//Initialize the buffer to all zeros
	memset((void*) &serv_addr, 0, sizeof(serv_addr));
	
	//Obtain the port number as an integer
	portno = atoi(argv[1]);
	
	//Setup the server address structure
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	
	//Bind the socket appropriately
	if(bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
		error("Error on binding!\n");
	}
	
	//Listen on the socker for an incoming connection
	//The param is the number of connections that can be waiting/queued
	//Most systems allow a maximum of 5
	listen(sockfd, 5);
	client = sizeof(clie_addr);
	
	//Block until a client has connected to the server
	//This returns a fd for the connection
	newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, &client);
	
	//If the rc is less than 1, there is an error
	if(newsockfd < 0) {
		error("Error on accept!\n");
	}
	
	//Fill the buffer with all zeros
	memset(&buffer[0], 0, sizeof(buffer));
	
	//Read from the buffer when data arrives
	//The max that can be read is 255
	n = read(newsockfd, buffer, sizeof(buffer) - 1);
	
	//Could not read from the socket
	if(n < 0) {
		error("Error reading from the socket!\n");
	}
	
	//Print the message
	printf("Here is the message: %s\n", buffer);
	
	//Write the message that has been received
	n = write(newsockfd, "I got your message!\n", 18);
	if(n < 0) {
		error("Error writing to socket!\n");
	}
	
	//Now convert the message to upper case
	index = 0;
	while(buffer[index] != 0) {
		buffer[index] = toupper(buffer[index]);
		index++;
	}
	
	//Write the message again
	n = write(newsockfd, &buffer[0], strlen(&buffer[0]));
	if(n < 0) {
		error("Error writing to socket!\n");
	}
	
	return 0;
	
}