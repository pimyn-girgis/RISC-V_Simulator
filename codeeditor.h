#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include "highlighter.h"
#include <QFile>
#include <QPainter>
#include <QTimer>

QT_BEGIN_NAMESPACE
class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
QT_END_NAMESPACE

class LineNumberArea;

//![codeeditordefinition]

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    CodeEditor(QWidget *parent = nullptr);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

    bool m_shouldPaint = false;

    void set_should_paint(bool shouldPaint);

    QPoint _cursorPos;
    QPoint _cursorPosEnd;


protected:
    void resizeEvent(QResizeEvent *event) override;

    /*void paintEvent(QPaintEvent *event) override
    {
        paintEvent(event);

        if(m_shouldPaint)
        {
            // Call the base class paint event to draw the text
            QPlainTextEdit::paintEvent(event);

            // Paint the line
            if (m_lineVisible) {
                QPainter painter(viewport());
                QPen pen(Qt::red, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
                painter.setPen(pen);
                painter.drawLine(m_lineStart, m_lineEnd);
            }
        }
    }*/


private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void highlight_for_stepping();
    void updateLineNumberArea(const QRect &rect, int dy);

    /*void updateLinePosition()
    {
        // Update the line position
        QTextCursor cursor = textCursor();
        m_lineStart = cursorRect(cursor).topLeft() + QPoint(0, cursor.block().layout()->lineAt(0).ascent() + cursor.block().layout()->lineAt(0).leading());
        m_lineEnd = m_lineStart + QPoint(width(), 0);

        // Toggle the line visibility
        m_lineVisible = !m_lineVisible;

        // Repaint the widget
        update();
    }*/

private:
    QWidget *lineNumberArea;

    QTimer m_timer;
    QPoint m_lineStart;
    QPoint m_lineEnd;
    bool m_lineVisible = false;
};

//![codeeditordefinition]
//![extraarea]

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(CodeEditor *editor) : QWidget(editor), codeEditor(editor)
    {}

    QSize sizeHint() const override
    {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        codeEditor->lineNumberAreaPaintEvent(event);
    }



private:

    CodeEditor *codeEditor;
};

//![extraarea]

#endif
