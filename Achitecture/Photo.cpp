#include "Photo.h"

Photo::Photo()
{

}

Photo::Photo(const QString &pathPhoto, const QString &strOnePhoto)
{
    setPhoto(pathPhoto, strOnePhoto);
}

void Photo::setPhoto(const QString &pathPhoto, const QString &strOnePhoto)
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

int Photo::getQuantityChapters() const
{
    return vecChapter.size();
}


