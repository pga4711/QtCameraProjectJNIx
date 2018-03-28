#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtAndroid>
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    startCamera();
    qDebug()<<"TEST";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startCamera()
{


    //om ihåg: Method signatures are written as "(Arguments)ReturnType"

    QAndroidJniObject mainActivity = QtAndroid::androidActivity();
    QAndroidJniObject packageManager = mainActivity.callObjectMethod("getPackageManager",
                                                                 "()Landroid/content/pm/PackageManager;");

    QAndroidJniObject qtnativeActivity =
            QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative",
                                                      "activity",
                                                      "()Landroid/app/Activity;");
    if (qtnativeActivity.isValid())
        qDebug()<<"qtnativeActivity is valid";
    qDebug()<<"qtnativeActivity is NOT valid";


}
