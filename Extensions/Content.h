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

    static void generateContenet_JsonText();
    static void generateContent_Photos();
    static void loadContentJson(QVector<Book> *vecBooks, const BibleEnums::Testament &testament);
    static void loadTextVersesJson(QVector<Book> *vecBooks, const BibleEnums::Testament &testament);

private:
    static QStringList getListFileInDirectory(const QString &dir);
    static void fillPhotos(QJsonObject *objBook, const QString &pathDir);
signals:

};

#endif // CONTENT_H
