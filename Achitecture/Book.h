#ifndef BOOK_H
#define BOOK_H

#include <QObject>
#include <QJsonObject>
#include <QDebug>

#include "Photo.h"
#include "Chapter.h"

class Book : public QObject
{
    Q_OBJECT

    QVector<Photo> vecPhotos;
    QVector<Chapter> vecChapters;
    int maxChapters;
    QString name_en;
    QString name_ru;
    QString other_info_en;
    QString other_info_ru;
    QString path_dir;
public:
    Book(const Book &other);
    explicit Book(QObject *parent = nullptr);
    explicit Book(const QJsonObject &obj);

    void operator=(const Book &other);

    void appentChapter(const Chapter &chapter);

    bool isNull() const;
    int getMaxChapters() const;
    QString getNameEn() const;
    QString getNameRu() const;
    QString getPathDir() const;
    QStringList getListQuantityChapters() const;
    QStringList getListVerses(const int chapter) const;
    Photo getPhoto(const int chapter) const;

private:
    int countNumberOfChapters() const;
};

#endif // BOOK_H
