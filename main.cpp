#include "mainwindow.h"
#include <QApplication>
#include "CameraControllerX.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    //CameraControllerX ccxInMain; //On stack?
    CameraControllerX *ccxInMain = new CameraControllerX(); //Or heap?

    //Function does not work
    //C:\Users\Philip\kodning\qtprojekt\QtCameraProjectJNIx\main.cpp:15:
    //error: no matching function for call to 'MainWindow::setCCX(CameraControllerX*&)'
    //w.setCCX(ccxInMain); //??????????????


    w.show();

    return a.exec();
}
