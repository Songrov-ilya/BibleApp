#include "Skeleton.h"

Skeleton::Skeleton(QObject *parent) : QObject(parent)
{
    Content::loadContentJson(vecBooks);
}

Book Skeleton::getBook(const QString name)
{
    for (const Book &book: vecBooks) {
        if(book.getNameEn() == name){
            return book;
        }
    }
    return Book();
}

Book Skeleton::getNextBook(const QString nameCurrentBook) const
{
    for (int var = 0; var < vecBooks.size(); ++var) {
        if(vecBooks.at(var).getNameEn() == nameCurrentBook && var < vecBooks.size() - 1){
            return vecBooks.at(var + 1);
        }
    }
    return Book{};
}

Book Skeleton::getPreviousBook(const QString nameCurrentBook) const
{
    for (int var = 0; var < vecBooks.size(); ++var) {
        if(vecBooks.at(var).getNameEn() == nameCurrentBook && var > 0){
            return vecBooks.at(var - 1);
        }
    }
    return Book{};
}

QStringList Skeleton::getListBooks() const
{
    QStringList list;
    for (const Book &book: vecBooks) {
        list.append(book.getNameEn());
    }
    return list;
}

