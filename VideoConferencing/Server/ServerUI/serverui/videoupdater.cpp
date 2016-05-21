#include "videoupdater.h"
#include <QImage>

VideoUpdater::VideoUpdater(QObject *parent) :
    QObject(parent)
{
}

void VideoUpdater::sendNewFrameGlobal(QImage img){
    sendNewFrame(img);
}

void VideoUpdater::vidnut(){
    vidUp();
}
