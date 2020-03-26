#ifndef SKELETON_H
#define SKELETON_H

#include <QObject>
#include <QTextCodec>

#include "Helper.h"
#include "Book.h"

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

    void loadTableOfContents();
    void generateContent(QString pathDir);
    QStringList getListDirectoryContents(const QString dir);
    void fillChapters(QJsonObject &objChapters, QString pathDir);

    void readBibleTextJson();

};

#endif // SKELETON_H
