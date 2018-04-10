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


    //Fixxing permissions
    QString permCamStr = QAndroidJniObject::getStaticObjectField("android/Manifest$permission",
                                                                           "CAMERA",
                                                                           "Ljava/lang/String;").toString();

    QString permWriteExtStr = QAndroidJniObject::getStaticObjectField("android/Manifest$permission",
                                                                           "WRITE_EXTERNAL_STORAGE",
                                                                           "Ljava/lang/String;").toString();

    QStringList permArray;
    permArray.append(permCamStr);
    permArray.append(permWriteExtStr);
    qDebug()<<"permArray: "<<permArray;

/*
    //Very bad to insert nullptr. But it is a fulhack
    QtAndroid::requestPermissions(permArray, nullptr);

    std::function<void(const QtAndroid::PermissionResultMap &)> x;
    const QtAndroid::PermissionResultMap y = nullptr;
    x = [](y){qDebug()<<"HELLO from lambda-function";};
    QtAndroid::PermissionResultCallback x;
    */

    QtAndroid::requestPermissions(permArray,[](const QtAndroid::PermissionResultMap& resultMap)
    {   qDebug()<<"This is resultMap :";
        /*
        QtAndroid::PermissionResult s;
        foreach( s, resultMap)
            qDebug()<<s;
        */
    });
    //1. Här funkar det inte, läs ifrån resultMap och kolla lite

    //2. Sen får Qt tillbaka ett filnamn som inte finns. Men som tur är sparas inget. Vad händer egentligen?



    //QtAndroid::requestPermissions(permArray, );




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCCX(/*const ?*/ CameraControllerX &inCcx)
{
    //I dont know the theory behind this referens passing, i have to stidy that actually.
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
