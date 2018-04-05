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
    ccx->callPhilipsActivityStarter();
}


void MainWindow::startCameraBAD()
{
    //om ihåg: Method signatures are written as "(Arguments)ReturnType"

    QAndroidJniObject mainActivity = QtAndroid::androidActivity();

    //When to use this pm?
    QAndroidJniObject pm = mainActivity.callObjectMethod("getPackageManager",
                                                                 "()Landroid/content/pm/PackageManager;");
    if (mainActivity.isValid())
    {
        QAndroidJniObject gotClass = mainActivity.callObjectMethod("getClass", "()Ljava/lang/Class;");
        QAndroidJniObject gotClassName = gotClass.callObjectMethod("getName", "()Ljava/lang/String;");
        qDebug()<<"This is mainActivity classname: " << gotClassName.toString();


        QAndroidJniObject param1 = QAndroidJniObject::fromString("com.vmi.cameratester");
        QAndroidJniObject param2 = QAndroidJniObject::fromString("com.vmi.cameratester.StartCameraActivity");


        //Problem here?
        QAndroidJniObject intent2("android/content/Intent", "(Ljava/lang/String;)V", param2.object<jstring>());


        qDebug()<<"getAction: "<<intent2.callObjectMethod<jstring>("getAction").toString();



        QAndroidJniObject o = intent2.callObjectMethod("resolveActivity","(Landroid/content/pm/PackageManager;)Landroid/content/ComponentName");

        qDebug()<<"resolveActivity: "<<o.toString();

        //resolveactivity?

        if (intent2.isValid())
        {
                qDebug()<<"intent2 is valid";
                mainActivity.callMethod<void>("startActivity","(Landroid/content/Intent;)V",intent2.object<jobject>());
        }
        else
        {
            qDebug()<<"intent2 is not valid";
        }


    }
    else
    {
        qDebug()<<"mainActivity is NOT valid";
    }

}
