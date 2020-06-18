#include "Chapter.h"

Chapter::Chapter(const QJsonArray &arrVerses)
{
    for (const QJsonValue &value: arrVerses) {
        listVerses.append(value.toString());
    }
}

QStringList Chapter::getListVerses() const
{
    return listVerses;
}
