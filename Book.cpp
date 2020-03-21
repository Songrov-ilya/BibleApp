#include "Book.h"

Book::Book(const Book &other) : QObject(nullptr)
{
    *this = other;
}

Book::Book(QObject *parent) : QObject(parent),
    maxChapters(0),
    name_ru(""),
    other_info_en(""),
    other_info_ru(""),
    path_dir("")
{

}

Book::Book(QJsonObject obj) : Book(nullptr)
{
    name_en       = obj.value("name_en").toString();
    name_ru       = obj.value("name_ru").toString();
    other_info_en = obj.value("other_info_en").toString();
    other_info_ru = obj.value("other_info_ru").toString();
    path_dir      = obj.value("path_dir").toString();
    QJsonObject objPhotos = obj.value("photos").toObject();
    for (const QString &key : objPhotos.keys()) {
        Photo photo(path_dir + "/" + key, objPhotos.value(key).toString());
        vecPhotos.push_back(photo);
    }
    maxChapters = countNumberOfChapters();
}


void Book::operator=(const Book &other)
{
    this->vecPhotos     = other.vecPhotos;
    this->maxChapters   = other.maxChapters;
    this->name_en       = other.name_en;
    this->name_ru       = other.name_ru;
    this->other_info_en = other.other_info_en;
    this->other_info_ru = other.other_info_ru;
    this->path_dir      = other.path_dir;
}

bool Book::isNull() const
{
    if(maxChapters <= 0){
        return true;
    }
    return false;
}

int Book::getMaxChapters() const
{
    return maxChapters;
}

QString Book::getNameEn() const
{
    return name_en;
}

QString Book::getPathDir() const
{
    return path_dir;
}


QStringList Book::getListNumberOfChapters() const
{
    QStringList list;
    for (int var = 0; var < maxChapters; ++var) {
        list.append(QString::number(var+1));
    }
    return list;
}

Photo Book::getPhoto(const int chapter) const
{
    for (const Photo &photo: vecPhotos) {
        if(photo.containsChapter(chapter)){
            return photo;
        }
    }

    if(chapter <= vecPhotos.size()){
        return vecPhotos.at(chapter - 1);
    }    /* finish at the end */ // удалить это условие

    return Photo();
}

int Book::countNumberOfChapters() const
{
    int count {0};
    for (const Photo &photo: vecPhotos) {
        count += photo.getNumberOfChapters();
    }
    return count;
}
