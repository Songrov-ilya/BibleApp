#ifndef PHOTO_H
#define PHOTO_H

#include <QObject>
#include <QVector>
#include <QJsonObject>

class Photo
{
    QVector<int> vecChapter;
    QString pathPhoto;
public:
    explicit Photo();
    explicit Photo(const QString &pathPhoto, const QString &strOnePhoto);
    inline void setPhoto(const QString &pathPhoto, const QString &strOnePhoto);

    bool containsChapter(const int chapter) const;
    QString getPathPhoto() const;
    int getQuantityChapters() const;

    void operator=(const Photo &other);
};

#endif // PHOTO_H
