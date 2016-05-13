#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QImageReader>
#include <QPushButton>
#include <QVBoxLayout>
#include <QtGui>
#include <QImage>
#include "videoview.h"
#include <string>
#include <QFileDialog>
#include <unistd.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QImage* image = new QImage();
    QScrollArea* containerArea = new QScrollArea();
    QHBoxLayout* layout = new QHBoxLayout();
    QWidget* containerWidget = new QWidget();

    containerArea->setFixedWidth(500);
    containerWidget->setLayout(layout);
    containerArea->setWindowTitle("Face Image");

    QImageReader* reader = new QImageReader("/media/sf_lwshare/se3910/VideoConferencer/RTS/VideoConferencing/Server/ServerUI/serverui/face.jpg");
    reader->read(image);

    QLabel* label = new QLabel();
    label->setPixmap(QPixmap::fromImage(*image));
    label->resize(100,100);
    layout->addWidget(label);

    containerArea->setWidget(containerWidget);
    containerArea->show();
    int i = 0;
    bool meh = true;
    while(i < 3){
        if(meh){
            reader = new QImageReader("/media/sf_lwshare/se3910/VideoConferencer/RTS/VideoConferencing/Server/ServerUI/serverui/face2.jpg");
            reader->read(image);
            label->setPixmap(QPixmap::fromImage(*image));
            meh= false;
            sleep(2);
            i++;
        }
        else{
            reader = new QImageReader("/media/sf_lwshare/se3910/VideoConferencer/RTS/VideoConferencing/Server/ServerUI/serverui/face.jpg");
            reader->read(image);
            label->setPixmap(QPixmap::fromImage(*image));
            meh= true;
            sleep(2);
            i++;
        }

    }
    return app.exec();

    /*    QWidget Main_Window;

        QLabel i_label(&Main_Window);

        QImage* img = new QImage();
        QImageReader* rdr = new QImageReader("face.jpg");
        rdr->read(img);
        QLabel* lbl = new QLabel();
        lbl->setPixmap(QPixmap::fromImage(*img));
        QHBoxLayout* layo = new QHBoxLayout();
        layo->addWidget(lbl);

 //       QString filePath = "face.jpg";
   //     QImage image(filePath);
     //   i_label.setPixmap(QPixmap("face.jpg"));
        //i_label.setPixmap(QPixmap("1837.jpg"));

        QVBoxLayout *vbl = new QVBoxLayout(&Main_Window);
        vbl->addWidget(&i_label);

        Main_Window.show();

        return app.exec();*/
}
