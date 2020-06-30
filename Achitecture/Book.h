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
    bool wasLoadedPhotos;
#endif
    QVector<ChapterText> vecChapters;
    bool wasLoadedChapters;
    int indexBook;
    int currentChapterIndex;
    InfoBook infoBook;
public:
    explicit Book(const int indexBook);

    void setCurrentChapter(const int chapterIndex);
#ifdef BIBLE_HARD
    void loadContentPhotos(const QJsonObject &objPhotos, const QString &path_dir_photos);
    int getPhoto(const int chapterIndex) const;
#endif
    void loadContentChapterText(const QJsonArray &arrChapters);
    void loadContentInfo(const QJsonObject &obj);

    bool wasLoaded();
    int getIndexBook() const;
    QStringList getListQuantityChapters() const;
    QStringList getListVerses() const;
};

#endif // BOOK_H
