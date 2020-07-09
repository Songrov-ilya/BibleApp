#include "Server.h"

Server::Server(QObject *parent) : QObject(parent)
{

}


void Server::getOnlineBookList()
{
    const QString url { "https://api.bibleonline.ru/booklist" };
    const QJsonDocument docParam({
                                     { "callback", "bible" },
                                     { "trans", "lut" }
                                 });
    sendGetRequest(url, docParam.toJson(), std::bind(&Server::slotReplyOnlineBookList, this, std::placeholders::_1));
}

void Server::sendGetRequest(const QString &urlStr, const QByteArray &paramJson, std::function<void (QNetworkReply *)> funcSlotReply)
{
    const QString header { "application/json" };
    qDebug() << "send param Utf8" << Qt::endl << qPrintable(QJsonDocument::fromJson(paramJson).toJson());
    QUrl url(urlStr);
    QUrlQuery query(paramJson);
    url.setQuery(query.query());
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, header);
    mngr.get(request);
    connect(&mngr, &QNetworkAccessManager::sslErrors, this, &Server::slotSSLErrors);
//    connect(&mngr, &QNetworkAccessManager::finished, this, funcSlotReply);
}

void Server::slotSSLErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{

}

void Server::slotReplyOnlineBookList(QNetworkReply *reply)
{

}
