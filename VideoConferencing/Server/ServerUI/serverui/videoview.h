#ifndef VIDEOVIEW_H
#define VIDEOVIEW_H

#include <QGraphicsView>
#include <QLabel>

class VideoView: public QLabel
{
public:
    VideoView(QWidget *parent);

    void updateImage(QImage image);

private:

};

#endif // VIDEOVIEW_H
