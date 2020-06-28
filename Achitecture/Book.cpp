#include "Book.h"

Book::Book(const Book &other) : QObject(nullptr)
{
    *this = other;
}

Book::Book(QObject *parent) : QObject(parent),
    quantityChapters(0),
    name_ru(""),
    family_books_en(""),
    family_books_ru(""),
    path_dir_photos("")
{

}

Book::Book(const QJsonObject &obj) : Book(nullptr)
{
    name_en                 = obj.value("name_en").toString();
    name_ru                 = obj.value("name_ru").toString();
    family_books_en           = obj.value("family_books_en").toString();
    family_books_ru           = obj.value("family_books_ru").toString();
    path_dir_photos         = obj.value("path_dir_photos").toString();
    QJsonObject objPhotos   = obj.value("photos").toObject();
    for (const QString &key : objPhotos.keys()) {
        Photo photo(path_dir_photos + "/" + key, objPhotos.value(key).toString());
#ifdef BIBLE_HARD
        vecPhotos.push_back(photo);
#endif
    }
    quantityChapters = countNumberOfChapters();
}


void Book::operator=(const Book &other)
{
#ifdef BIBLE_HARD
    this->vecPhotos     = other.vecPhotos;
#endif
    this->vecChapters   = other.vecChapters;
    this->quantityChapters   = other.quantityChapters;
    this->name_en       = other.name_en;
    this->name_ru       = other.name_ru;
    this->family_books_en = other.family_books_en;
    this->family_books_ru = other.family_books_ru;
    this->path_dir_photos      = other.path_dir_photos;
}

void Book::appentChapter(const Chapter &chapter)
{
    vecChapters.append(chapter);
}

void Book::setCurrentChapter(const int chapter)
{
    currentChapter = chapter;
#ifdef BIBLE_HARD
    currentPhoto   = getPhoto(chapter);
#endif
}

bool Book::isNull() const
{
    if(quantityChapters <= 0){
        return true;
    }
    return false;
}

int Book::getMaxChapters() const
{
    return quantityChapters;
}

QString Book::getNameEn() const
{
    return name_en;
}

QString Book::getNameRu() const
{
    return name_ru;
}

QString Book::getPathDir() const
{
    return path_dir_photos;
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

#ifdef BIBLE_HARD
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

int Book::countNumberOfChapters() const
{
    int count {0};
#ifdef BIBLE_HARD
    for (const Photo &photo: vecPhotos) {
        count += photo.getNumberOfChapters();
    }
#endif
    return count;
}
