#ifndef MODELVIEW_H
#define MODELVIEW_H

#include <QObject>
#include <QAbstractListModel>

#include "View/BibleList.h"

class ModelView : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(BibleList *list READ list WRITE setList)

    BibleList *mList;
public:
    explicit ModelView(QObject *parent = nullptr);


    ModelView(ModelView const &) = delete;
    void operator=(ModelView const &) = delete;

    enum {
        Text = Qt::UserRole + 1,
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &, const QVariant &, int = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    BibleList *list() const;
    void setList(BibleList *list);

};

#endif // MODELVIEW_H
