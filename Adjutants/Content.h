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
#include <QThread>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QUrl>
#endif

class Content
{
    enum FamilyBooks { // Standard::Western
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
    enum TypeContent {
        GITHUB_BIBLE_USFM2JSON_RUSLAN_KAZAKOV, // пока самое точное!
        GITHUB_BIBLE_XML_AND_JSON_THIAGO_BODRUK, // здесь много ошибок
        BIBLEONLINE_RU, // здесь вообще не доделанное API
    };
    enum Standard {
        Western,
        EasternSynodal,
    };
#ifdef QT_DEBUG
    static void generateContentStandart(const Content::Standard requiredStandart, const TypeContent typeContent);
#endif
    static void loadContent_Photos(QVector<Book> *vecBooks, const BibleEnums::Testament testament);
    static void loadContenet_ArrayBooks(QStringList *list, const BibleEnums::Testament testament);
    static void loadContenet_OneBook(Book *book, const BibleEnums::Testament testament);
    static void loadTextVersesJson(QVector<Book> *vecBooks, const BibleEnums::Testament testament);

private:
    static QStringList getListFileInDirectory(const QString &dir);
    static void fillPhotos(QJsonObject *objBook, const QString &pathDir);
    static QString getIndexBookStr(const int indexBook);
    static QString getIndexBookStr(int indexBook, const BibleEnums::Testament testament,
                                   const Content::Standard currentStandart, const Content::Standard requiredStandart);

#ifdef QT_DEBUG
    static QNetworkAccessManager mngr;
    static void generateContent_Photos();
    static void generateNewNameFolder_Photos();

    static void generateContent_Folders(const TypeContent typeContent);
    static void generateContent_Info_BODRUK(const Content::Standard requiredStandart);
    static void generateContent_Info_ONLINE(const Content::Standard requiredStandart);
    static void generateContent_Info_KAZAKOV(const Content::Standard requiredStandart);
    static void generateContent_JsonText_BODRUK(const Content::Standard requiredStandart);
    static void generateContent_JsonText_ONLINE(const Content::Standard requiredStandart);
    static void generateContent_JsonText_KAZAKOV(const Content::Standard requiredStandart);
    static void generateContent_TwoArraysBooks(const TypeContent typeContent);

    static QVector<QString> getVectorFamilyBooks(const FamilyBooks familyBooks);
    static QString getNameFamilyBooks(const FamilyBooks familyBooks, const QString &language);
    static void getOnlineBookList();
    static void getOnlineBible();
    static void generateValidJson_KAZAKOV();
    static void sendGetRequest(const QString &urlStr, const QByteArray &paramJson,
                               std::function<void (QNetworkReply *)> funcSlotReply);
    static void slotSSLErrors(QNetworkReply *reply, const QList<QSslError> &errors);
    static void slotGetReply(QNetworkReply* reply);
#endif
};

#endif // CONTENT_H
