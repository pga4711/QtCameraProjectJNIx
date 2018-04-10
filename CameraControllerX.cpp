#include "CameraControllerX.h"

#ifdef Q_OS_ANDROID
#include <QAndroidJniEnvironment>
#include <QAndroidJniObject>
#include <QtAndroid>
#endif

#include <QDebug>

void CameraControllerX::callPhilipsActivityStarter()
{
    #ifdef Q_OS_ANDROID
    //Creating an intent that are going to start StartCameraActivity.


    int PHILIP_PHOTO = 1;
    qDebug()<<"Inside activity";

    QAndroidJniObject intent=QAndroidJniObject("android/content/Intent","()V");

    QAndroidJniObject packageName=QAndroidJniObject::fromString("com.vmi.cameratester");
    QAndroidJniObject className=QAndroidJniObject::fromString("com.vmi.cameratester.StartCameraActivity");
    intent.callObjectMethod("setClassName","(Ljava/lang/String;Ljava/lang/String;)Landroid/content/Intent;",
                            packageName.object<jstring>(),
                            className.object<jstring>());

    qDebug()<<"Before startActivity intent2..";

    QtAndroid::startActivity(intent, PHILIP_PHOTO, this);

    #endif
}

#ifdef Q_OS_ANDROID
void CameraControllerX::handleActivityResult(int receiverRequestCode, int resultCode, const QAndroidJniObject & data)
{
    qDebug()<<"inside handleActivityResult";

    int PHILIP_PHOTO = 1;
	jint Activity__RESULT_OK = QAndroidJniObject::getStaticField<jint>(
				"android.app.Activity", "RESULT_OK");


    if (receiverRequestCode == PHILIP_PHOTO && resultCode == Activity__RESULT_OK )
    {
        qDebug()<<"Returned from philip started activity";

        QAndroidJniObject str = QAndroidJniObject::fromString("photoURI");

        QString uri = data.callObjectMethod("getStringExtra",
                              "(Ljava/lang/String;)Ljava/lang/String;",
                              str.object<jstring>()).toString();
        qDebug()<<"This was received URI: "<<uri;

        //Passing it the same way as Minixxie
        m_imagePath=uri;
        emit this->imagePathChanged();
    }

}
#endif
