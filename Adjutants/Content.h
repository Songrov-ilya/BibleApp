#ifndef CONTENT_H
#define CONTENT_H

#include <QObject>
#include <QJsonDocument>
#include <QFileInfo>
#include <QDir>
#include <QJsonObject>

#include "Data.h"
#include "FileWorker.h"
#include "Book.h"

#ifdef QT_DEBUG
#include <QApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QUrl>
#endif

class Content
{
    enum FamilyBooks{
        Pentateuch = 5,
        HistoricalBooks = 17,
        Wisdom = 22,
        MajorProphets = 27,
        MinorProphets = 39,

        GospelsAndActs = 44,
        PaulineEpistles = 58,
        CatholicEpistles = 65,
        Apocalypse = 66,
    };
public:
    enum TypeContent{
        GITHUB_BIBLE_XML_AND_JSON,
        BIBLEONLINE_RU,
    };
    enum Standard {
        Western,
        EasternSynodal,
    };
#ifdef QT_DEBUG
    static QNetworkAccessManager mngr;
    static void generateOnlineContent();

    static void generateContent_Photos();
    static void generateNewNameFolder_Photos();

    static void generateContentStandart(const Content::Standard standart, const TypeContent typeContent);
    static void generateContent_Folders();
    static void generateContent_Info(const Content::Standard standart);
    static void generateContent_Info_Online(const Content::Standard standart);
    static void generateContent_JsonText(const Content::Standard standart);
    static void generateContent_JsonText_Online(const Content::Standard standart);
    static void generateContent_TwoArraysBooks(const TypeContent typeContent);
#endif

    static void loadContent_Photos(QVector<Book> *vecBooks, const BibleEnums::Testament testament);
    static void loadContenet_ArrayBooks(QStringList *list, const BibleEnums::Testament testament);
    static void loadContenet_OneBook(Book *book, const BibleEnums::Testament testament);

    static void loadTextVersesJson(QVector<Book> *vecBooks, const BibleEnums::Testament testament);

private:
    static QStringList getListFileInDirectory(const QString &dir);
    static void fillPhotos(QJsonObject *objBook, const QString &pathDir);
    static QString getIndexBookStr(const int indexBook);
    static QString getIndexBookStr(int indexBook, const BibleEnums::Testament testament, const Content::Standard standart);
#ifdef QT_DEBUG
    static QVector<QString> getVectorFamilyBooks(const FamilyBooks familyBooks);
    static QString getNameFamilyBooks(const FamilyBooks familyBooks, const QString &language);
    static void getOnlineBookList();
    static void getOnlineBible();
    static void sendGetRequest(const QString &urlStr, const QByteArray &paramJson,
                               std::function<void (QNetworkReply *)> funcSlotReply);
private slots:
    static void slotSSLErrors(QNetworkReply *reply, const QList<QSslError> &errors);
    static void slotGetReply(QNetworkReply* reply);
#endif
};

#endif // CONTENT_H
