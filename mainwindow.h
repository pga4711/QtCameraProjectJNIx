#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <CameraControllerX.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

                //const QVariant &value
    void setCCX(CameraControllerX &);
    void invokeCCX();

private slots:
    void on_triggerActivityBtn_clicked();
    void newUriArrived();


private:
    Ui::MainWindow *ui;

    //CameraControllerX ccx;

    CameraControllerX *ccxFromMain;
    QString currentURI;
};

#endif // MAINWINDOW_H
