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
#include "videoserver.h"
#include <opencv2/opencv.hpp>
using namespace cv;

#define SAMPLING_RATE (22500)
#define NUMBER_OF_CHANNELS (2)
#define BYTES_PER_SAMPLE (2)

VideoServer::VideoServer() {
    port = 10001;
    updater = new VideoUpdater;
}

VideoServer::~VideoServer() {

}

void VideoServer::startListening(int port) {
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
    newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, (socklen_t*)&client);
    if(newsockfd < 0) {
        error("Error on accept!\n");
    }

    updater->vidnut();
    while(true){

        int height = 480;
        int width = 640;
        Mat img = Mat::zeros( height,width, CV_8UC3);
            int  imgSize = img.total()*img.elemSize();
            uchar sockData[imgSize];

         //Receive data here
        int bytes = 0;
        for (int i = 0; i < imgSize; i += bytes) {
            if ((bytes = recv(newsockfd, sockData +i, imgSize  - i, 0)) == -1) {
                exit(-1);
            }
        }

         // Assign pixel value to img

         int ptr=0;
         for (int i = 0;  i < img.rows; i++) {
            for (int j = 0; j < img.cols; j++) {
                img.at<cv::Vec3b>(i,j) = cv::Vec3b(sockData[ptr+ 0],sockData[ptr+1],sockData[ptr+2]);
                ptr=ptr+3;
            }
         }
         updater->sendNewFrameGlobal(Mat2QImage(img));
    }

    //Print the message
    printf("Here is the message: %s\n", bufferVideo);
}

void VideoServer::error(char* msg) {
    //Print the error using perror (See page 328)
    perror(msg);
    exit(-1);
}

QImage VideoServer::Mat2QImage(const cv::Mat3b &src) {
        QImage dest(src.cols, src.rows, QImage::Format_ARGB32);
        for (int y = 0; y < src.rows; ++y) {
                const cv::Vec3b *srcrow = src[y];
                QRgb *destrow = (QRgb*)dest.scanLine(y);
                for (int x = 0; x < src.cols; ++x) {
                        destrow[x] = qRgba(srcrow[x][2], srcrow[x][1], srcrow[x][0], 255);
                }
        }
        return dest;
}
