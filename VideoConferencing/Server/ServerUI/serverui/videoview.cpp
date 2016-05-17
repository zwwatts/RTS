#include "videoview.h"

VideoView::VideoView(QWidget *parent) :QLabel(parent)
{
    resize(100,100);
}

void VideoView::updateImage(QImage image){
    QPixmap pixmap = QPixmap::fromImage(image);
    this->setPixmap(pixmap);
}
