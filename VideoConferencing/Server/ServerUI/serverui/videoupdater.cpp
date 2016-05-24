#include "videoupdater.h"
#include <QImage>

VideoUpdater::VideoUpdater(QObject *parent) :
    QObject(parent)
{
}

/**
 * Sends a sendNewFrame signal with the given QImage
 * @param img The QImage to send
 */
void VideoUpdater::sendNewFrameGlobal(QImage img){
    sendNewFrame(img);
}

/**
 * Sends a vidUp signal
 */
void VideoUpdater::vidnut(){
    vidUp();
}
