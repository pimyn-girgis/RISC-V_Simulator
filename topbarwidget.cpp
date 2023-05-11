#include "topbarwidget.h"

topBarWidget::topBarWidget(QWidget *parent)
    : QWidget{parent}
{

}

// these next 3 functions are copypasted from stack overflow with little retrofitting //
void topBarWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void topBarWidget::mousePressEvent(QMouseEvent *event)
{
    startPos = event->pos();
    QWidget::mousePressEvent(event);
}

void topBarWidget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint delta = event->pos() - startPos;
    QWidget * w = window();
    if(w)
        w->move(w->pos() + delta);
    QWidget::mouseMoveEvent(event);

}
// i can kinda explain it but for now all you need to know is that they make the widget drag our window around//
// neat //
