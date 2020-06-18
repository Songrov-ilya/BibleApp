#ifndef SKELETON_H
#define SKELETON_H

#include <QObject>
#include <QTextCodec>

#include "Extensions/Content.h"

class Skeleton : public QObject
{
    Q_OBJECT
    QVector<Book> vecOldTestamentBooks;
    QVector<Book> vecNewTestamentBooks;
public:
    explicit Skeleton(QObject *parent = nullptr);

    Book getBook(const QString &name, const BibleEnums::Testament &testament);
    Book getNextBook(const QString nameCurrentBook) const;
    Book getPreviousBook(const QString nameCurrentBook) const;
    QStringList getListBooks(const BibleEnums::Testament &testament) const;

};

#endif // SKELETON_H
