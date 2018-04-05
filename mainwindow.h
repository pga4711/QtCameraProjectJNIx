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
    void invokeCCX();

private:
    Ui::MainWindow *ui;
    CameraControllerX *ccx = new CameraControllerX();


};

#endif // MAINWINDOW_H
