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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCCX(CameraControllerX inCcx)
{
    //ccxFromMain=inCcx;//pass the reference i think is good
}

void MainWindow::invokeCCX()
{
    ccx->callPhilipsActivityStarter();

    //ccxFromMain.callExternalCamera();
    //i can not do these yet, i forgot how it works with pointers and ampersand and references:
    //ccxFromMain->callExternalCamera();
}

void MainWindow::on_triggerActivityBtn_clicked()
{
    invokeCCX();
}
