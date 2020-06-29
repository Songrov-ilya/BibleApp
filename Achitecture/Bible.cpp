#include "Bible.h"

Bible::Bible(QObject *parent) : QObject(parent)
{
    Content::loadContenet_ArrayBooks(&listOldTestamentBooks, BibleEnums::Old_Testament);
    Content::loadContenet_ArrayBooks(&listNewTestamentBooks, BibleEnums::New_Testament);

    //    Content::loadContentJson(&vecOldTestamentBooks, BibleEnums::Old_Testament);
    //    Content::loadContentJson(&vecNewTestamentBooks, BibleEnums::New_Testament);
    //    Content::loadTextVersesJson(&vecOldTestamentBooks, BibleEnums::Old_Testament);
    //    Content::loadTextVersesJson(&vecNewTestamentBooks, BibleEnums::New_Testament);

//        Content::generateContenet_Info();

    createAllBooks();
}

QVector<Book>::iterator Bible::getBook(const int number, const BibleEnums::Testament testament)
{
    QVector<Book> *vecBooks = testament == BibleEnums::New_Testament ? &vecNewTestamentBooks : &vecOldTestamentBooks;
    Q_ASSERT(vecBooks->size() >= number);
    return vecBooks->begin() + number;
}

//Book Bible::getNextBook(const QString &nameCurrentBook) const
//{
//    //    for (int var = 0; var < vecBooks.size(); ++var) {
//    //        if(vecBooks.at(var).getNameEn() == nameCurrentBook && var < vecBooks.size() - 1){
//    //            return vecBooks.at(var + 1);
//    //        }
//    //    }
//    return Book(currentBook->getNumberBook() + 1);
//}

//Book Bible::getPreviousBook(const QString nameCurrentBook) const
//{
//    //    for (int var = 0; var < vecBooks.size(); ++var) {
//    //        if(vecBooks.at(var).getNameEn() == nameCurrentBook && var > 0){
//    //            return vecBooks.at(var - 1);
//    //        }
//    //    }
//    return Book(currentBook->getNumberBook() - 1);
//}

QStringList Bible::getListBooks() const
{
    return currentTestament == BibleEnums::Old_Testament ? listOldTestamentBooks: listNewTestamentBooks;
}

void Bible::setCurrentTestament(const BibleEnums::Testament testament)
{
    currentTestament = testament;
}

void Bible::setCurrentBook(const int number)
{
    currentBook = getBook(number, currentTestament);
}

void Bible::setCurrentChapter(const int chapter)
{
    currentBook->setCurrentChapter(chapter);
}

QStringList Bible::getListQuantityChapters() const
{
    return currentBook->getListQuantityChapters();
}

QStringList Bible::getListVerses() const
{
    return currentBook->getListVerses();
}

void Bible::createAllBooks()
{
    for (int var = 0; var < BibleEnums::Old_Testament; ++var) {
        vecNewTestamentBooks.append(Book(var + 1));
    }
    for (int var = 0; var < BibleEnums::New_Testament; ++var) {
        vecNewTestamentBooks.append(Book(var + 1));
    }
}


//bool Bible::operator++()
//{
//    bool changes = false;
//    if(currentChapter < currentBook.getMaxChapters()){
//        ++currentChapter;
//        if(!currentPhoto.containsChapter(currentChapter)){
//            currentPhoto = currentBook.getPhoto(currentChapter);
//            changes = true;
//        }
//    }
//    else{
//        Book nextBook = skeleton->getNextBook(currentBook.getNameEn());
//        if(nextBook.isNull()){
//            return false;
//        }
//        currentBook = nextBook;
//        currentChapter = 1;
//        currentPhoto = currentBook.getPhoto(currentChapter);
//        changes = true;
//    }
//    return changes;
//}

//bool Bible::operator--()
//{
//    bool changes = false;
//    if(currentChapter > 1){
//        --currentChapter;
//        if(!currentPhoto.containsChapter(currentChapter)){
//            currentPhoto = currentBook.getPhoto(currentChapter);
//            changes = true;
//        }
//    }
//    else{
//        Book previousBook = skeleton->getPreviousBook(currentBook.getNameEn());
//        if(previousBook.isNull()){
//            return false;
//        }
//        currentBook = previousBook;
//        currentChapter = currentBook.getMaxChapters();
//        currentPhoto = currentBook.getPhoto(currentChapter);
//        changes = true;
//    }
//    return changes;
//}
