#include "httpmgr.h"

HttpMgr::~HttpMgr()
{

}

HttpMgr::HttpMgr()
{
    connect(this,&HttpMgr::sig_http_finish,this,&HttpMgr::slot_http_finish);
}

void HttpMgr::PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod)
{
    // 将json对象序列化为字节数组
    QByteArray data = QJsonDocument(json).toJson();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    // 使用QByteArray的函数会解决大端小端的问题
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(data.length()));
    auto self = shared_from_this();//35:20
    // 异步发送请求
    QNetworkReply * reply = _manager.post(request,data);
    // 判读是否完成
    QObject::connect(reply,&QNetworkReply::finished,[self,reply,req_id,mod](){// 为什么使用self而不是使用this 41:00
        // 处理错误情况
        if(reply->error() != QNetworkReply::NoError)
        {
            qDebug() << reply->errorString();
            // 发生信号给相关界面完成
            emit self->sig_http_finish(req_id,"",ErrorCodes::ERR_NETWORK,mod);
            // 因为reply还有可能用于底层的数据循环，使用deleteLater告诉QT不需要使用时回收
            reply->deleteLater();
            return;
        }

        // 无错误
        QString res = reply->readAll();
        // 发送信号通知完成
        emit self->sig_http_finish(req_id,res,ErrorCodes::SUCCESS,mod);
        reply->deleteLater();
        return;
    });

}

void HttpMgr::slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod)
{
    if(mod == Modules::REGISTERMOD)
    {
        // 发送信号通知指定模块http的响应结束了
        emit sig_reg_mod_finish(id,res,err);
    }
}
