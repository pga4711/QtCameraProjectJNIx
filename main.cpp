#include "mainwindow.h"
#include <QApplication>
#include "CameraControllerX.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    CameraControllerX *ccxInMain = new CameraControllerX();

    w.setCCX(*ccxInMain);
    w.show();

    return a.exec();
}
