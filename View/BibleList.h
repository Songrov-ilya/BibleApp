#ifndef BIBLELIST_H
#define BIBLELIST_H

#include <QObject>

class BibleList : public QObject
{
    Q_OBJECT
    QStringList list;
public:
    explicit BibleList(QObject *parent = nullptr);

    void appendElement(const QString &text);
    void appendList(const QStringList &list);
    void setList(const QStringList &list);
    void clearListBible();
    QString getText(const int index) const;
    int getSize() const;

signals:
    void preResetModel ();
    void postResetModel();
    void preSetItems   (int count);
    void postSetItems  ();

};

#endif // BIBLELIST_H
