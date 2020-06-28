#ifndef BOOK_H
#define BOOK_H

#include <QObject>
#include <QJsonObject>
#include <QDebug>

#include "Photo.h"
#include "Chapter.h"
#include "../Extensions/Data.h"


class Book : public QObject
{
    Q_OBJECT

#ifdef BIBLE_HARD
    QVector<Photo> vecPhotos;
    QString path_dir_photos;
    int currentPhoto;
#endif
    QVector<Chapter> vecChapters;
    int currentChapter;
    int quantityChapters;
    QString name_en;
    QString name_ru;
    QString family_books_en;
    QString family_books_ru;
public:
    Book(const Book &other);
    explicit Book(QObject *parent = nullptr);
    explicit Book(const QJsonObject &obj);

    void operator=(const Book &other);

    void appentChapter(const Chapter &chapter);

    void setCurrentChapter(const int chapter);

    bool isNull() const;
    int getMaxChapters() const;
    QString getNameEn() const;
    QString getNameRu() const;
    QString getPathDir() const;
    QStringList getListQuantityChapters() const;
    QStringList getListVerses() const;
#ifdef BIBLE_HARD
    int getPhoto(const int chapter) const;
#endif

private:
    int countNumberOfChapters() const;
};

#endif // BOOK_H
