#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtAndroid>
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <CameraControllerX.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    invokeCCX();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::invokeCCX()
{
    ccx->callPhilipsActivityStarter(); //Calls a "pure" Android-java-"file".
    //ccx->callExternalCamera();
}
