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

void MainWindow::setCCX(/*const ?*/ CameraControllerX &inCcx)
{
    //I dont know the theory behind this referens passing, i have to STUDY that actually.
    ccxFromMain = &inCcx;  //Trying to pass the reference-value.
    connect(ccxFromMain, SIGNAL(imagePathChanged()), this, SLOT(newUriArrived()));
}

void MainWindow::invokeCCX()
{
    ccxFromMain->callPhilipsActivityStarter();
}
void MainWindow::on_triggerActivityBtn_clicked()
{
    invokeCCX();
}

void MainWindow::newUriArrived()
{
    qDebug()<<"Setting new uri onto label";
    ui->uriLabel->setText(ccxFromMain->imagePath());
}

