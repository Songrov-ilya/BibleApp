#include "ScrollAreaMy.h"

ScrollAreaMy::ScrollAreaMy(QWidget *parent) :
    QScrollArea(parent)
{

}

void ScrollAreaMy::wheelEvent(QWheelEvent *)
{

}

void ScrollAreaMy::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit doubleClick(event->pos());
    QScrollArea::mouseDoubleClickEvent(event);
}
