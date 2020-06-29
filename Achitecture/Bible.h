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
    QStringList listOldTestamentBooks;
    QStringList listNewTestamentBooks;
    BibleEnums::Testament currentTestament;
    QVector<Book>::iterator currentBook;
public:
    explicit Bible(QObject *parent = nullptr);

    void setCurrentTestament(const BibleEnums::Testament testament);
    void setCurrentBook(const int indexBook);
    void setCurrentChapter(const int chapter);

    QVector<Book>::iterator getBook(const int indexBook, const BibleEnums::Testament testament);
//    Book getNextBook(const QString &nameCurrentBook) const;
//    Book getPreviousBook(const QString nameCurrentBook) const;
    QStringList getListBooks() const;
    QStringList getListQuantityChapters() const;
    QStringList getListVerses() const;

private:
    void createAllBooks();
};

#endif // BIBLE_H
