#ifndef CONTENT_H
#define CONTENT_H

#include <QObject>
#include <QJsonDocument>
#include <QFileInfo>
#include <QJsonObject>

#include "Data.h"
#include "../Helper.h"
#include "../Achitecture/Book.h"

class Content
{
public:
    static void generateContent_Photos();
    static void generateNewNameFolder_Photos();
    static void generateContenet_Info();
    static void generateContenet_JsonText();
    static void generateContenet_TwoArraysBooks();

    static void loadContent_Photos(QVector<Book> *vecBooks, const BibleEnums::Testament testament);
    static void loadContenet_ArrayBooks(QStringList *list, const BibleEnums::Testament testament);
    static void loadContenet_OneBook(QVector<Book> *vecBooks, const int numBook, const BibleEnums::Testament testament);

    static void loadTextVersesJson(QVector<Book> *vecBooks, const BibleEnums::Testament testament);

private:
    static QStringList getListFileInDirectory(const QString &dir);
    static void fillPhotos(QJsonObject *objBook, const QString &pathDir);

};

#endif // CONTENT_H
