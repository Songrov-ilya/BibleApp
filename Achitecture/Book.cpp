#include "Book.h"


Book::Book(const int numberBook) :
#ifdef BIBLE_HARD
    path_dir_photos(""),
    currentPhoto(0),
#endif
    numberBook(1),
    currentChapter(1),
    quantityChapters(0),
    infoBook()
{
    this->numberBook = numberBook;
}

#ifdef BIBLE_HARD
void Book::setContentPhotos(const QJsonObject &objPhotos, const QString &path_dir_photos)
{
    for (const QString &key : objPhotos.keys()) {
        Photo photo(path_dir_photos + key, objPhotos.value(key).toString());
        vecPhotos.append(photo);
    }
    Q_ASSERT(vecPhotos.isEmpty());
    quantityChapters = vecPhotos.back().getQuantityChapters();
}

int Book::getPhoto(const int chapter) const
{
    Q_ASSERT(chapter <= vecPhotos.size() || chapter < 1);
    for (int var = 0; var < vecPhotos.size(); ++var) {
        if(vecPhotos.at(var).containsChapter(chapter)){
            return var;
        }
    }
    return 0;
}
#endif

void Book::setContentChapterText(const QJsonArray &arr)
{
    ChapterText chapterText(arr);
    vecChapters.append(chapterText);
    quantityChapters = arr.size();
}

void Book::setContentInfo(const QJsonObject &obj)
{
    infoBook.abbrev             = obj.value("abbrev").toString();
    infoBook.name_en            = obj.value("name_en").toString();
    infoBook.name_ru            = obj.value("name_ru").toString();
    infoBook.family_books_en    = obj.value("family_books_en").toString();
    infoBook.family_books_ru    = obj.value("family_books_ru").toString();
}


void Book::setCurrentChapter(const int chapter)
{
    currentChapter = chapter;
#ifdef BIBLE_HARD
    currentPhoto   = getPhoto(chapter);
#endif
}

int Book::getNumberBook() const
{
    return this->numberBook;
}

QStringList Book::getListQuantityChapters() const
{
    QStringList list;
    for (int var = 0; var < quantityChapters; ++var) {
        list.append(QString::number(var+1));
    }
    return list;
}

QStringList Book::getListVerses() const
{
    qDebug() << "chapter" << currentChapter << "vecChapters.size()" << vecChapters.size() << Qt::endl;
    Q_ASSERT(currentChapter <= vecChapters.size() || currentChapter < 1);
    return vecChapters.at(currentChapter - 1).getListVerses();
}

