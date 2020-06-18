#ifndef CHAPTER_H
#define CHAPTER_H

#include <QObject>
#include <QJsonArray>

class Chapter
{
    QStringList listVerses;
public:
    Chapter(const QJsonArray &arrVerses);

    QStringList getListVerses() const;
};

#endif // CHAPTER_H
