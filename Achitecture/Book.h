#ifndef BOOK_H
#define BOOK_H

#include <QObject>
#include <QJsonObject>
#include <QDebug>

#include "Photo.h"
#include "ChapterText.h"
#include "../Extensions/Data.h"

struct InfoBook{
    QString abbrev;
    QString name_en;
    QString name_ru;
    QString family_books_en;
    QString family_books_ru;
};

class Book
{
#ifdef BIBLE_HARD
    QVector<Photo> vecPhotos;
    QString path_dir_photos;
    int currentPhoto;
#endif
    QVector<ChapterText> vecChapters;
    int numberBook;
    int currentChapter;
    int quantityChapters;
    InfoBook infoBook;
public:
    explicit Book(const int numberBook);

#ifdef BIBLE_HARD
    void setContentPhotos(const QJsonObject &objPhotos, const QString &path_dir_photos);
    int getPhoto(const int chapter) const;
#endif
    void setContentChapterText(const QJsonArray &arr);
    void setContentInfo(const QJsonObject &obj);
    void setCurrentChapter(const int chapter);

    int getNumberBook() const;
    QStringList getListQuantityChapters() const;
    QStringList getListVerses() const;
};

#endif // BOOK_H
