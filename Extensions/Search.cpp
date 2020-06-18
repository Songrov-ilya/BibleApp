#include "Search.h"

Search::Search(QObject *parent) :
    QObject(parent),
    arrBooks(new QJsonArray)
{
    readBibleTextJson();
}

Search::~Search()
{
    delete arrBooks;
}

void Search::generateAllBooksJson()
{
    QJsonDocument doc;
    Helper::readFileJson(&doc, File::bibleTextJson);
    QJsonArray arrMain = doc.array();

    int count = 0;
    for (const QJsonValue &book: arrMain) {
        QJsonObject objBook = book.toObject();
        Helper::writeFileJson(QJsonDocument(objBook), "../BibleApp/TextBible/Bible_XML_and_JSON/bible-master/Chapters/" + QString::number(++count) + "__" +
                              objBook.value("name").toString() + "_ru_synodal.json");
    }
}

ListOfResult Search::find(const QString &textQuery, RangeSearch range)
{
    //    [
    //        {
    //        "abbrev" : "abbrev"
    //        "name" : "book"
    //        "chapters":
    //            [
    //                ["Verse 1", "Verse 2", "Verse 3", "..."],
    //                ["Verse 1", "Verse 2", "Verse 3", "..."],
    //                ["Verse 1", "Verse 2", "Verse 3", "..."]
    //            ]
    //        },
    //        {
    //        ...
    //        },
    //    ]
    ListOfResult list { textQuery };
    if(range == RangeSearch::Verse){
        searhVerse(list, textQuery);
    }
    else if(range == RangeSearch::Chapter){
        searhChapter(list, textQuery);
    }
    return list;
}

void Search::searhVerse(ListOfResult &list, const QString &textQuery)
{
    for (const QJsonValue &book: *arrBooks) {
        QJsonObject objBook = book.toObject();
        int chapterInt = 0;
        for(const QJsonValue &chapters : objBook.value("chapters").toArray()){
            ++chapterInt;
            QJsonArray arrOneChapter = chapters.toArray();
            QString strObject {};
            int verseInt = 0;
            for(const QJsonValue &verse : arrOneChapter){
                ++verseInt;
                strObject = verse.toString();
                int ret = strObject.indexOf(textQuery, 0, Qt::CaseInsensitive);
                if(ret != -1){
                    list.addResult(objBook.value("name").toString(), chapterInt, verseInt, verseInt, verse.toString());
                }
            }
        }
    }
}

void Search::searhVerse(ListOfResult &list, const QString &nameBook, const QString &textQuery)
{
    for (const QJsonValue &book: *arrBooks) {
        QJsonObject objBook = book.toObject();
        if(objBook.value("name").toString() != nameBook){
            continue;
        }
        int chapterInt = 0;
        for(const QJsonValue &chapters : objBook.value("chapters").toArray()){
            ++chapterInt;
            QJsonArray arrOneChapter = chapters.toArray();
            QString strObject {};
            int verseInt = 0;
            for(const QJsonValue &verse : arrOneChapter){
                ++verseInt;
                strObject = verse.toString();
                int ret = strObject.indexOf(textQuery, 0, Qt::CaseInsensitive);
                if(ret != -1){
                    list.addResult(objBook.value("name").toString(), chapterInt, verseInt, verseInt, verse.toString());
                    return;
                }
            }
        }
    }
}

void Search::searhChapter(ListOfResult &list, const QString &textQuery)
{
    Result resutl;
    for (const QJsonValue &book: *arrBooks) {
        QJsonObject objBook = book.toObject();
        resutl.book = objBook.value("name").toString();
        int chapterInt = 0;
        for(const QJsonValue &chapter : objBook.value("chapters").toArray()){
            ++chapterInt;
            resutl.chapter = chapterInt;
            QJsonArray arrOneChapter = chapter.toArray();
            int ret { -1 };
            while (true) {
                ret = findTextQueryIntoChapter(ret + 1, resutl, textQuery, arrOneChapter);
                if(ret == -1){
                    break;
                }
                list.addResult(resutl);
            }
        }
    }
}

int Search::findTextQueryIntoChapter(const int pos, Result &resutl, const QString &textQuery, const QJsonArray &arrOneChapter)
{
    QString appendingVerses {};
    int verseEnd = 0;
    int countCharsVerses = 0;
    int ret = -1;
    for (int var = 0; var < arrOneChapter.size(); ++var) {
        QString verse = arrOneChapter.at(var).toString();
        appendingVerses += verse + (var - 1 < arrOneChapter.size() ? " " : "");
        if(pos > appendingVerses.size()){
            continue;
        }
        ret = appendingVerses.indexOf(textQuery, pos, Qt::CaseInsensitive);
        if(ret != -1){
            countCharsVerses += verse.size();
            verseEnd = var;
            int countQuerySymbols = textQuery.size();
            int countQuerySymbolsIntoVerse = countQuerySymbols - countCharsVerses;
            for (int varReverse = verseEnd; varReverse > 0;) {
                if(countQuerySymbolsIntoVerse <= 0){
                    resutl.verseBegin = varReverse;
                    resutl.verseEnd = verseEnd;
                    resutl.textRangeVerses = fillTextRangeVerses(arrOneChapter, varReverse, verseEnd);
                    return ret;
                }
                --varReverse;
                countQuerySymbols = countQuerySymbols - countQuerySymbolsIntoVerse;
                countQuerySymbolsIntoVerse = countQuerySymbols - arrOneChapter.at(varReverse).toString().size();
            }
            break;
        }
    }
    return ret;
}

QString Search::fillTextRangeVerses(const QJsonArray &arrOneChapter, const int verseBegin, const int verseEnd)
{
    QString text;
    for (int var = verseBegin; var <= verseEnd; ++var) {
        if(var < arrOneChapter.size()){
            text += arrOneChapter.at(var).toString() + (verseBegin != verseEnd ? " " : "");
        }
    }
    return text;
}


void Search::readBibleTextJson()
{
    QJsonDocument doc;
    Helper::readFileJson(&doc, File::bibleTextJson);
    *arrBooks = doc.array();
}

ListOfResult::ListOfResult(const QString &textQuery)
{
    this->textQuery = textQuery;
}

void ListOfResult::addResult(const Result &result)
{
    vectResult.append(result);
}

void ListOfResult::addResult(const QString book, const int chapter, const int verseBegin, const int verseEnd,
                             const QString &textRangeVerses)
{
    Result result;
    result.book = book;
    result.chapter = chapter;
    result.verseBegin = verseBegin;
    result.verseEnd = verseEnd;
    result.textRangeVerses = textRangeVerses;
    vectResult.append(result);
}

void ListOfResult::printResult(bool showTextQuery)
{
    int count { 0 };
    for (const Result &result : vectResult) {
        QString rangeVerses = QString::number(result.verseBegin + 1);
        if(result.verseBegin != result.verseEnd){
            rangeVerses += "-" + QString::number(result.verseEnd + 1);
        }
        qDebug() << ++count << result.book + " (" + QString::number(result.chapter) + ":" +
                    rangeVerses + ")";
        if (showTextQuery) {
            qDebug() << textQuery;
        }
        qDebug() << result.textRangeVerses << Qt::endl;
    }
}
