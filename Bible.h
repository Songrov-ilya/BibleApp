#ifndef BIBLE_H
#define BIBLE_H

#include <QObject>

#include "Skeleton.h"

class Bible : public QObject
{
    Q_OBJECT
    Skeleton *skeleton;
    Book currentBook;
    Photo currentPhoto;
    int currentChapter;
public:
    explicit Bible(QObject *parent = nullptr);
    ~Bible();

    void setCurrentBook(const QString &name);
    bool setCurrentChapter(const int chapter);

    QStringList getListAllBooks() const;
    QStringList getListNumberOfChapters() const;
    QString getCurrentPathPhoto() const;
    QString getCurrentBook() const;
    int getCurrentChapter() const;


    bool operator++();
    bool operator--();

};

#endif // BIBLE_H
