#ifndef TOPBARWIDGET_H
#define TOPBARWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>

class topBarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit topBarWidget(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    QPoint startPos;

};

#endif // TOPBARWIDGET_H
