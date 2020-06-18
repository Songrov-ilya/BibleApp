#include "ModelView.h"

ModelView::ModelView(QObject *parent) :
    QAbstractListModel(parent),
    mList(nullptr)
{

}

int ModelView::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    return mList->getSize();
}

QVariant ModelView::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    switch (role) {
    case TextModel:
        return QVariant(mList->getText(index.row()));
    }

    return QVariant();
}

bool ModelView::setData(const QModelIndex &, const QVariant &, int)
{
    if (!mList)
        return false;

//    emit dataChanged(index, index, QVector<int>() << role);

    return false;
}

Qt::ItemFlags ModelView::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> ModelView::roleNames() const
{
    QHash<int, QByteArray> names;
    names[TextModel] = "textModel";
    return names;
}

BibleList *ModelView::list() const
{
    return mList;
}

void ModelView::setList(BibleList *list)
{
    beginResetModel();

    if (mList){
        mList->disconnect(this);
    }

    mList = list;

    if (mList) {

        connect(mList, &BibleList::preResetModel, this, [=]() {
            beginResetModel();
        });
        connect(mList, &BibleList::postResetModel, this, [=]() {
            endResetModel();
        });

        connect(mList, &BibleList::preSetItems, this, [=](int count) {
            const int index = mList->getSize();
            beginInsertRows(QModelIndex(), index, index + count - 1);
        });
        connect(mList, &BibleList::postSetItems, this, [=]() {
            endInsertRows();
        });
    }

    endResetModel();
}
