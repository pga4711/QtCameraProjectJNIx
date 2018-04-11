#ifndef __CAMERA_CONTROLLER_X_H__
#define __CAMERA_CONTROLLER_X_H__

#include <QObject>
#include <QDebug>

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
public:
	const QString& imagePath() const { return this->m_imagePath; }

public:
    bool grantPermission();
    void callPhilipsActivityStarter(); 

signals:
    void imagePathChanged();

private:
#ifdef Q_OS_ANDROID
	void handleActivityResult(int receiverRequestCode, int resultCode, const QAndroidJniObject & data);
#endif

};

#endif
