#include "Bible.h"

Bible::Bible(QObject *parent) : QObject(parent)
{
#ifdef QT_DEBUG
//    Content::generateContentStandart(Content::EasternSynodal, Content::GITHUB_BIBLE_XML_AND_JSON_THIAGO_BODRUK);
    Content::generateContentStandart(Content::EasternSynodal, Content::GETBIBLE_NET);
#endif

    Content::loadContenet_ArrayBooks(&listOldTestamentBooks, BibleEnums::Old_Testament);
    Content::loadContenet_ArrayBooks(&listNewTestamentBooks, BibleEnums::New_Testament);

    createAllBooks();
}

QVector<Book>::iterator Bible::getBook(const int indexBook, const BibleEnums::Testament testament)
{
    QVector<Book> *vecBooks = testament == BibleEnums::New_Testament ? &vecNewTestamentBooks : &vecOldTestamentBooks;
    Q_ASSERT(vecBooks->size() < indexBook || indexBook >= 0);
    auto itBook = vecBooks->begin() + indexBook;
    if (!itBook->wasLoaded()) {
        Content::loadContenet_OneBook(itBook, testament);
    }
    return itBook;
}

BibleEnums::Testament Bible::getCurrentTestament() const
{
    return currentTestament;
}

QVector<Book>::iterator Bible::getCurrentBook() const
{
    return currentBook;
}

int Bible::getCurrentIndexBook() const
{
    return currentBook->getIndexBook();
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

void Bible::setCurrentBook(const int indexBook)
{
    currentBook = getBook(indexBook, currentTestament);
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
        vecOldTestamentBooks.append(Book(var));
    }
    for (int var = 0; var < BibleEnums::New_Testament; ++var) {
        vecNewTestamentBooks.append(Book(var));
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
