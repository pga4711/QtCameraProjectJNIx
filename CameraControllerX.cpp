#include "CameraControllerX.h"

#ifdef Q_OS_ANDROID
#include <QAndroidJniEnvironment>
#include <QAndroidJniObject>
#include <QtAndroid>
#endif

#include <QDebug>


void CameraControllerX::callPhilipsActivityStarter()
{
    //Creating an intent that are going to start StartCameraActivity.

    int PHILIP_PHOTO = 2;
    qDebug()<<"Inside activity";

    QAndroidJniObject intent=QAndroidJniObject("android/content/Intent","()V");

    QAndroidJniObject packageName=QAndroidJniObject::fromString("com.vmi.cameratester");
    QAndroidJniObject className=QAndroidJniObject::fromString("com.vmi.cameratester.StartCameraActivity");
    intent.callObjectMethod("setClassName","(Ljava/lang/String;Ljava/lang/String;)Landroid/content/Intent;",
                            packageName.object<jstring>(),
                            className.object<jstring>());

    qDebug()<<"Before startActivity intent2..";
    QtAndroid::startActivity(intent, PHILIP_PHOTO, this);
}

void CameraControllerX::callExternalCamera()
{
#ifdef Q_OS_ANDROID


    //Gör så att man kan använda uri  och file och sådär:
    QAndroidJniObject builder = QAndroidJniObject("android/os/StrictMode$VmPolicy$Builder", "()V");
    QAndroidJniObject in_vmpolicy = builder.callObjectMethod("build",
                                                             "()Landroid/os/StrictMode$VmPolicy;");
    QAndroidJniObject::callStaticMethod<void>("android/os/StrictMode",
                                              "setVmPolicy",
                                              "(Landroid/os/StrictMode$VmPolicy;)V",
                                              in_vmpolicy.object<jobject>() );

    // Grant permissions

    // To prevent java.lang.SecurityException: Permission Denial:
    // starting Intent { act=android.media.action.IMAGE_CAPTURE
    // flg=0x3 cmp=org.codeaurora.snapcam/com.android.camera.PhotoCamera
    // clip={text/uri-list U:file:///storage/emulated/0/camera.jpg} (has extras) }
    // from ProcessRecord{dd1e705 5630:com.vmi.cameratester/u0a250} (pid=5630, uid=10250) with revoked permission android.permission.CAMERA



    QString permCamStr = QAndroidJniObject::getStaticObjectField("android/Manifest$permission",
                                                                           "CAMERA",
                                                                           "Ljava/lang/String;").toString();


    QString permWriteExtStr = QAndroidJniObject::getStaticObjectField("android/Manifest$permission",
                                                                           "WRITE_EXTERNAL_STORAGE",
                                                                           "Ljava/lang/String;").toString();

    QStringList strArray;
    strArray.append(permCamStr);
    strArray.append(permWriteExtStr);
    qDebug()<<"strArray!!: "<<strArray;

    QtAndroid::requestPermissions(strArray, nullptr); //Very bad to insert nullptr. But is a fulhack


    //Everything down below is from: https://github.com/minixxie/examples/tree/master/qt-for-mobile
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

        qDebug()<<"data.toString()!!!; " << data.toString();
		m_imagePath = absPath.toString();
		emit this->imagePathChanged();
	}

    if (receiverRequestCode == PHILIP_PHOTO && resultCode == Activity__RESULT_OK )
    {
        qDebug()<<"Returned from philip started activity";

    }
}
#endif
