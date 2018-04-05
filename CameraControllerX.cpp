#include "CameraControllerX.h"

#ifdef Q_OS_ANDROID
#include <QAndroidJniEnvironment>
#include <QAndroidJniObject>
#include <QtAndroid>
#endif

#include <QDebug>

void CameraControllerX::callPhilipsActivityStarter()
{
    //Gör en intent som ska starta StartCameraActivity.
    //Android brukar vela ha var den är och vilket package den ligger i.

    int PHILIP_PHOTO = 2;
    qDebug()<<"Inside activity";

    QAndroidJniObject action = QAndroidJniObject::fromString("com.vmi.cameratester.StartCameraActivity");


    QAndroidJniObject intent2=QAndroidJniObject("android/content/Intent","()V");

    QAndroidJniObject packageName=QAndroidJniObject::fromString("com.vmi.cameratester");
    QAndroidJniObject className=QAndroidJniObject::fromString("com.vmi.cameratester.StartCameraActivity");
    intent2.callObjectMethod("setClassName","(Ljava/lang/String;Ljava/lang/String;)Landroid/content/Intent;",
                            packageName.object<jstring>(),
                            className.object<jstring>());


    //VAD SKA JAG HA HÄR?
    qDebug()<<"Before startActivity";

    QtAndroid::startActivity(intent2, PHILIP_PHOTO, this);


}

void CameraControllerX::callExternalCamera()
{
#ifdef Q_OS_ANDROID

    // Philips smuts:

     QAndroidJniObject mainActivity = QtAndroid::androidActivity();
     QAndroidJniObject gotClass = mainActivity.callObjectMethod("getClass", "()Ljava/lang/Class;");
     QAndroidJniObject gotClassName = gotClass.callObjectMethod("getName", "()Ljava/lang/String;");
     qDebug()<<"This is mainActivity !! classname: " << gotClassName.toString();

	//android.provider.MediaStore.EXTRA_OUTPUT
	QAndroidJniObject MediaStore__EXTRA_OUTPUT
            = QAndroidJniObject::getStaticObjectField(
				"android/provider/MediaStore", "EXTRA_OUTPUT", "Ljava/lang/String;");
    qDebug() << "MediaStore__EXTRA_OUTPUT.isValid()=" << MediaStore__EXTRA_OUTPUT.isValid();

	QAndroidJniObject action = QAndroidJniObject::fromString("android.media.action.IMAGE_CAPTURE");
	QAndroidJniObject intent=QAndroidJniObject("android/content/Intent","(Ljava/lang/String;)V",
											   action.object<jstring>());
    qDebug() << __FUNCTION__ << "intent.isValid()=" << intent.isValid();

	QAndroidJniObject extDir = QAndroidJniObject::callStaticObjectMethod(
				"android/os/Environment", "getExternalStorageDirectory", "()Ljava/io/File;");
    qDebug() << "extDir.isValid()=" << extDir.isValid();

	QAndroidJniObject filename = QAndroidJniObject::fromString("camera.jpg");

	QAndroidJniObject photo=QAndroidJniObject("java/io/File","(Ljava/io/File;Ljava/lang/String;)V",
											   extDir.object<jobject>(), filename.object<jstring>());
    qDebug() << __FUNCTION__ << "photo.isValid()=" << photo.isValid();

    takePhotoSavedUri = QAndroidJniObject::callStaticObjectMethod(
                "android/net/Uri", "fromFile", "(Ljava/io/File;)Landroid/net/Uri;", photo.object<jobject>());
    qDebug() << "takePhotoSavedUri.isValid()=" << takePhotoSavedUri.isValid();

    intent.callObjectMethod(
                "putExtra","(Ljava/lang/String;Landroid/os/Parcelable;)Landroid/content/Intent;",
				MediaStore__EXTRA_OUTPUT.object<jstring>(), takePhotoSavedUri.object<jobject>());
    qDebug() << __FUNCTION__ << "intent.isValid()=" << intent.isValid();

	int SHOOT_PHOTO = 1;
	QtAndroid::startActivity(intent, SHOOT_PHOTO, this);
#endif

}

#ifdef Q_OS_ANDROID
void CameraControllerX::handleActivityResult(int receiverRequestCode, int resultCode, const QAndroidJniObject & data)
{
	int SHOOT_PHOTO = 1;
    int PHILIP_PHOTO = 2;
	jint Activity__RESULT_OK = QAndroidJniObject::getStaticField<jint>(
				"android.app.Activity", "RESULT_OK");

	if ( receiverRequestCode == SHOOT_PHOTO && resultCode == Activity__RESULT_OK )
	{
        qDebug() << "takePhotoSavedUri:" << takePhotoSavedUri.toString();

		QAndroidJniObject absPath = takePhotoSavedUri.callObjectMethod("getPath","()Ljava/lang/String;");
        qDebug() << __FUNCTION__ << "absPath.isValid()=" << absPath.isValid();

		m_imagePath = absPath.toString();
		emit this->imagePathChanged();
	}

    if (receiverRequestCode == PHILIP_PHOTO && resultCode == Activity__RESULT_OK )
    {
        qDebug()<<"Returned from philip started activity";

    }
}
#endif
