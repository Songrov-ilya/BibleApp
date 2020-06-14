#include "Bible.h"

Bible::Bible(QObject *parent) : QObject(parent)
{
    skeleton = new Skeleton;
    currentChapter = 0;
    search = new Search;
//    ListOfResult list = search->find("блажен", Search::Chapter);
//    list.printResult();
}

Bible::~Bible()
{
    delete skeleton;
    delete search;
}

void Bible::setCurrentBook(const QString &name)
{
    currentBook = skeleton->getBook(name);
    currentChapter = 1;
    currentPhoto = currentBook.getPhoto(currentChapter);
}

bool Bible::setCurrentChapter(const int chapter)
{
    bool changes = false;
    if(!currentPhoto.containsChapter(chapter)){
        currentPhoto = currentBook.getPhoto(chapter);
        changes = true;
    }
    currentChapter = chapter;
    return changes;
}

QStringList Bible::getListAllBooks() const
{
    return skeleton->getListBooks();
}

QStringList Bible::getListNumberOfChapters() const
{
    return currentBook.getListNumberOfChapters();
}

QString Bible::getCurrentPathPhoto() const
{
    return currentPhoto.getPathPhoto();
}

QString Bible::getCurrentBook() const
{
    return currentBook.getNameEn();
}

int Bible::getCurrentChapter() const
{
    return currentChapter;
}

bool Bible::operator++()
{
    bool changes = false;
    if(currentChapter < currentBook.getMaxChapters()){
        ++currentChapter;
        if(!currentPhoto.containsChapter(currentChapter)){
            currentPhoto = currentBook.getPhoto(currentChapter);
            changes = true;
        }
    }
    else{
        Book nextBook = skeleton->getNextBook(currentBook.getNameEn());
        if(nextBook.isNull()){
            return false;
        }
        currentBook = nextBook;
        currentChapter = 1;
        currentPhoto = currentBook.getPhoto(currentChapter);
        changes = true;
    }
    return changes;
}

bool Bible::operator--()
{
    bool changes = false;
    if(currentChapter > 1){
        --currentChapter;
        if(!currentPhoto.containsChapter(currentChapter)){
            currentPhoto = currentBook.getPhoto(currentChapter);
            changes = true;
        }
    }
    else{
        Book previousBook = skeleton->getPreviousBook(currentBook.getNameEn());
        if(previousBook.isNull()){
            return false;
        }
        currentBook = previousBook;
        currentChapter = currentBook.getMaxChapters();
        currentPhoto = currentBook.getPhoto(currentChapter);
        changes = true;
    }
    return changes;
}



