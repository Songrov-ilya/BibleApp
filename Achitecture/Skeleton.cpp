#include "Skeleton.h"

Skeleton::Skeleton(QObject *parent) : QObject(parent)
{
    Content::loadContentJson(&vecOldTestamentBooks, BibleEnums::Old_Testament);
    Content::loadContentJson(&vecNewTestamentBooks, BibleEnums::New_Testament);
    Content::loadTextVersesJson(&vecOldTestamentBooks, BibleEnums::Old_Testament);
    Content::loadTextVersesJson(&vecNewTestamentBooks, BibleEnums::New_Testament);
}

Book Skeleton::getBook(const QString &name, const BibleEnums::Testament &testament)
{
    const QVector<Book> *vecBooks { testament == BibleEnums::New_Testament ? &vecNewTestamentBooks : &vecOldTestamentBooks };
    auto it = std::find_if(vecBooks->begin(), vecBooks->end(),
                 [name](const Book &book){ return book.getNameRu() == name; });
    return it == vecBooks->end() ? Book() : *it;
}

Book Skeleton::getNextBook(const QString nameCurrentBook) const
{
//    for (int var = 0; var < vecBooks.size(); ++var) {
//        if(vecBooks.at(var).getNameEn() == nameCurrentBook && var < vecBooks.size() - 1){
//            return vecBooks.at(var + 1);
//        }
//    }
//    return Book{};
}

Book Skeleton::getPreviousBook(const QString nameCurrentBook) const
{
//    for (int var = 0; var < vecBooks.size(); ++var) {
//        if(vecBooks.at(var).getNameEn() == nameCurrentBook && var > 0){
//            return vecBooks.at(var - 1);
//        }
//    }
//    return Book{};
}

QStringList Skeleton::getListBooks(const BibleEnums::Testament &testament) const
{
    const QVector<Book> *vecBooks { testament == BibleEnums::New_Testament ? &vecNewTestamentBooks : &vecOldTestamentBooks };
    QStringList list;
    for (const Book &book: *vecBooks) {
        list.append(book.getNameRu());
    }
    return list;
}

