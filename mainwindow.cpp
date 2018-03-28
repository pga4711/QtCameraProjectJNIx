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

    /*
    QAndroidJniObject intent("android/content/Intent", <--------Där är klassen intent, man skapar en android-intent
                             "(Ljava/lang/String;)V",  <----------Argumentet är en String som vi skickar in, och ut kommer void!
                             ACTION_SET_TIMER.object<jstring>()); <--------jstring skickas in, då vet jni om det. .object<jstring>()
                                                                           gör om android-stringt till en JNI-vänlig string

     */

    //Prova gör en sånhär:
    //    Intent intent = new Intent(this, SecondActivity.class);
    //    startActivity(intent);
    //Som implementeras såhär:
    // public Intent(Context packageContext, Class<?> cls) {
    //  throw new RuntimeException("Stub!");
    //}



    //fast i Qt-JNI-form. HUR SKA JAG GÖRA DET?
    //QAndroidJniObject intent("android/content/Intent",
    //                         "(Landroid/content/Context;Ljava/lang.Class;)V");

    //QAndroidJniObject mainActivity = QtAndroid::androidActivity();

    //QtAndroid::startActivity(activity);
}
