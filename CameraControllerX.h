#ifndef __CAMERA_CONTROLLER_X_H__
#define __CAMERA_CONTROLLER_X_H__

#include <QObject>
#ifdef Q_OS_ANDROID
	#include <QAndroidActivityResultReceiver>
#endif

#ifdef Q_OS_ANDROID
class CameraControllerX : public QObject, QAndroidActivityResultReceiver
#else
class CameraControllerX : public QObject
#endif
{
	Q_OBJECT
	
private:
	QString m_imagePath;
public: //getters/setters
	const QString& imagePath() const { return this->m_imagePath; }

public:
    void callPhilipsActivityStarter();

	void callExternalCamera();

signals:
	void imagePathChanged();

private:
#ifdef Q_OS_ANDROID
	QAndroidJniObject takePhotoSavedUri;
	void handleActivityResult(int receiverRequestCode, int resultCode, const QAndroidJniObject & data);
#endif

};

#endif
