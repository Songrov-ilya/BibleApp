#include "BibleList.h"

BibleList::BibleList(QObject *parent) : QObject(parent)
{

}

void BibleList::appendElement(const QString &text)
{
    emit preSetItems(1);
    this->list.append(text);
    emit postSetItems();
}

void BibleList::appendList(const QStringList &list)
{
    emit preSetItems(list.size());
    this->list += list;
    emit postSetItems();
}


void BibleList::clearListBible()
{
    emit preResetModel();
    this->list.clear();
    emit postResetModel();
}

QString BibleList::getText(const int index)
{
    return list.at(index);
}

int BibleList::getSize() const
{
    return list.size();
}
