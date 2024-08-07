#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindialog.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _login_dig = new LoginDialog(this);
    setCentralWidget(_login_dig);
//    _login_dig->show();
    // 创建注册按钮和注册对话框的槽
    connect(_login_dig,&LoginDialog::switchRegister,this,&MainWindow::SlotSwitchReg);
    _reg_dig = new RegisterDialog(this);

    _login_dig->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    _reg_dig->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    _reg_dig->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SlotSwitchReg()
{
    setCentralWidget(_reg_dig);
    _login_dig->hide();
    _reg_dig->show();
}

