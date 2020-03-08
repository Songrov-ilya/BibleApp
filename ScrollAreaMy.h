#ifndef SCROLLAREAMY_H
#define SCROLLAREAMY_H

#include <QScrollArea>
#include <QDebug>

class ScrollAreaMy : public QScrollArea
{
public:
    ScrollAreaMy(QWidget *parent = nullptr);

protected:
    virtual void wheelEvent(QWheelEvent *);
};

#endif // SCROLLAREAMY_H
