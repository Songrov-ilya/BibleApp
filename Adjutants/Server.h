#pragma once

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QUrl>

class Server : public QObject
{
    Q_OBJECT

    QNetworkAccessManager mngr;
public:
    explicit Server(QObject *parent = nullptr);

    void getOnlineBookList();

private:
    void sendGetRequest(const QString &urlStr, const QByteArray &paramJson, std::function<void (QNetworkReply *)> funcSlotReply);
//    void parseReplyOnlineBookLists(QNetworkReply *reply);
//    void parseReplySetMarker(QNetworkReply *reply);

private slots:
    void slotSSLErrors(QNetworkReply *reply, const QList<QSslError> &errors);
    void slotReplyOnlineBookList(QNetworkReply* reply);
//    void slotReplySetMarkerFinished(QNetworkReply* reply);
};

