#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QImageReader>
#include <QPushButton>
#include <QVBoxLayout>
#include <QtGui>
#include <QImage>
#include <string>
#include <QFileDialog>
#include <unistd.h>
#include <thread>
#include <stdio.h>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QImage* image = new QImage();
    QScrollArea* containerArea = new QScrollArea();
    QHBoxLayout* layout = new QHBoxLayout();
    QWidget* containerWidget = new QWidget();

    containerArea->setFixedWidth(500);
    containerWidget->setLayout(layout);
    containerArea->setWindowTitle("Team Zero");

    QImageReader* reader = new QImageReader("/media/sf_lwshare/se3910/VideoConferencer/RTS/VideoConferencing/Server/ServerUI/serverui/face.jpg");
    reader->read(image);
    label = new QLabel();

    label->setPixmap(QPixmap::fromImage(*image));
    label->resize(100,100);
    layout->addWidget(label);
    vidStat = new QLabel();

    vidStat->setText("Waiting...");
    layout->addWidget(vidStat);

    containerArea->setWidget(containerWidget);
    containerArea->show();
}

MainWindow::~MainWindow()
{
}

void MainWindow::updateFrame(QImage img){
    label->setPixmap(QPixmap::fromImage(img));

}

void MainWindow::vidUp(){
    vidStat->setText("Video Connected");
}
