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
        GETBIBLE_NET, // пока используем этот вариант
        GITHUB_BIBLE_USFM2JSON_RUSLAN_KAZAKOV, // ошибки с новым заветом
        GITHUB_BIBLE_XML_AND_JSON_THIAGO_BODRUK, // здесь много ошибок
        BIBLEONLINE_RU, // здесь вообще не доделанное API
    };
    enum Standard {
        Western,
        EasternSynodal,
    };
    static void loadContent_Photos(QVector<Book> *vecBooks, const BibleEnums::Testament testament);
    static void loadContenet_ArrayBooks(QStringList *list, const BibleEnums::Testament testament);
    static void loadContenet_OneBook(Book *book, const BibleEnums::Testament testament);
    static void loadTextVersesJson(QVector<Book> *vecBooks, const BibleEnums::Testament testament);

#ifdef QT_DEBUG
    static void generateContentStandart(const Content::Standard requiredStandart, const TypeContent typeContent);
    static void removeAllContent();
private:
    static QNetworkAccessManager mngr;
    static QString getIndexBookStr(const int index);
    static QString getIndexBookStr(int index, const BibleEnums::Testament testament,
                                   const Content::Standard currentStandart, const Content::Standard requiredStandart);
    static int getIndexBook(int index, const BibleEnums::Testament testament,
                            const Content::Standard currentStandart, const Content::Standard requiredStandart);
    static void testGetIndexBook();

    static void generateContent_Photos();
    static void generateNewNameFolder_Photos();
    static QStringList getListFileInDirectory(const QString &dir);
    static void fillPhotos(QJsonObject *objBook, const QString &pathDir);

    static void generateContent_Folders(const TypeContent typeContent, const bool onlyRemove = false);
    static void generateContent_Info(const QString &fileOld, const QString &fileNew, const Content::Standard requiredStandart);
    static void generateContent_Info_BODRUK(const Content::Standard requiredStandart);
    static void generateContent_Info_ONLINE(const Content::Standard requiredStandart);
    static void generateContent_Info_KAZAKOV(const Content::Standard requiredStandart);
    static void generateContent_Info_GETBIBLE(const Content::Standard requiredStandart);
    static void generateContent_JsonText(const QString &pathFrom, const QString &dirOld, const QString &dirNew,
                                         const Content::Standard currentStandart, const Content::Standard requiredStandart);
    static void generateContent_JsonText_BODRUK(const Content::Standard requiredStandart);
    static void generateContent_JsonText_ONLINE(const Content::Standard requiredStandart);
    static void generateContent_JsonText_KAZAKOV(const Content::Standard requiredStandart);
    static void generateContent_JsonText_GETBIBLE(const Content::Standard requiredStandart);
    static void generateContent_TwoArraysBooks(const TypeContent typeContent);

    static QString getAbbrev(const int index, const Content::Standard requiredStandart, const QString &language = "ru");
    static QVector<QString> getVectorFamilyBooks(const FamilyBooks familyBooks, const QString &language = "ru");
    static QString getNameFamilyBooks(const FamilyBooks familyBooks, const QString &language = "ru");
    static void getOnlineBookList();
    static void getOnlineBible();
    static void generateValidJson_KAZAKOV();
    static void generateJsonFromTxt_GETBIBLE();
    static void sendGetRequest(const QString &urlStr, const QByteArray &paramJson,
                               std::function<void (QNetworkReply *)> funcSlotReply);
    static void slotSSLErrors(QNetworkReply *reply, const QList<QSslError> &errors);
    static void slotGetReply(QNetworkReply* reply);
#endif
};

#endif // CONTENT_H
