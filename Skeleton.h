#ifndef SKELETON_H
#define SKELETON_H

#include <QObject>
#include <QTextCodec>

#include "Extensions/Content.h"

class Skeleton : public QObject
{
    Q_OBJECT
    QVector<Book> vecBooks;
public:
    explicit Skeleton(QObject *parent = nullptr);

    Book getBook(const QString name);
    Book getNextBook(const QString nameCurrentBook) const;
    Book getPreviousBook(const QString nameCurrentBook) const;
    QStringList getListBooks() const;

};

#endif // SKELETON_H
