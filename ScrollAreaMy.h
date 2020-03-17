#ifndef SCROLLAREAMY_H
#define SCROLLAREAMY_H

#include <QScrollArea>
#include <QMouseEvent>
#include <QDebug>

class ScrollAreaMy : public QScrollArea
{
    Q_OBJECT
public:
    ScrollAreaMy(QWidget *parent = nullptr);

signals:
    void doubleClick(const QPoint point);

protected:
    virtual void wheelEvent(QWheelEvent *) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

};

#endif // SCROLLAREAMY_H
