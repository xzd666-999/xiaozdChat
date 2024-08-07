#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "logindialog.h"
#include "registerdialog.h"
#include <QMainWindow>
/******************************************************************************
 *
 * @file       mainwindow.h
 * @brief      主窗口
 *
 * @author     xiaozd
 * @date       2024/04/14
 * @history
 *****************************************************************************/

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void SlotSwitchReg();
private:
    Ui::MainWindow *ui;
    LoginDialog * _login_dig;
    RegisterDialog* _reg_dig;
};
#endif // MAINWINDOW_H
