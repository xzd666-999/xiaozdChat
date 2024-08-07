#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "global.h"
#include "httpmgr.h"
RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    ui->pass_lineEdit->setEchoMode(QLineEdit::Password);
    ui->confirm_lineEdit->setEchoMode(QLineEdit::Password);
    ui->err_tip->setProperty("state","normal");// 设置错误信息的初始状态为normal
    repolish(ui->err_tip);
    initHttpHandles();
    connect(HttpMgr::GetInstance().get(),&HttpMgr::sig_reg_mod_finish,this,&RegisterDialog::slot_reg_mod_finish);
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

void RegisterDialog::initHttpHandles()
{
    // 注册获取验证码回包的逻辑
    _handlers.insert(ReqId::ID_GET_VARIFY_CODE,[this](const QJsonObject& jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS)
        {
            showTip("can shu cuo wu",false);
            return;
        }
        auto email = jsonObj["email"].toString();
        showTip(tr("code has sent to mail"),true);
        qDebug() << "email is " << email;
    });
}

void RegisterDialog::on_get_code_clicked()
{
    auto email = ui->email_label->text();
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.)(\w+)+)");
    bool match = regex.match(email).hasMatch();
    if(match)
    {
        // 发送http验证码
    }else{
        showTip("your email format is wrong",false);
    }
}

void RegisterDialog::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err)
{
    if(err != ErrorCodes::SUCCESS)
    {
        showTip("network request error",false);
        return;
    }
    // 解析Json字符串, res 转化为QByteArray
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    if(jsonDoc.isNull())
    {
        showTip("json transferred failed",false);
        return;
    }
    // json解析错误
    if(!jsonDoc.isObject())
    {
        showTip("json transferred failed",false);
        return;
    }

    _handlers[id](jsonDoc.object());
    return;
}

