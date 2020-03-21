#ifndef BOOK_H
#define BOOK_H

#include <QObject>
#include <QJsonObject>
#include <QDebug>

#include "Photo.h"

class Book : public QObject
{
    Q_OBJECT

    QVector<Photo> vecPhotos;
    int maxChapters;
    QString name_en;
    QString name_ru;
    QString other_info_en;
    QString other_info_ru;
    QString path_dir;
public:
    Book(const Book &other);
    explicit Book(QObject *parent = nullptr);
    explicit Book(QJsonObject obj);

    void operator=(const Book &other);

    bool isNull() const;
    int getMaxChapters() const;
    QString getNameEn() const;
    QString getPathDir() const;
    QStringList getListNumberOfChapters() const;
    Photo getPhoto(const int chapter) const;

private:
    int countNumberOfChapters() const;
};

#endif // BOOK_H
