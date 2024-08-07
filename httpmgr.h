#ifndef HTTPMGR_H
#define HTTPMGR_H
#include "singleton.h"
#include <QString>
#include <QUrl>
#include <QObject>
#include <QNetworkAccessManager>// 网络管理
#include <QJsonObject>
#include <QJsonDocument>

// CRTP奇异递归模板
class HttpMgr : public QObject ,public Singleton<HttpMgr> ,
        public std::enable_shared_from_this<HttpMgr>
{
    Q_OBJECT
public:
    ~HttpMgr();

private:
    friend class Singleton<HttpMgr>;// 使用友元是为了让父类能够调用子类的构造函数去构造单例
    QNetworkAccessManager _manager;

private:
    HttpMgr();
    void PostHttpReq(QUrl url, QJsonObject json , ReqId req_id , Modules mod); // json req_id是功能 modules是模块

private slots:
    void slot_http_finish(ReqId id , QString res , ErrorCodes err ,Modules mod);

signals:
    void sig_http_finish(ReqId id , QString res , ErrorCodes err ,Modules mod);// 当一个Http发送完成之后，会发送该信号给其他模块做界面上的显示等功能
    void sig_reg_mod_finish(ReqId id , QString res , ErrorCodes err);
};

#endif // HTTPMGR_H
