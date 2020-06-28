#include "Bible.h"

Bible::Bible(QObject *parent) : QObject(parent)
{
//    Content::loadContentJson(&vecOldTestamentBooks, BibleEnums::Old_Testament);
//    Content::loadContentJson(&vecNewTestamentBooks, BibleEnums::New_Testament);
//    Content::loadTextVersesJson(&vecOldTestamentBooks, BibleEnums::Old_Testament);
//    Content::loadTextVersesJson(&vecNewTestamentBooks, BibleEnums::New_Testament);

    Content::generateContent_Photos();
}

Book Bible::getBook(const QString &name, const BibleEnums::Testament &testament)
{
    const QVector<Book> *vecBooks { testament == BibleEnums::New_Testament ? &vecNewTestamentBooks : &vecOldTestamentBooks };
    auto it = std::find_if(vecBooks->begin(), vecBooks->end(),
                 [name](const Book &book){ return book.getNameRu() == name; });
    return it == vecBooks->end() ? Book() : *it;
}

Book Bible::getNextBook(const QString nameCurrentBook) const
{
//    for (int var = 0; var < vecBooks.size(); ++var) {
//        if(vecBooks.at(var).getNameEn() == nameCurrentBook && var < vecBooks.size() - 1){
//            return vecBooks.at(var + 1);
//        }
//    }
    return Book{};
}

Book Bible::getPreviousBook(const QString nameCurrentBook) const
{
//    for (int var = 0; var < vecBooks.size(); ++var) {
//        if(vecBooks.at(var).getNameEn() == nameCurrentBook && var > 0){
//            return vecBooks.at(var - 1);
//        }
//    }
    return Book();
}

QStringList Bible::getListBooks() const
{
    const QVector<Book> *vecBooks { currentTestament == BibleEnums::New_Testament ? &vecNewTestamentBooks : &vecOldTestamentBooks };
    QStringList list;
    for (const Book &book: *vecBooks) {
        list.append(book.getNameRu());
    }
    return list;
}

void Bible::setCurrentTestament(const BibleEnums::Testament &testament)
{
    currentTestament = testament;
}

void Bible::setCurrentBook(const QString &name)
{
    currentBook = getBook(name, currentTestament);
}

void Bible::setCurrentChapter(const int chapter)
{
    currentBook.setCurrentChapter(chapter);
}

QStringList Bible::getListQuantityChapters() const
{
    return currentBook.getListQuantityChapters();
}

QStringList Bible::getListVerses() const
{
    return currentBook.getListVerses();
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
