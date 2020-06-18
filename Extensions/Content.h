#ifndef CONTENT_H
#define CONTENT_H

#include <QObject>
#include <QJsonDocument>
#include <QFileInfo>
#include <QJsonObject>

#include "Data.h"
#include "../Helper.h"
#include "../Achitecture/Book.h"

class Content : public QObject
{
    Q_OBJECT
public:
    explicit Content(QObject *parent = nullptr);

    static void generateContentJson(const QString pathDir);
    static void loadContentJson(QVector<Book> *vecBooks, const BibleEnums::Testament &testament);
    static void loadTextVersesJson(QVector<Book> *vecBooks, const BibleEnums::Testament &testament);

private:
    static QStringList getListDirectoryContents(const QString &dir);
    static void fillChapters(QJsonObject *objChapters, const QString &pathDir);
signals:

};

#endif // CONTENT_H
