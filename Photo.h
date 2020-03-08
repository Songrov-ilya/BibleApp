#ifndef PHOTO_H
#define PHOTO_H

#include <QObject>
#include <QVector>
#include <QJsonObject>

class Photo : public QObject
{
    Q_OBJECT
    QVector<int> vecChapter;
    QString pathPhoto;
public:
    Photo(const Photo &other);
    explicit Photo(QObject *parent = nullptr);
    explicit Photo(const QString pathPhoto, const QString strOnePhoto);
    void setPhoto(const QString pathPhoto, const QString strOnePhoto);

    bool containsChapter(const int chapter) const;
    QString getPathPhoto() const;
    int getNumberOfChapters() const;

    void operator=(const Photo &other);
};

#endif // PHOTO_H
