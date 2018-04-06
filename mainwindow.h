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


    void setCCX(CameraControllerX inCcx);
    void invokeCCX();

private slots:
    void on_triggerActivityBtn_clicked();


private:
    Ui::MainWindow *ui;
    CameraControllerX *ccx = new CameraControllerX();
    //CameraControllerX ccxFromMain;
    CameraControllerX ccxFromMain;
};

#endif // MAINWINDOW_H
