#include "linenumberarea.h"

LineNumberArea::LineNumberArea()
{

}

QSize LineNumberArea::sizeHint() const
{
    return {};
}


void LineNumberArea::paintEvent(QPaintEvent *event)
{
    codeEditor->lineNumberAreaPaintEvent(event);
}
