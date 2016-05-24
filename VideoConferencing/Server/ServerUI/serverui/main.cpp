#include "mainwindow.h"
#include <QApplication>
#include "audioserver.h"
#include "videoserver.h"

/**
 * Starts the audio listener
 * @param server The listener to start
 */
void startAudioServer(AudioServer server);

/**
 * Starts the video listener
 * @param server The listener to start
 */
void startVideoServer(VideoServer server);

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWin;
    //mainWin.show();

    AudioServer aserver;
    std::thread aserverThread(startAudioServer, aserver);

    VideoServer vserver;
    std::thread vserverThread(startVideoServer, vserver);
    QObject::connect(vserver.updater,SIGNAL(sendNewFrame(QImage)),&mainWin,SLOT(updateFrame(QImage)));
    QObject::connect(vserver.updater,SIGNAL(vidUp()),&mainWin,SLOT(vidUp()));

    int ret = app.exec();
    aserverThread.join();
    vserverThread.join();
    return ret;
}

void startAudioServer(AudioServer server){
    server.startListening(10000);
}

void startVideoServer(VideoServer server){
    server.startListening(10001);
}
