#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "videoview.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *imageLabel = new VideoView(this);
    layout->addWidget(imageLabel);
}

MainWindow::~MainWindow()
{
}
