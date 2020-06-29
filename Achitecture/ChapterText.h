#ifndef CHAPTERTEXT_H
#define CHAPTERTEXT_H

#include <QObject>
#include <QJsonArray>

class ChapterText
{
    QStringList listVerses;
public:
    ChapterText(const QJsonArray &arrVerses);

    QStringList getListVerses() const;
};

#endif // CHAPTERTEXT_H
