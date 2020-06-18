#ifndef BIBLE_H
#define BIBLE_H

#include <QObject>

#include "Skeleton.h"
#include "Extensions/Search.h"

class Bible : public QObject
{
    Q_OBJECT
    Skeleton *skeleton;
    Search *search;
    BibleEnums::Testament currentTestament;
    Book currentBook;
    Photo currentPhoto;
    int currentChapter;
public:
    explicit Bible(QObject *parent = nullptr);
    ~Bible();

    void setCurrentTestament(const BibleEnums::Testament &testament);
    void setCurrentBook(const QString &name);
    bool setCurrentChapter(const int chapter);

    QStringList getListAllBooks() const;
    QStringList getListQuantityChapters() const;
    QStringList getListVerses() const;
    QString getCurrentPathPhoto() const;
    QString getCurrentBook() const;
    int getCurrentChapter() const;


    bool operator++();
    bool operator--();

};

#endif // BIBLE_H
