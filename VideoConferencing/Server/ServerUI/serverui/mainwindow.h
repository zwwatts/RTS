#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <thread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateFrame(QImage img);
    void vidUp();

signals:
    void sendNewFrame();

private:
    Ui::MainWindow *ui;
    QLabel* label;
    QLabel* vidStat;
};

#endif // MAINWINDOW_H
