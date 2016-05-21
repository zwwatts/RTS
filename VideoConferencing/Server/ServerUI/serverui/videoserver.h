#ifndef VIDEOSERVER_H
#define VIDEOSERVER_H
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <QImage>
#include <QObject>
#include "videoupdater.h"
using namespace cv;

class VideoServer
{
public:
    VideoServer();
    virtual ~VideoServer();
    void error(char* msg);
    void startListening(int port);
    VideoUpdater* updater;

private:
    int sockfd, newsockfd, client, n, index;
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
    char *bufferVideo;
    QImage Mat2QImage(const cv::Mat3b &src);
    int port;

};

#endif // VIDEOSERVER_H
