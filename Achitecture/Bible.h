#ifndef BIBLE_H
#define BIBLE_H

#include <QObject>
#include <QTextCodec>

#include "Extensions/Content.h"

class Bible : public QObject
{
    Q_OBJECT
    QVector<Book> vecOldTestamentBooks;
    QVector<Book> vecNewTestamentBooks;
    BibleEnums::Testament currentTestament;
    Book currentBook;
public:
    explicit Bible(QObject *parent = nullptr);

    void setCurrentTestament(const BibleEnums::Testament &testament);
    void setCurrentBook(const QString &name);
    void setCurrentChapter(const int chapter);

    Book getBook(const QString &name, const BibleEnums::Testament &testament);
    Book getNextBook(const QString nameCurrentBook) const;
    Book getPreviousBook(const QString nameCurrentBook) const;
    QStringList getListBooks() const;
    QStringList getListQuantityChapters() const;
    QStringList getListVerses() const;

};

#endif // BIBLE_H
