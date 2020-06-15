#include "Photo.h"

Photo::Photo(QObject *parent) : QObject(parent)
{

}

Photo::Photo(const Photo &other) : QObject(other.parent())
{
    *this = other;
}

Photo::Photo(const QString pathPhoto, const QString strOnePhoto) : QObject(nullptr)
{
    setPhoto(pathPhoto, strOnePhoto);
}

void Photo::setPhoto(const QString pathPhoto, const QString strOnePhoto)
{
    vecChapter.clear();
    if(strOnePhoto.isEmpty()){
        return;
    }
    this->pathPhoto = pathPhoto;
    for (const QString &str : strOnePhoto.split(",")) {
        vecChapter.push_back(str.toInt());
    }
}

bool Photo::containsChapter(const int chapter) const
{
    return vecChapter.contains(chapter);
}

QString Photo::getPathPhoto() const
{
    return pathPhoto;
}

int Photo::getNumberOfChapters() const
{
    return vecChapter.size();
}

void Photo::operator=(const Photo &other)
{
    this->vecChapter = other.vecChapter;
    this->pathPhoto = other.pathPhoto;
}

