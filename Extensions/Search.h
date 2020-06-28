#ifndef SEARCH_H
#define SEARCH_H

#include <QObject>

#include "Data.h"
#include "../Helper.h"

struct Result {
    QString book            { "" };
    int chapter             { 0 };
    int verseBegin          { 0 };
    int verseEnd            { 0 };
    QString textRangeVerses { "" };
};

struct ListOfResult {
    QVector <Result> vectResult;
    QString textQuery { "" };

    explicit ListOfResult(const QString &textQuery);

    void addResult(const Result &result);
    void addResult(const QString book, const int chapter, const int verseBegin, const int verseEnd,
                   const QString &textRangeVerses);
    void printResult(bool showTextQuery = false);
};

class Search : public QObject
{
    Q_OBJECT
    QJsonDocument doc;
public:
    enum RangeSearch {
        Verse,
        Chapter,
    };
    explicit Search(QObject *parent = nullptr);
    ~Search();

    QStringList getListVerses();
    ListOfResult find(const QString &textQuery, RangeSearch range = RangeSearch::Verse);

private:
    void searhVerse(ListOfResult &list, const QString &textQuery);
    void searhVerse(ListOfResult &list, const QString &nameBook, const QString &textQuery);
    void searhChapter(ListOfResult &list, const QString &textQuery);

    int findTextQueryIntoChapter(const int pos, Result &resutl, const QString &textQuery, const QJsonArray &arrOneChapter);
    QString fillTextRangeVerses(const QJsonArray &arrOneChapter, const int verseBegin, const int verseEnd);
    void readBibleTextJson();

};

#endif // SEARCH_H
