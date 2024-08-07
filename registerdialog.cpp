#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "global.h"
RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    ui->pass_lineEdit->setEchoMode(QLineEdit::Password);
    ui->confirm_lineEdit->setEchoMode(QLineEdit::Password);
    ui->err_tip->setProperty("state","normal");// 设置错误信息的初始状态为normal
    repolish(ui->err_tip);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::showTip(QString str,bool b_ok)
{
    if(b_ok){
        ui->err_tip->setProperty("state","normal");
        repolish(ui->err_tip);
    }else{
        ui->err_tip->setText(str);
        ui->err_tip->setProperty("state","err");
        repolish(ui->err_tip);
    }
}

void RegisterDialog::on_get_code_clicked()
{
    auto email = ui->email_label->text();
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.)(\w+)+)");
    bool match = regex.match(email).hasMatch();
    if(match)
    {
        // 发送验证码
    }else{
        showTip("your email format is wrong",false);
    }
}

