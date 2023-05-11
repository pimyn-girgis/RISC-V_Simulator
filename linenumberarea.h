#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

#include <QWidget>
#include "codeeditor.h"

class LineNumberArea : public QWidget
{
public:
    LineNumberArea();

    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:

};

#endif // LINENUMBERAREA_H
