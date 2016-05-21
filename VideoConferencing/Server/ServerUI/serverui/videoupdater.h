#ifndef VIDEOUPDATER_H
#define VIDEOUPDATER_H

#include <QObject>
#include <QImage>

class VideoUpdater : public QObject
{
    Q_OBJECT
public:
    explicit VideoUpdater(QObject *parent = 0);
    void sendNewFrameGlobal(QImage img);
    void vidnut();

signals:
    void sendNewFrame(QImage img);
    void vidUp();

public slots:

};

#endif // VIDEOUPDATER_H
