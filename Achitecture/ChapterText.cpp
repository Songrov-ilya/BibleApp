#include "ChapterText.h"


ChapterText::ChapterText(const QJsonArray &arrVerses)
{
    for (const QJsonValue &value: arrVerses) {
        listVerses.append(value.toString());
    }
}

QStringList ChapterText::getListVerses() const
{
    return listVerses;
}
