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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startCamera()
{
    //Foo
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


        /*
        QAndroidJniObject intent("Landroid/content/Intent", "()V");

        if (intent.isValid())
        {
            qDebug()<<"intent is valid";
            intent.callObjectMethod("setClassName",
                                    "(Ljava/lang/String;Ljava/lang/String;)Landroid/content/Intent;",
                                    param1.object<jobject>(), param2.object<jobject>());


            //These both returns empty string
            qDebug()<<"This is getLaunchIntentForPackage param 1: "<< pm.callObjectMethod("getLaunchIntentForPackage","(Ljava/lang/String;)Landroid/content/Intent;", param1.object<jstring>()).toString();
            qDebug()<<"This is getLaunchIntentForPackage param 2: "<< pm.callObjectMethod("getLaunchIntentForPackage","(Ljava/lang/String;)Landroid/content/Intent;", param2.object<jstring>()).toString();


            //Här är problemet just nu.
            mainActivity.callMethod<void>("startActivity","(Landroid/content/Intent;)V",intent.object<jobject>());

            qDebug()<<"Kommer vi hit?";
        }
        else
        {
            qDebug()<<"intent is NOT valid";
        }

        */

    }
    else
    {
        qDebug()<<"mainActivity is NOT valid";
    }

}
