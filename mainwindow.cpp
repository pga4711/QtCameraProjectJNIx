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


    //om ihåg: Method signatures are written as "(Arguments)ReturnType"

    QAndroidJniObject mainActivity = QtAndroid::androidActivity();
    QAndroidJniObject packageManager = mainActivity.callObjectMethod("getPackageManager",
                                                                 "()Landroid/content/pm/PackageManager;");

    QAndroidJniObject qtnativeActivity =
            QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", //temporär Import+QtNative...
                                                      "activity", //anropar activity-metoden
                                                      "()Landroid/app/Activity;"); //Vi får tillbaka en Activity.


    if (qtnativeActivity.isValid())
    {
        qDebug()<<"qtnativeActivity is valid";
        //QAndroidJniObject intent("android/content/Intent", "()V");


        QAndroidJniObject gotClass = qtnativeActivity.callObjectMethod("getClass",
                                                                       "()Ljava/lang/Class;");
        QAndroidJniObject gotClassName = gotClass.callObjectMethod("getName", "()Ljava/lang/String;");
        qDebug()<<"This is qtnativeActivity class name: " << gotClassName.toString();


        QAndroidJniObject param1 = QAndroidJniObject::fromString("com.vmi");
        QAndroidJniObject param2 = QAndroidJniObject::fromString("com.vmi.StartCameraActivity");



        QAndroidJniObject intent("android/content/Intent", "()V");

        /*
        QAndroidJniObject intent("android/content/Intent",
                                 "(Landroid/content/Context;Ljava/lang/Class)V"
                                 qtnativeActivity.object<jobject>(),"min activity!!!!");
        */

        // Landroid/content/Context;   och sen ska vi ha Ljava/lang/Class;
        if (intent.isValid()){
            qDebug()<<"INTENT IS VALID";
            intent.callObjectMethod("setClassName","(Ljava/lang/String;Ljava/lang/String;)Landroid/content/Intent;",
                                    param1.object<jobject>(), param2.object<jobject>());



            //Här är problemet just nu.
            //qtnativeActivity.callObjectMethod("startActivity","(Landroid/content/Intent;)V",intent.object<jobject>());
        }

    }
    else
    {
        qDebug()<<"qtnativeActivity is NOT valid";
    }


    if (mainActivity.isValid())
    {
        qDebug()<<"mainactivity is valid";
        QAndroidJniObject gotClass = mainActivity.callObjectMethod("getClass",
                                                                       "()Ljava/lang/Class;");
        QAndroidJniObject gotClassName = gotClass.callObjectMethod("getName", "()Ljava/lang/String;");
        qDebug()<<"This is mainActivity classname: " << gotClassName.toString();


    }
    else
    {
    qDebug()<<"mainactivity is NOT valid";
    }
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
